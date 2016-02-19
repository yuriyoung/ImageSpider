#include "Fetcher.h"
#include "DataQueue.h"
#include <QNetworkRequest>
#include <QEventLoop>
#include <QDateTime>
#include <QThread>
#include <QDebug>

Fetcher::Fetcher(QObject *parent) :
    AbstractSpider(parent)
{
    m_manager = 0;
    m_puase = false;
    m_stop = false;
}

Fetcher::Fetcher(AbstractParser *parser, QObject *parent):
    AbstractSpider(parent)
{
    m_manager = 0;
    m_puase = false;
    m_stop = false;
    m_parser = parser;
}

Fetcher::~Fetcher()
{
}

void Fetcher::start()
{
    m_puase = false;
    m_stop = false;
    if( !m_parser )
    {
        m_logString = logTime();
        m_logString.append("No any parser to handle page data.[Error]");
        qDebug() << m_logString;
        emit logString(1, m_logString);

        return;
    }

    if( !m_manager )
    {
        m_logString = logTime();
        m_logString.append("Network module uninitialized.[Error]");
        qDebug() << m_logString;
        emit logString(1, m_logString);
        return ;
    }

    fetchNext();
}

void Fetcher::pause()
{
    m_puase = true;

    m_logString = logTime();
    m_logString.append("Fetcher paused...[SYSTEM]");
    qDebug() << m_logString;
    emit logString(0, m_logString);
}

void Fetcher::stop()
{
    m_stop = true;

    DataQueue::data()->clearAll();

    m_logString = logTime();
    m_logString.append("Fetcher stoped...[SYSTEM]");
    qDebug() << m_logString;
    emit logString(0, m_logString);
}

AbstractParser *Fetcher::parser() const
{
    return m_parser;
}

void Fetcher::setParser(AbstractParser *parser)
{
    m_parser = parser;
}

void Fetcher::setStartUrl(const QUrl &url)
{
    DataQueue::data()->appendUrl(url);
}

QString Fetcher::logTime() const
{
    QDateTime dt;
    QDateTime time = dt.currentDateTime();
    QString str = "<font color=blue>";
    QString t = time.toString("[yyyy-MM-dd hh:mm:ss]");
    str.append(t);
    str.append(" </font>");
    return str;
}

void Fetcher::fetchNext()
{
    if( m_puase || m_stop)
    {
        m_puase = false;
        m_stop = false;
        return;
    }

    if( DataQueue::data()->isUrlEmpty() )
    {
        m_logString = logTime();
        m_logString.append("All pages have completed!No more page to do.[OK]");
        qDebug() << m_logString;
        emit logString(0, m_logString);

        emit finished();

        return;
    }

    QUrl url = DataQueue::data()->dequeueUrl();

/**
 * 这里如果使用loop事件循环处理网络事件
 * 线程数会不断增加80个以上，造成内存泄漏，导致程序crash
 * 不知为何？
 * 修改方案：从主线程中传入一个network指针来抓取网页数据
 */
    QNetworkRequest request(url);
//    QNetworkAccessManager network;
//    QEventLoop loop;
   m_currentReply = m_manager->get(request);
//    connect(m_currentReply, SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);
    connect(m_currentReply, SIGNAL(finished()), this, SLOT(fetchFinished()));

    connect(m_currentReply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(replyError(QNetworkReply::NetworkError)));
    connect(m_currentReply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(replySslErrors(QList<QSslError>)));
//    loop.exec();

}

void Fetcher::loadHistory()
{
    DataQueue::data()->load();
    m_logString = logTime();
    m_logString.append("History data load finished.[OK]");
    qDebug() << m_logString;
    emit logString(0, m_logString);
}

void Fetcher::fetchFinished()
{
    QUrl url = m_currentReply->url();
    if (m_currentReply->error() == QNetworkReply::NoError)
    {
        QByteArray replyData = m_currentReply->readAll();
        m_parser->parserUrl(replyData);
        m_parser->parserNextPage(replyData);
        m_parser->parserImage(replyData);

        m_logString = logTime();
        m_logString.append(url.toEncoded().constData());
        m_logString.append(" Fetcher succeeded![OK]");
        qDebug() << m_logString;
        emit logString(0, m_logString);
    }
    else
    {
        m_logString = logTime();
        m_logString.append(url.toEncoded().constData());
        m_logString.append(" Fetcher failed! error:");
        m_logString.append(m_currentReply->errorString());
        m_logString.append("[Error]");
        qDebug() << m_logString;
        emit logString(1, m_logString);
    }
    m_currentReply->deleteLater();
    fetchNext();
}

void Fetcher::replyError(QNetworkReply::NetworkError code)
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QUrl url = reply->url();
    DataQueue::data()->enqueueUrl(url);

    m_logString = logTime();
    m_logString.append("Fetcher network reply error: " + url.toString());
    m_logString.append("[Error]");
    qDebug() << m_logString;
    emit logString(1, m_logString);
}

void Fetcher::replySslErrors(QList<QSslError> sslErrors)
{
#ifndef QT_NO_SSL
    m_logString = logTime();
    foreach (const QSslError &error, sslErrors)
    {
        m_logString.append("Fetcher network SSL error: " + error.errorString());
        m_logString.append("\n");
    }
    m_logString.append("[Error]");
    qDebug() << m_logString;
    emit logString(1, m_logString);
#else
    Q_UNUSED(sslErrors);
#endif
}

QNetworkAccessManager *Fetcher::networkManager() const
{
    return m_manager;
}

void Fetcher::setNetworkManager(QNetworkAccessManager *manager)
{
    m_manager = manager;
}

