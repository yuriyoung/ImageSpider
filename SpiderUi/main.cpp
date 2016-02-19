#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


//http://sexy.faceks.com/
//http://www.2xiezhen.com/meinvxiezhen/
//    m_startUrl = QUrl("http://sexy.faceks.com/?page=23");
//    m_startUrl = QUrl("http://www.2xiezhen.com/ribenmeinv/");
//    QString referer = "http://" + m_startUrl.host();
/*
QStringList nextPagePatterns;
nextPagePatterns << "<a\\s+class=[\"']next[\"'].*href=[\"']([^>]*page=\\d+.*)[\"']>"
                 << "<a\\s+href=['\"]([^['\"]+.html)['\"]>></a>"
                 << QString::fromUtf8("<a\\s+href=['\"]([^['\"]+.html)['\"]>下一.*</a>")
                 << "<a\\s+href=['\"]([^['\"]+.html)['\"]>Next</a>";

//http://sexy.faceks.com
QString rxUrlPattern = "<div\\s+class=['\"]pic['\"].*href=['\"]([^['\"]+)['\"].*>";
QString rxImgPattern = "bigimgsrc=[\"']([^'\"]+)['\"]";
*/
//http://www.2xiezhen.com
//    QString rxUrlPattern = "<li>\\s*<a.*href=['\\\"]([^['\\\"]+.html)['\\\"]\\s+target=.*/></a>";
//    QString rxImgPattern = "<a\\s+class=['\"]showpic['\"].*href=.*src=['\"]([^['\"]+.jpg)['\"]\\s*/>";


/*
m_network = new QNetworkAccessManager(this);
m_spider = new Spider;
m_parser = new Parser;
m_parser->setUrlRegexpPattern(rxUrlPattern);
m_parser->setImageRegexpPattern(rxImgPattern);
m_parser->setNextPageRegexpPatterns(nextPagePatterns);
m_parser->setRefererUrl(referer);

m_spider->setNetwokManager(m_network);
m_spider->setParser(m_parser);
m_spider->setStartUrl(m_startUrl);

// download images
m_downloader = new Downloader;
m_downloader->setNetwokManager(m_network);
m_downloader->setRefererUrl(referer.toLocal8Bit());

connect(ui->startButton, SIGNAL(pressed()), this, SLOT(start()));
connect(ui->stopButton, SIGNAL(pressed()), this, SLOT(stop()));

QTimer::singleShot(2000, m_spider, SLOT(loadHistory()));

*/
