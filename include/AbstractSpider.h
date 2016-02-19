#ifndef ABSTRACTSPIDER_H
#define ABSTRACTSPIDER_H

#include "AbstractParser.h"
#include <QObject>
#include <QNetworkAccessManager>

class AbstractSpider : public QObject
{
    Q_OBJECT
public:
    virtual ~AbstractSpider();

    /**
     * @brief 开始和停止爬取任务
     */
    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;

    /**
     * @brief 设置和获取爬虫解析网页url的解析器类型
     * @return
     */
    virtual AbstractParser* parser() const = 0;
    virtual void setParser(AbstractParser* parser) = 0;

signals:

public slots:

protected:
    explicit AbstractSpider(QObject *parent = 0);

};

#endif // ABSTRACTSPIDER_H
