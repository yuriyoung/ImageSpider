#include "DownloadDispatcher.h"
#include "DataQueue.h"

#include <QFile>
#include <QByteArray>
#include <QRegExp>
#include <QCryptographicHash>
#include <QEventLoop>
#include <QThread>

#include <QDebug>

DownloadDispatcher::DownloadDispatcher(QObject *parent):
    QObject(parent), m_stop(true)
{
    m_limitCount = 8;
    m_currentCount = 0;
}

DownloadDispatcher::~DownloadDispatcher()
{
}

void DownloadDispatcher::setDestination(QObject *destiantion)
{
}

void DownloadDispatcher::startDispatch(bool ok)
{
    if( !ok )
        return;

    m_stop = false;
    run();
}

void DownloadDispatcher::stopDispatch(bool ok)
{
    if( !ok )
        return;
    m_stop = true;
}

void DownloadDispatcher::dispatchNext()
{
    --m_currentCount;
}

void DownloadDispatcher::newImage(const QString &title, const QUrl &url)
{
    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    QEventLoop loop;
    QNetworkReply *reply = manager.head(request);
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);
    loop.exec();
    QVariant var = reply->header(QNetworkRequest::ContentLengthHeader);
    qint64 size = var.toLongLong();
    QString sizeStr = sizeWithUnit(size);
    emit dispatchImage(title, sizeStr, url);
    reply->deleteLater();
}

void DownloadDispatcher::run()
{
    while( !m_stop )
    {
        if( !DataQueue::data()->isImageEmpty() )
        {
            if( m_currentCount < m_limitCount )
            {
                Url image = DataQueue::data()->dequeueImage();
                QString title = image.title();
                QUrl url = image.url();
                newImage(title, url);
                ++m_currentCount;
            }
        }
    }
}

QString DownloadDispatcher::sizeWithUnit(qint64 bytes)
{
    QString fileSize;
    QString unit;
    double size = 0;
    if (bytes < 1024)
    {
        size = (double)bytes;
        unit = "Bytes";
    }
    else if (bytes < 1024*1024)
    {
        size = (double)(bytes / 1024);
        unit = "KB";
    }
    else
    {
        size = (double)(bytes / 1024*1024);
        unit = "MB";
    }
    fileSize = QString::fromLatin1("%1 %2").arg(size, 3, 'f', 1).arg(unit);

    return fileSize;
}

