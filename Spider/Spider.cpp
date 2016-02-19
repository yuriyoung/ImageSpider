#include "Spider.h"

Spider::Spider(QObject *parent) : QObject(parent)
{
    m_parser = new Parser(this);
    m_fetcher = new Fetcher(m_parser, this);

    connect(m_fetcher, &Fetcher::logString, this, &Spider::logString);
}

Spider::~Spider()
{
    delete m_parser;
    delete m_fetcher;
}

void Spider::setNetworkManager(QNetworkAccessManager *manager)
{
    m_fetcher->setNetworkManager(manager);
}

void Spider::start(bool ok)
{
    if(!ok)
        return;
    m_fetcher->start();
}

void Spider::pause(bool ok)
{
    if(!ok)
        return;
    m_fetcher->pause();
}

void Spider::stop(bool ok)
{
    if(!ok)
        return;
    m_fetcher->stop();
}

void Spider::setStartupUrl(const QUrl &url)
{
    m_fetcher->setStartUrl(url);
    QString referer = "http://" + url.host();
    m_parser->setReferer(referer);
}

void Spider::setPageRegexpPattern(const QString &pattern)
{
    if( pattern.isEmpty() )
        return;
    m_parser->setUrlRegexpPattern(pattern);
}

void Spider::setImageRegexpPattern(const QString &pattern)
{
    if( pattern.isEmpty() )
        return;
    m_parser->setImageRegexpPattern(pattern);
}

void Spider::setNextPageRegexpPatterns(const QStringList &patterns)
{
    if( patterns.isEmpty() )
        return;
    m_parser->setNextPageRegexpPatterns(patterns);
}

