#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

#include <QObject>

class AbstractParser : public QObject
{
    Q_OBJECT
public:
    virtual ~AbstractParser();

    /**
     * @brief 设置解析页面的url的正则匹配
     * @param pattern 正则表达式
     */
    virtual void setUrlRegexpPattern(const QString &pattern) = 0;
    virtual QString urlRegexpPattern() const = 0;

    /**
     * @brief 设置解析图片的url的正则匹配
     * @param pattern 正则表达式
     */
    virtual void setImageRegexpPattern(const QString &pattern) = 0;
    virtual QString imageRegexpPattern() const = 0;

    /**
     * @brief 设置下一页的标签，下一页的标签类型可能有多种
     *      如："下一页" "next" ">"
     * @return
     */
    virtual QStringList nextPageRegexpPatterns() const = 0;
    virtual void setNextPageRegexpPatterns(const QStringList &nextPatterns) = 0;

    /**
     * @brief 解析页面的url
     * @param html输入页面的html内容
     * @return
     */
    virtual void parserUrl(const QByteArray &html) = 0;

    /**
     * @brief 解析下一页标签，并抓取其下一页的连接
     * @param html
     */
    virtual void parserNextPage(const QByteArray &html) = 0;

    /**
     * @brief 解析图片的url
     * @param html输入页面的html内容
     * @return
     */
    virtual void parserImage(const QByteArray &html) = 0;

    /**
     * @brief 设置页面引用地址
     * @return
     */
    virtual QString referer() const = 0;
    virtual void setReferer(const QString &referer) = 0;

signals:

public slots:

protected:
    explicit AbstractParser(QObject *parent = 0);

};

#endif // ABSTRACTPARSER_H
