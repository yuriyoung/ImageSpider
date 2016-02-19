#ifndef PARSER_H
#define PARSER_H

#include "AbstractParser.h"
#include <QObject>

class Parser : public AbstractParser
{
    Q_OBJECT
public:
    Parser(QObject *parent = 0);
    ~Parser();

    /**
     * @brief 设置解析页面的url的正则匹配
     * @param pattern 正则表达式
     */
    void setUrlRegexpPattern(const QString &pattern);
    QString urlRegexpPattern() const;


    /**
     * @brief 设置解析图片的url的正则匹配
     * @param pattern 正则表达式
     */
    void setImageRegexpPattern(const QString &pattern);
    QString imageRegexpPattern() const;

    /**
     * @brief 设置下一页的标签，下一页的标签类型可能有多种
     *      如："下一页" "next" ">"
     * @return
     */
    QStringList nextPageRegexpPatterns() const;
    void setNextPageRegexpPatterns(const QStringList &nextPatterns);

    /**
     * @brief 解析页面的url
     * @param html输入页面的html内容
     * @return
     */
    void parserUrl(const QByteArray &html);

    /**
     * @brief 解析下一页标签，并抓取其下一页的连接
     * @param html
     */
    void parserNextPage(const QByteArray &html);

    /**
     * @brief 解析图片的url
     * @param html输入页面的html内容
     * @return
     */
    void parserImage(const QByteArray &html);

    /**
     * @brief 设置页面引用地址(部分网站使用的是相对地址，需要补充完整地址)
     * @return
     */
    QString referer() const;
    void setReferer(const QString &referer);


private:
    QString parserTitle(const QByteArray &html);

private:
    QString     m_urlPattern;
    QStringList m_nextPatterns;
    QString     m_imagePattern;
    QString     m_referer;
};

#endif // PARSER_H
