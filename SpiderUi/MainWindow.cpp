#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Image.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>
#include <QComboBox>
#include <QSplitter>
#include <QRegExp>
#include <QMessageBox>
#include <QDir>
#include <QDesktopServices>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow),
    m_logBuff(0),m_errBuff(0), m_downloadCount(0)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 1);
    ui->splitter_2->setStretchFactor(0, 8);
    ui->splitter_2->setStretchFactor(1, 2);
    ui->splitter_3->setStretchFactor(0, 3);
    ui->splitter_3->setStretchFactor(1, 7);

    DownloadingViewDelegate *delegate1 = new DownloadingViewDelegate(this);
    ui->downloadingView->setItemDelegate(delegate1);
    DownloadedViewDelegate *delegate2 = new DownloadedViewDelegate(this);
    ui->downloadedView->setItemDelegate(delegate2);

    connect(ui->downloadedView, &QTreeWidget::itemDoubleClicked,
            this, &MainWindow::itemDoubleClicked );
    // Create common actions
    m_startAction = new QAction(QIcon(":/icons/start.png"), tr("&Start"), this);
    m_pauseAction = new QAction(QIcon(":/icons/pause.png"), tr("&Pause"), this);
    m_stopAction = new QAction(QIcon(":/icons/stop.png"), tr("S&top"), this);
    m_addAction = new QAction(QIcon(":/icons/add.png"), tr("&Add"), this);
    m_removeAction = new QAction(QIcon(":/icons/remove.png"), tr("&Remove"), this);
    // File menu
    QMenu *fileMenu = ui->menuBar->addMenu(tr("&File"));
    fileMenu->addAction(m_startAction);
    fileMenu->addAction(m_pauseAction);
    fileMenu->addAction(m_stopAction);
    fileMenu->addAction(m_addAction);
    fileMenu->addAction(m_removeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(QIcon(":/icons/exit.png"), tr("&Exit"), this, SLOT(close()));

    // Help menu
//    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
//    helpMenu->addAction(tr("&About"), this, SLOT(aboutApp()));

    // main toolbar
    ui->mainToolBar->setMovable(true);
    ui->mainToolBar->addAction(m_startAction);
    ui->mainToolBar->addAction(m_pauseAction);
    ui->mainToolBar->addAction(m_stopAction);
    ui->mainToolBar->addAction(m_addAction);
    ui->mainToolBar->addAction(m_removeAction);

    QActionGroup* actGroup = new QActionGroup(this);
    actGroup->addAction(m_startAction);
    actGroup->addAction(m_pauseAction);
    actGroup->addAction(m_stopAction);
    m_startAction->setCheckable(true);
    m_pauseAction->setCheckable(true);
    m_stopAction->setCheckable(true);
    m_startAction->setEnabled(true);
    m_pauseAction->setEnabled(false);
    m_stopAction->setEnabled(false);

    // Url toolbar
    QToolBar *urlBar = new QToolBar(tr("Url"));
    addToolBar(Qt::TopToolBarArea, urlBar);
    urlBar->setMovable(true);

    QLabel *urlTile = new QLabel(tr("Site:"));
    m_siteCombox = new QComboBox(this);
    m_siteCombox->setEditable(true);
    m_siteCombox->setFixedWidth(320);
    m_siteCombox->setDuplicatesEnabled(false);
    QLabel *savetoTile = new QLabel(tr("Save to:"));
    m_savetoCombox = new QComboBox(this);
    m_savetoCombox->setEditable(true);
    m_savetoCombox->setFixedWidth(210);
    m_savetoCombox->setDuplicatesEnabled(false);

//    connect(m_siteCombox, &QComboBox::currentTextChanged,
//            this, &MainWindow::siteChanged);
//    connect(m_savetoCombox, &QComboBox::currentTextChanged,
//            this, &MainWindow::destinationFolderChanged);


    urlBar->addWidget(urlTile);
    urlBar->addWidget(m_siteCombox);
    urlBar->addWidget(savetoTile);
    urlBar->addWidget(m_savetoCombox);

    // Load settings and start
    setWindowTitle(tr("WebImage Spider v0.1 beta(下图利器) - copyleft (c) 2015 Power by YURI"));
    resize(800, 480);

    m_spider = new Spider;
//    m_spiderThread = new QThread(this);
//    m_spider->moveToThread(m_spiderThread);
//    m_spiderThread->start();

    m_network = new QNetworkAccessManager(this);
    m_spider->setNetworkManager(m_network);
    m_downloader = new Downloader(this);
    m_downloader->setNetwokManager(m_network);
    m_dispatcher = new DownloadDispatcher;

    m_dispatcherThread = new QThread(this);
    m_dispatcher->moveToThread(m_dispatcherThread);
    m_dispatcherThread->start();

//    connect(m_spiderThread, &QThread::finished, &QThread::deleteLater);
    connect(m_dispatcherThread, &QThread::finished, &QThread::deleteLater);

    connect(this, &MainWindow::spiderStart, m_spider, &Spider::start);
    connect(this, &MainWindow::spiderPause, m_spider, &Spider::pause);
    connect(this, &MainWindow::spiderStop, m_spider, &Spider::stop);
    connect(this, &MainWindow::spiderStart, m_dispatcher, &DownloadDispatcher::startDispatch);
    connect(this, &MainWindow::spiderPause, m_dispatcher, &DownloadDispatcher::stopDispatch);
    connect(this, &MainWindow::spiderStop, m_dispatcher, &DownloadDispatcher::stopDispatch);

    connect(m_startAction, SIGNAL(toggled(bool)), this, SLOT(start(bool)) );
    connect(m_pauseAction, SIGNAL(toggled(bool)), this, SLOT(pause(bool)) );
    connect(m_stopAction, SIGNAL(toggled(bool)), this, SLOT(stop(bool)) );

    connect(m_spider, &Spider::logString, this, &MainWindow::logString );
    connect(m_downloader, &Downloader::logString, this, &MainWindow::logString);

    connect(m_dispatcher, &DownloadDispatcher::dispatchImage, this, &MainWindow::addImageItem );
    connect(m_downloader, &Downloader::downloadOnefinished, this, &MainWindow::updateNext);

    //http://sexy.faceks.com/
    QStringList nextPagePatterns;
    nextPagePatterns << "<a\\s+class=[\"']next[\"'].*href=[\"']([^>]*page=\\d+.*)[\"']>"
                     << "<a\\s+href=['\"]([^['\"]+.html)['\"]>></a>"
                     << "<a\\s+href=['\"]([^['\"]+.html)['\"]>下一.*</a>"
                     << "<a\\s+href=['\"]([^['\"]+.html)['\"]>Next</a>";
    //http://sexy.faceks.com
    QString rxUrlPattern = "<div\\s+class=['\"]pic['\"].*href=['\"]([^['\"]+)['\"].*>";
    QString rxImgPattern = "bigimgsrc=[\"']([^'\"]+)['\"]";

    ui->textEdit->setText(rxUrlPattern);
    ui->textEdit_2->setText(rxImgPattern);
    foreach (QString str, nextPagePatterns)
    {
        ui->textEdit_3->append(str);
    }

    m_siteCombox->addItem("http://sexy.faceks.com/?page=1");
    m_destinationFolder = QApplication::applicationDirPath() + "/Images/";
    m_savetoCombox->addItem(m_destinationFolder);

    m_spider->setPageRegexpPattern(rxUrlPattern);
    m_spider->setImageRegexpPattern(rxImgPattern);
    m_spider->setNextPageRegexpPatterns(nextPagePatterns);
}

MainWindow::~MainWindow()
{
//    m_spiderThread->quit();
    m_dispatcherThread->quit();

    delete m_network;
    delete m_downloader;
    delete m_dispatcher;

    delete ui;
}

Image *MainWindow::imageForRow(int row)
{
    return NULL;
}

Image *MainWindow::imageForMd5(const QString md5)
{
    Image *image = NULL;
    QMap<Image*, QTreeWidgetItem*>::iterator i = m_imageItems.begin();
    while (i != m_imageItems.end())
    {
        if(i.key()->md5 == md5)
        {
            image = i.key();
            break;
        }
        ++i;
    }

    return image;
}

void MainWindow::start(bool checked)
{
    if( !checked )
        return;
    if(m_siteCombox->currentText().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("The site url is empty. Please chose a site url.");
        msgBox.exec();
        m_startAction->setChecked(false);
        return;
    }
    if(m_siteCombox->findText(m_siteCombox->currentText()) == -1)
        m_siteCombox->addItem( m_siteCombox->currentText() );
    if(m_savetoCombox->findText(m_savetoCombox->currentText()) == -1)
        m_savetoCombox->addItem( m_savetoCombox->currentText() );

    m_destinationFolder = m_savetoCombox->currentText();
    m_destinationFolder = QDir::toNativeSeparators(m_destinationFolder);
    QDir dir(m_destinationFolder);
    if( !dir.exists() )
    {
        QMessageBox msgBox;
        msgBox.setText("the folder/path not exist or not available.");
        msgBox.exec();
        m_startAction->setChecked(false);
        return;
    }
    m_savetoCombox->setCurrentText(m_destinationFolder);
    m_downloader->setDownloadPath(m_destinationFolder);

    QUrl startUrl = QUrl(m_siteCombox->currentText());
    if(!startUrl.isValid() )
    {
        QMessageBox msgBox;
        msgBox.setText("The site url is invalid. Please input a valid url.");
        msgBox.exec();
        return;
    }
    m_spider->setStartupUrl(startUrl);
    QString referer = "http://" + startUrl.host();
    m_downloader->setReferer(referer);

    m_pauseAction->setEnabled(true);
    m_stopAction->setEnabled(true);

    emit spiderStart(checked);
}

void MainWindow::pause(bool checked)
{
    emit spiderPause(checked);

    QMapIterator<Image*, QTreeWidgetItem*> i(m_imageItems);
    while (i.hasNext())
    {
        i.next();
        if( i.key()->state != Image::Finished)
        {
            i.key()->setState(Image::Paused);
            i.value()->setText(5, i.key()->stateString);
        }
    }
}

void MainWindow::stop(bool checked)
{
    emit spiderStop(checked);

    QMapIterator<Image*, QTreeWidgetItem*> i(m_imageItems);
    while (i.hasNext())
    {
        i.next();
        if( i.key()->state != Image::Finished &&
                i.key()->state != Image::Downloading)
        {
            i.key()->setState(Image::Stopping);
            i.value()->setText(5, i.key()->stateString);
        }
    }
}

void MainWindow::logString(int type, const QString &log)
{
    switch (type)
    {
    case 0:
        ui->logEdit->append(log);
        ++m_logBuff;
        if( m_logBuff >= 80 )
        {
            m_logBuff = 0;
            ui->logEdit->clear();
        }
        break;
    case 1:
        ui->errorLogEdit->append(log);
        ++m_errBuff;
        if( m_errBuff >= 80 )
        {
            m_errBuff = 0;
            ui->errorLogEdit->clear();
        }
        break;
    default:
        break;
    }
}

void MainWindow::addImageItem(const QString &title, const QString &size, const QUrl &url)
{
    Image* image = new Image;
    image->folder = title;
    image->url = url;
    image->size = size;

    QUrl copy(url);
    copy.setQuery(copy.query(QUrl::FullyDecoded), QUrl::DecodedMode);
    QString path = copy.toString();
    QRegExp rx("([-\\w]+.jpg)");// 匹配: - 中文 下滑线 数字 字母
    QString basename;
    if( rx.indexIn(path) > 0)
        basename = rx.cap(1);
    if (basename.isEmpty())
        basename = "download";
    image->name = basename;

    QString toMd5 = title + basename;
    QString md5;
    QByteArray byte;
    byte = QCryptographicHash::hash ( toMd5.toLatin1(), QCryptographicHash::Md5 );
    md5.append(byte.toHex());
    image->md5 = md5;

    connect(image, SIGNAL(progressUpdated()), this, SLOT(updateProgress()));
    connect(image, SIGNAL(downloadRateUpdated()), this, SLOT(updateDownloadRate()));
    connect(image, SIGNAL(stateChanged()), this, SLOT(updateState()));

    QTreeWidgetItem *item = new QTreeWidgetItem(ui->downloadingView);
    item->setText(0, QString("%1").arg(++m_downloadCount));
    item->setText(1, title);
    item->setToolTip(1, tr("Image: %1<br>Destination: %2")
                           .arg(basename).arg(m_savetoCombox->currentText()));
    item->setToolTip(2, tr("Image: %1<br>Destination: %2")
                           .arg(basename).arg(m_savetoCombox->currentText()));
    item->setToolTip(3, tr("Image: %1<br>Destination: %2")
                           .arg(basename).arg(m_savetoCombox->currentText()));
    item->setToolTip(4, tr("Image: %1<br>Destination: %2")
                           .arg(basename).arg(m_savetoCombox->currentText()));
    item->setToolTip(5, tr("Image: %1<br>Destination: %2")
                           .arg(basename).arg(m_savetoCombox->currentText()));
    item->setText(2, "0%");
    item->setData(2, Qt::UserRole+1, QVariant(md5));
    item->setText(3, "0.0 KB/s");
    item->setText(4, size);
    item->setText(5, tr("Preparing"));
    item->setText(6, md5);

    m_imageItems.insert(image, item);
    m_downloader->download(image);
}

void MainWindow::updateProgress()
{
    Image* image = qobject_cast<Image*>(sender());
    m_imageItems.value(image)->setText(2, QString::number(image->progress));
}

void MainWindow::updateDownloadRate()
{
    Image* image = qobject_cast<Image*>(sender());
    m_imageItems.value(image)->setText(3, image->downloadRate);
}

void MainWindow::updateState()
{
    Image* image = qobject_cast<Image*>(sender());
    m_imageItems.value(image)->setText(5, image->stateString);
}

void MainWindow::updateNext()
{
    // 完成的移到已完成列表
    QMap<Image*, QTreeWidgetItem*>::iterator i = m_imageItems.begin();
    while (i != m_imageItems.end() )
    {
        if( i.key()->state == Image::Finished )
        {
            Image* img = i.key();
            QTreeWidgetItem* item = i.value();
//            ui->downloadedView->addTopLevelItem(item);//没作用

            int count = ui->downloadedView->topLevelItemCount();
            if(count >= 512)
                ui->downloadedView->clear();
            QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->downloadedView);
            newItem->setText(0, QString("%1").arg(m_downloadCount));
            newItem->setText(1, img->localFile);
            newItem->setToolTip(1, tr("Image: %1<br>Destination: %2<br><b>(Double click open image in folder)")
                                   .arg(img->localFile).arg(m_savetoCombox->currentText()));
            newItem->setText(2, QString::number(img->progress));
            newItem->setText(3, img->downloadRate);
            newItem->setText(4, img->size);
            newItem->setText(5, img->stateString);
            newItem->setText(6, img->md5);

            i = m_imageItems.erase(i);
            delete img;
            delete item;
        }
        else
        {
            ++i;
        }
    }

    m_dispatcher->dispatchNext();
}

void MainWindow::itemDoubleClicked(QTreeWidgetItem *item, int)
{
    QString localFile = item->data(1, Qt::DisplayRole).toString();
    QFileInfo info(localFile);
    QDesktopServices::openUrl( QUrl::fromLocalFile( info.absolutePath()) );
}

void MainWindow::siteChanged(const QString &text)
{
    QUrl url(text);
    if(!url.isValid() )
    {
        QMessageBox msgBox;
        msgBox.setText("The site url is invalid. Please input a valid url.");
        msgBox.exec();
        return;
    }

    if(m_siteCombox->findText(text) == -1)
        m_siteCombox->addItem(text);
    m_siteCombox->setCurrentText(text);
    m_spider->setStartupUrl(url);
    QString referer = "http://" + url.host();
    m_downloader->setReferer(referer);
}

void MainWindow::destinationFolderChanged(const QString &text)
{
    m_destinationFolder = QDir::toNativeSeparators(text);
    QDir dir(m_destinationFolder);
    if( !dir.exists() )
    {
        QMessageBox msgBox;
        msgBox.setText("the folder/path not exist or not available.");
        msgBox.exec();
        return;
    }
    if(m_savetoCombox->findText(m_destinationFolder) == -1)
        m_savetoCombox->addItem(m_destinationFolder);

    m_savetoCombox->setCurrentText(m_destinationFolder);
    m_downloader->setDownloadPath(m_destinationFolder);
}

