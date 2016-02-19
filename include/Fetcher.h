#ifndef FETCHER_H
#define FETCHER_H

#include "AbstractSpider.h"
#include <QObject>
#include <QNetworkReply>

class Fetcher : public AbstractSpider
{
    Q_OBJECT
public:
    Fetcher(QObject *parent = 0);
    Fetcher(AbstractParser *parser, QObject *parent = 0);

    ~Fetcher();

    /**
     * @brief 开始和停止爬取任务
     */
    void start();
    void pause();
    void stop();

    /**
     * @brief 设置和获取爬虫解析网页url的解析器类型
     * @return
     */
    AbstractParser* parser() const;
    void setParser(AbstractParser* parser);

    void setStartUrl(const QUrl &url);

    QNetworkAccessManager* networkManager() const;
    void setNetworkManager(QNetworkAccessManager *manager);

private:
    inline QString logTime() const;
    void fetchNext();

signals:
    void finished();
    void logString(int type, const QString &logString);
    void fetchUpdated();

public slots:
    void loadHistory();

private slots:
    void fetchFinished();
    void replyError(QNetworkReply::NetworkError);
    void replySslErrors(QList<QSslError>);

private:
    AbstractParser* m_parser;
    QNetworkAccessManager* m_manager;
    QNetworkReply*  m_currentReply;
    bool            m_puase;
    bool            m_stop;
    QString         m_logString;
};

#endif // FETCHER_H
