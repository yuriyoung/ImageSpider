#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Spider.h"
#include "Downloader.h"
#include "DownloadDispatcher.h"
#include <QThread>

QT_BEGIN_NAMESPACE
class QAction;
class QCloseEvent;
class QLabel;
class QProgressDialog;
class QSlider;
class QLineEdit;
class QPalette;
class QComboBox;
class QTreeWidgetItem;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int rowOfImage(Image *image);
    Image* imageForRow(int row);// 要从队列中删除数据，这种方法不安全
    Image* imageForMd5(const QString md5);

signals:
    void spiderStart(bool);
    void spiderPause(bool);
    void spiderStop(bool);

private slots:
    void start(bool);
    void pause(bool);//暂停当前任务，等待继续
    void stop(bool);//停止当前任务，并清除所有数据
    void logString(int type, const QString &log);
    void addImageItem(const QString &title, const QString &size, const QUrl &url);
    void updateProgress();
    void updateDownloadRate();
    void updateState();
    void updateNext();
    void itemDoubleClicked(QTreeWidgetItem*,int);
    void siteChanged(const QString & text);
    void destinationFolderChanged(const QString & text);

private:
    Ui::MainWindow *ui;
    QComboBox*  m_siteCombox;
    QComboBox*  m_savetoCombox;

    QNetworkAccessManager* m_network;
    Spider*         m_spider;
    Downloader*     m_downloader;
    DownloadDispatcher* m_dispatcher;

//    QThread*        m_spiderThread;
    QThread*        m_dispatcherThread;
    QMap<Image*, QTreeWidgetItem*> m_imageItems;

    int         m_logBuff;
    int         m_errBuff;
    int         m_downloadCount;
    QString     m_destinationFolder;

    QAction     *m_addAction;
    QAction     *m_startAction;
    QAction     *m_pauseAction;
    QAction     *m_stopAction;
    QAction     *m_removeAction;
};

#endif // MAINWINDOW_H
