#ifndef IMAGE_H
#define IMAGE_H

#include "global.h"
#include <QObject>
#include <QUrl>

class SPIDER_EXPORT Image : public QObject
{
    Q_OBJECT
public:
    enum State
    {
        Stopping,
        Preparing,
        WarmingUp,
        Downloading
    };
    explicit Image(QObject *parent = 0);

    QString getTitle() const;
    void setTitle(const QString &title);

    QUrl getUrl() const;
    void setUrl(const QUrl &url);

    QString getMd5() const;
    void setMd5(const QString &value);

    qint64 getTotalBytes() const;
    void setTotalBytes(const qint64 &totalBytes);

    qint64 getDownloadedBytes() const;
    void setDownloadedBytes(const qint64 &downloadedBytes);

    int getLastProgressValue() const;
    void setLastProgressValue(int lastProgressValue);

    int getDownloadRate() const;
    void setDownloadRate(int downloadRate);

    int getDownloadStatus() const;
    void setDownloadStatus(int downloadStatus);

    QString getLocalPath() const;
    void setLocalPath(const QString &localPath);

signals:
    void stateChanged(Image::State state);
    void downloadCompleted();
    void dataReceived(int downloadedBytes);
    void progressUpdated(int percentProgress);
    void downloadRateUpdated(int bytesPerSecond);
    void stopped();

public slots:

private:
    QString m_title;
    QUrl    m_url;
    QString m_localPath;
    QString md5;
    qint64  m_totalBytes;
    qint64  m_downloadedBytes;
    int     m_lastProgressValue;
    int     m_downloadRate;
    int     m_downloadStatus;
};

#endif // IMAGE_H
