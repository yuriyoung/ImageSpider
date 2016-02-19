#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include "Image.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QTimer>
#include <QQueue>

class Downloader : public QObject
{
    Q_OBJECT
public:
    Downloader(QObject *parent = 0);
    ~Downloader();

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
    QString saveFileName(const QUrl &url);

signals:
    void logString(int type, const QString &logString);
    void downloadOnefinished();

public slots:
    void startDownload();
    void stopDownload();
    void download(Image *image);

private slots:
    void downloadReadyRead();
    void downloadFinished();
    void downloadNext();

private:
    QNetworkAccessManager*  m_network;
    QMap<QNetworkReply*, QFile*> m_currentDownloads;
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
