#include "Downloader.h"
#include "Image.h"

#include <QCoreApplication>
#include <QDir>
#include <QMapIterator>
#include <QDateTime>

Downloader::Downloader(QObject *parent) :
    QObject(parent)
{
    m_stop = true;
    m_network = 0;
    m_downloadedCount = 0;
    m_maxDownloading = 5;
    m_currentDownloadCount = 0;
    m_downloadPath = QCoreApplication::applicationDirPath() + "/Images/";
}

Downloader::~Downloader()
{
    qDeleteAll(m_currentDownloads);
    m_currentDownloads.clear();
}

void Downloader::startDownload()
{
    if( !m_network )
    {
        m_logString = logTime();
        m_logString.append("Network module uninitialized.[Error]");
        qDebug() << m_logString;
        emit logString(1, m_logString);
        return ;
    }

    m_stop = false;
    downloadNext();

    m_logString = logTime();
    m_logString.append("Start download...[OK]");
    qDebug() << m_logString;
    emit logString(0, m_logString);
}

void Downloader::stopDownload()
{
    m_stop = true;

    m_logString = logTime();
    m_logString.append("Stop download...[OK]");
    qDebug() << m_logString;
    emit logString(0, m_logString);
}

void Downloader::downloadNext()
{
    if( m_stop )
        return;

//    if( m_imageQueue.isEmpty() )
//    {
//        m_logString = logTime();
//        m_logString.append("All image have downloaded![OK]");
//        qDebug() << m_logString;
//        emit logString(0, m_logString);
//        return;
//    }

    m_logString = logTime();
    m_logString.append("Downloading next image...[OK]");
    qDebug() << m_logString;
    emit logString(0, m_logString);
}

QNetworkAccessManager *Downloader::networkManager() const
{
    return m_network;
}

void Downloader::setNetwokManager(QNetworkAccessManager *networkManager)
{
    m_network = networkManager;
}

void Downloader::downloadReadyRead()
{
    //do nothing.
}

void Downloader::download(Image *image)
{
    QUrl url = image->url;
    QString folder = image->folder;
    QString name = image->name;

    QString path = m_downloadPath + folder;
    QDir dir(path);
    if( !dir.exists() )
    {
        dir.mkpath(path);
    }
    QString filename = path + "/" + name;
    image->localFile = filename;
    QFile *file = new QFile;
    file->setFileName(filename);
    image->setState(Image::Downloading);

    QNetworkRequest request(url);
    request.setRawHeader("Host", url.host().toLocal8Bit());
    request.setRawHeader("Referer", m_referer.toUtf8());
    QNetworkReply *reply = m_network->get(request);
    m_currentDownloads.insert(reply, file);
    connect(reply, SIGNAL(finished()), this, SLOT(downloadFinished()));
    connect(reply, SIGNAL(readyRead()), this, SLOT(downloadReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), image,
                SLOT(downloadProgress(qint64,qint64)));
    image->progressTime.start();
}

QString Downloader::logTime() const
{
    QDateTime dt;
    QDateTime time = dt.currentDateTime();
    QString str = "<font color=blue>";
    QString t = time.toString("[yyyy-MM-dd hh:mm:ss]");
    str.append(t);
    str.append(" </font>");
    return str;
}

void Downloader::downloadFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QUrl url = reply->url();
    QFile *file = m_currentDownloads.take(reply);
    if (reply->error() == QNetworkReply::NoError)
    {
        if (!file->open(QIODevice::WriteOnly))
        {
            m_logString = logTime();
            m_logString.append("Problem opening save file: ");
            m_logString.append(file->fileName());
            m_logString.append("for download(");
            m_logString.append(url.toEncoded().constData());
            m_logString.append(")error:");
            m_logString.append(file->errorString());
            m_logString.append("[Error]");
            qDebug() << m_logString;
            emit logString(1, m_logString);
        }
        else
        {
            file->write(reply->readAll());
            ++m_downloadedCount;

            m_logString = logTime();
            m_logString.append(QString::number(m_downloadedCount));
            m_logString.append(" images - ");
            m_logString.append(file->fileName());
            m_logString.append(" - Download Succeeded!");
            m_logString.append("[OK]");
            qDebug() << m_logString;
            emit logString(0, m_logString);
        }
    }
    else
    {
        // download failed
        m_logString = logTime();
        m_logString.append("Download image failed,error:");
        m_logString.append(reply->errorString());
        m_logString.append("[Error]");
        qDebug() << m_logString;
        emit logString(1, m_logString);
    }
    file->close();
    m_currentDownloads.remove(reply);
    delete file;
    delete reply;
    --m_currentDownloadCount;
    emit downloadOnefinished();
    downloadNext();
}

int Downloader::currentDownloadCount() const
{
    return m_currentDownloadCount;
}

QString Downloader::downloadPath() const
{
    return m_downloadPath;
}

void Downloader::setDownloadPath(const QString &downloadPath)
{
    QString tmp_path = downloadPath;
    if( !tmp_path.endsWith("/"))
        tmp_path += "/";
    m_downloadPath = tmp_path;
}

void Downloader::setLimitDownloading(int max)
{
    m_maxDownloading = max;
}

int Downloader::limitDowndloading() const
{
    return m_maxDownloading;
}

int Downloader::downloadedCount() const
{
    return m_downloadedCount;
}

QString Downloader::referer() const
{
    return m_referer;
}

void Downloader::setReferer(const QString &referer)
{
    m_referer = referer;
}

QString Downloader::saveFileName(const QUrl &url)
{
    QUrl copy(url);
    copy.setQuery(copy.query(QUrl::FullyDecoded), QUrl::DecodedMode);
    QString path = copy.toString();
    QRegExp rx("([-\\w]+.jpg)");// 匹配: - 中文 下滑线 数字 字母
    QString basename;
    if( rx.indexIn(path) > 0)
    {
        basename = rx.cap(1);//FileInfo(path).fileName();
    }

    if (basename.isEmpty())
        basename = "download";

    if (QFile::exists(basename))
    {
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)))
            ++i;

        basename += QString::number(i);
    }

    return basename;
}
