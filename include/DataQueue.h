#ifndef DATAQUEUE_H
#define DATAQUEUE_H

#include "global.h"
#include <QObject>
#include <QQueue>
#include <QUrl>
#include <QStringList>
#include <QMutex>
#include <QReadWriteLock>
#include <QTimer>

class Url;

class SPIDER_EXPORT DataQueue : public QObject
{
    Q_OBJECT
public:
    ~DataQueue();
    static DataQueue* data();

    enum
    {
        PageUrl,
        ImageUrl
    };

    void save();
    void load();

    void appendUrl(const QUrl &url);
    void insterHeadUrl(const QUrl &url);
//    void appendUrls(const QStringList &urlList);
    void enqueueUrl(const QUrl &url);
    QUrl dequeueUrl();

    void appendImage(const Url &url);
//    void appendImages(const QStringList &urlList);
    void enqueueImage(const Url &url);
    Url dequeueImage();

    void clearAll();

    int urlCount() const;
    bool isUrlEmpty() const;

    int imageCount() const;
    bool isImageEmpty() const;

private slots:
    void freeQueue();

private:
    explicit DataQueue(QObject *parent = 0);
    DataQueue(const DataQueue &) Q_DECL_EQ_DELETE;
    DataQueue& operator=(DataQueue rhs) Q_DECL_EQ_DELETE;
    static DataQueue*   m_instance;
    static QMutex   m_instanceLock;
    QReadWriteLock      m_urlLock;
    QReadWriteLock      m_imageLock;

    QQueue<QUrl>    m_urlQueue;
    QQueue<QUrl>    m_visitedUrlQueue;
    QQueue<Url>     m_imageQueue;
    QQueue<Url>     m_visitedImageQueue;
    int             m_urlCount;
    int             m_imageCount;
    bool            m_isLoading;

//    QTimer*         m_freeTimer;
};


class Url
{
public:
    Url();
    Url(const QString &title, const QUrl &url)
    {
        m_title = title;
        m_url = url;
    }

    Url(const Url &copy)
    {
        this->m_title = copy.m_title;
        this->m_url = copy.m_url;
    }

    inline Url &operator=(Url &&other)
    {
        using std::swap;
        swap(m_title, other.m_title);
        swap(m_url, other.m_url);
        return *this;
    }

    inline bool operator==(const Url &url)
    {
        if( this->m_title == url.m_title &&
                this->m_url == url.m_url )
            return true;
        return false;
    }

    QString title() const{ return m_title;}
    QUrl url() const { return m_url;}

private:
    QString m_title;
    QUrl    m_url;
};

#endif // DATAQUEUE_H
