#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include "DataQueue.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QTimer>
#include <QThread>

class Downloader : public QObject
{
    Q_OBJECT
public:
    Downloader(QObject *parent = 0);
    ~Downloader();

    /**
     * @brief 开始和停止爬取任务
     */
    void startDownload();
    void stopDownload();

    /**
     * @brief 设置和获取爬虫的网络组件
     * @return
     */
    QNetworkAccessManager* networkManager() const;
    void setNetwokManager(QNetworkAccessManager *networkManager);

    QString referer() const;
    void setReferer(const QString &referer);

    QString downloadPath() const;
    void setDownloadPath(const QString &downloadPath);

    void setLimitDownloading(int max);
    int limitDowndloading() const;
    int downloadedCount() const;
    inline QString logTime() const;

    int currentDownloadCount() const;

private:
    void download(const Url &myUrl);
    QString saveFileName(const QUrl &url);

signals:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void logString(int type, const QString &logString);

public slots:
    void downloadNext();

private slots:
    void downloadReadyRead();
    void downloadFinished();

private:
    QNetworkAccessManager*  m_network;
    QMap<QNetworkReply*, QFile*> m_currentDownloads;
    QTime       m_progressTime;
    QTimer      m_downloadTimer;

    QString     m_referer;
    QString     m_downloadPath;
    QString     m_logString;
    int         m_downloadedCount;

    int         m_maxDownloading;
    int         m_currentDownloadCount;
    bool        m_stop;
};

#endif // DOWNLOADER_H
