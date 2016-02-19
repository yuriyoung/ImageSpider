#include "Worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
    //http://sexy.faceks.com/
    //http://www.2xiezhen.com/meinvxiezhen/
    startUrl = QUrl("http://sexy.faceks.com/");
//    startUrl = QUrl("http://www.2xiezhen.com/meinvxiezhen/");
    QString referer = "http://" + startUrl.host();
    DataQueue::data()->appendUrl(startUrl);

    network = new QNetworkAccessManager(this);
    spider = new Spider;
    parser = new Parser;

    QStringList nextPagePatterns;
    nextPagePatterns << "<a\\s+class=[\"']next[\"'].*href=[\"']([^>]*page=\\d+.*)[\"']>"
                     << "<a\\s+href=['\"]([^['\"]+.html)['\"]>></a>"
                     << "<a\\s+href=['\"]([^['\"]+.html)['\"]>下一页</a>"
                     << "<a\\s+href=['\"]([^['\"]+.html)['\"]>Next</a>";

    //http://sexy.faceks.com
    parser->setUrlRegexpPattern("<div\\s+class=['\"]pic['\"].*href=['\"]([^['\"]+)['\"].*>");
    parser->setImageRegexpPattern("bigimgsrc=[\"']([^'\"]+)['\"]");
    parser->setNextPageRegexpPatterns(nextPagePatterns);

    //http://www.2xiezhen.com/siwameinv
//    parser->setUrlRegexpPattern("<li>\\s*<a.*href=['\"]([^['\"]+.html)['\"].*/></a>");
//    parser->setImageRegexpPattern("<a\\s+class=['\"]showpic['\"].*href=.*src=['\"]([^['\"]+.jpg)['\"]\\s*/>");
    parser->setRefererUrl(referer);

    spider->setNetwokManager(network);
    spider->setParser(parser);


    // download images
    downloader = new Downloader;
    downloader->setNetwokManager(network);
    downloader->setRefererUrl(referer.toLocal8Bit());

}

Worker::~Worker()
{
    delete parser;
    delete spider;
    delete network;
}

void Worker::start()
{
    spider->start();
}

