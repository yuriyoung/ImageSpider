#include "Parser.h"
#include "DataQueue.h"

#include <QTimer>
#include <QDebug>

Parser::Parser(QObject *parent) : AbstractParser(parent)
{

}

Parser::~Parser()
{

}

void Parser::setUrlRegexpPattern(const QString &pattern)
{
    m_urlPattern = pattern;
}

QString Parser::urlRegexpPattern() const
{
    return m_urlPattern;
}

void Parser::setImageRegexpPattern(const QString &pattern)
{
    m_imagePattern = pattern;
}

QString Parser::imageRegexpPattern() const
{
    return m_imagePattern;
}

void Parser::parserUrl(const QByteArray &html)
{
    QRegExp rx(m_urlPattern);
    if( !rx.isValid() )
        return ;
    rx.setMinimal(true);//使用非贪婪匹配原则
    QString str = QString(html); //QString::fromUtf8(replyData);
    int pos = 0;
    while ((pos = rx.indexIn(str, pos)) != -1)
    {
        if( rx.matchedLength() > 0 )
        {
            QString strUrl = rx.cap(1);
            QUrl url = QUrl(strUrl);
            if( url.isValid() )
            {
                if( url.isRelative() )
                    url = QUrl( m_referer + strUrl );
                DataQueue::data()->appendUrl( url );
            }
        }
        pos += rx.matchedLength();
    }
}

void Parser::parserNextPage(const QByteArray &html)
{
    int i = 0;
    foreach (QString pattern, m_nextPatterns)
    {
        ++i;
        QRegExp rx(pattern);
        rx.setMinimal(true);//使用非贪婪匹配原则
        QString str = QString(html);
        if( rx.indexIn(str) > 0)
        {
            QString strUrl = rx.cap(1);
            QUrl url = QUrl(strUrl);
            if( url.isValid() )
            {
                if( url.isRelative() )
                    url = QUrl( m_referer + strUrl );
                if( i == 3)
                    DataQueue::data()->insterHeadUrl(url);
                else
                    DataQueue::data()->appendUrl( url );

                qDebug() << "================================= Has next page ====================== ";
            }
        }
    }
}

void Parser::parserImage(const QByteArray &html)
{
    QString title = parserTitle(html);

    QRegExp rx(m_imagePattern);
    if( !rx.isValid() )
        return;
    rx.setMinimal(true);
    QString str = QString(html);
    int pos = 0;
    while ((pos = rx.indexIn(str, pos)) != -1)
    {
        if( rx.matchedLength() > 0 )
        {
            QString imgUrl = rx.cap(1);
            QUrl url = QUrl(imgUrl);
            if( url.isValid() )
            {
                if( url.isRelative() )
                    url = QUrl( m_referer + imgUrl );
                DataQueue::data()->appendImage( Url(title, url) );
            }
        }
        pos += rx.matchedLength();
    }
}

// 解析图片时，最好加上标题，用来给图片分别存放在对应的文件夹内
// 因为部分网站图片所在的链接没有title和alt属性
// 所以统一取当前页面的主title标签内容(会存在一个非常长的标题)
// 可以使用空格、-或_来截断取首部
// <title>(.*)</title>
QString Parser::parserTitle(const QByteArray &html)
{
    QString long_title;
    QRegExp rx("<title>(.*)</title>");
    rx.setMinimal(true);
    QString str = QString::fromUtf8(html);
    if( rx.indexIn(str) > 0 )
    {
        long_title = rx.cap(1);
        QStringList list1 = long_title.split("_");
        QStringList list2 = long_title.split("-");
        if(list1.count() >= 2)
        {
            return list1.at(0);
        }
        else if( list2.count() >= 2 )
        {
            return list2.at(0);
        }
    }

    return long_title;
}

QStringList Parser::nextPageRegexpPatterns() const
{
    return m_nextPatterns;
}

void Parser::setNextPageRegexpPatterns(const QStringList &nextPatterns)
{
    m_nextPatterns = nextPatterns;
}

QString Parser::referer() const
{
    return m_referer;
}

void Parser::setReferer(const QString &referer)
{
    m_referer = referer;
}


