#ifndef SPIDER_H
#define SPIDER_H

#include "global.h"
#include "DataQueue.h"
#include "Fetcher.h"
#include "Parser.h"
#include <QObject>
#include <QQueue>
#include <QMap>
#include <QTimer>

class SPIDER_EXPORT Spider : public QObject
{
    Q_OBJECT
public:
    explicit Spider(QObject *parent = 0);
    ~Spider();

    void setNetworkManager(QNetworkAccessManager *manager);
    void setStartupUrl(const QUrl &url);

    // 设置正则表达式匹配地址
    void setPageRegexpPattern(const QString &pattern);
    void setImageRegexpPattern(const QString &pattern);
    void setNextPageRegexpPatterns(const QStringList &patterns);

//    bool loadHistory(QQueue<QUrl> &urls, QMap<QString, QUrl> &images);

signals:
    void logString(int type, const QString &log);

public slots:
    void start(bool);
    void pause(bool);
    void stop(bool);
private:
    Fetcher*        m_fetcher;
    Parser*         m_parser;
};

#endif // SPIDER_H
