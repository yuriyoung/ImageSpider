#include "DataQueue.h"

#include <QCoreApplication>
#include <QDir>
#include <QTimer>
#include <QTextStream>
#include <QDebug>
#include <QThread>

DataQueue* DataQueue::m_instance = 0;
QMutex DataQueue::m_instanceLock;

DataQueue::DataQueue(QObject *parent) : QObject(parent)
{
    m_isLoading = false;
    m_urlCount = 0;
    m_imageCount = 0;
//    m_freeTimer = new QTimer(this);
//    connect(m_freeTimer, SIGNAL(timeout()), this, SLOT(freeQueue()));
}

DataQueue::~DataQueue()
{
    m_urlQueue.clear();
    m_imageQueue.clear();
//    m_freeTimer->stop();
}

DataQueue *DataQueue::data()
{
    if(m_instance == NULL)
    {
        m_instanceLock.lock();
        if(m_instance == NULL)
            m_instance = new DataQueue;
        m_instanceLock.unlock();
    }

    return m_instance;
}

void DataQueue::save()
{
    qDebug() << "sava to history data.";

    QString dataPath = QCoreApplication::applicationDirPath() + "/data/";
    QDir dir(dataPath);
    if( !dir.exists() )
        dir.mkdir(dataPath);
    if( !m_urlQueue.isEmpty() )
    {
        //save url
        QFile urlFile(dataPath+"urls.dat");
        if(urlFile.open(QIODevice::ReadWrite| QIODevice::Text))
        {
            QTextStream out(&urlFile);
            for(int i = 0; i < m_urlCount; ++i)
            {
                out << m_urlQueue.at(i).toString() << "\n";
            }
            out.flush();
            urlFile.close();
        }
    }
    // save image
    if( !m_imageQueue.isEmpty() )
    {
        QFile imageFile(dataPath+"images.dat");
        if(imageFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&imageFile);
            for(int i = 0; i < m_imageCount; ++i)
            {
                Url _url = m_imageQueue.at(i);
                out << _url.title() << ","
                    << _url.url().toString()
                    << "\n";
            }
            out.flush();
            imageFile.close();
        }
    }
}

void DataQueue::load()
{
    m_isLoading = true;
    QString dataPath = QCoreApplication::applicationDirPath() + "/data/";
    QFile urlFile(dataPath+"urls.dat");
    if( !urlFile.exists() )
    {
        return;
    }
    if(urlFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&urlFile);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            appendUrl( QUrl(line) );
        }
        in.flush();
        urlFile.close();
    }

    QFile imageFile(dataPath+"images.dat");

    if( !imageFile.exists() )
    {
        return;
    }
    if(imageFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&imageFile);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList list = line.split(",");
            QString title = list.at(0);
            QUrl url = list.at(1);
            appendImage( Url(title, url) );
        }
        in.flush();
        imageFile.close();
    }
    qDebug() << "Load history data.";
    m_isLoading = false;
}

void DataQueue::appendUrl(const QUrl &url)
{
    // 需要读写锁来做写锁
    m_urlLock.lockForWrite();
    if( !m_visitedUrlQueue.contains(url))
    {
        m_visitedUrlQueue.enqueue(url);
        m_urlQueue.enqueue(url);
        ++m_urlCount;
    }
    m_urlLock.unlock();

    if( m_visitedUrlQueue.count() >= 1000)
        m_visitedUrlQueue.clear();
}

void DataQueue::insterHeadUrl(const QUrl &url)
{
    m_urlLock.lockForWrite();
    if( !m_visitedUrlQueue.contains(url))
    {
        m_visitedUrlQueue.enqueue(url);
        m_urlQueue.insert(0,url);
        ++m_urlCount;
    }
    m_urlLock.unlock();
}

void DataQueue::enqueueUrl(const QUrl &url)
{
    appendUrl(url);
}

QUrl DataQueue::dequeueUrl()
{
    // 需要读写锁来做读锁
    m_urlLock.lockForRead();
    --m_urlCount;
    QUrl url = m_urlQueue.dequeue();
//    qDebug() << "[Url dequeue]: " << m_urlCount << " --- "  << url;
    m_urlLock.unlock();

    return url;
}

void DataQueue::appendImage(const Url &url)
{
    // 需要读写锁来做写锁
    m_imageLock.lockForWrite();
    if( !m_visitedImageQueue.contains(url))
    {
        m_visitedImageQueue.enqueue(url);
        m_imageQueue.enqueue(url);
        ++m_imageCount;
    }
    m_imageLock.unlock();

    if( m_visitedImageQueue.count() >= 500)
        m_visitedImageQueue.clear();
}

void DataQueue::enqueueImage(const Url &url)
{
    appendImage(url);
}

Url DataQueue::dequeueImage()
{
    // 需要读写锁来做读锁
//    m_imageLock.lockForRead();
    --m_imageCount;
    Url url = m_imageQueue.dequeue();
//    m_imageLock.unlock();

    return url;
}

void DataQueue::clearAll()
{
//    m_freeTimer->stop();
    m_urlQueue.clear();
    m_imageQueue.clear();
    m_visitedUrlQueue.clear();
    m_visitedImageQueue.clear();
    m_urlCount = 0;
    m_imageCount = 0;
}

int DataQueue::urlCount() const
{
    return m_urlCount;
}

bool DataQueue::isUrlEmpty() const
{
    return (m_urlCount == 0);
}

int DataQueue::imageCount() const
{
    return m_imageCount;
}

bool DataQueue::isImageEmpty() const
{
    return (m_imageCount == 0);
}

void DataQueue::freeQueue()
{
    m_visitedImageQueue.clear();
    m_visitedUrlQueue.clear();
}

