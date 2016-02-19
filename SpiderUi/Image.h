#ifndef IMAGE_H
#define IMAGE_H

#include <QObject>
#include <QUrl>
#include <QTime>

class Image :public QObject
{
    Q_OBJECT
public:
    enum State
    {
        Stopping,
        Paused,
        Preparing,
        WarmingUp,
        Downloading,
        Finished
    };

    Image(QObject *parent = 0);

    void setState(Image::State state);

signals:
    void stateChanged();
    void downloadCompleted();

    void progressUpdated();
    void downloadRateUpdated();
    void stopped();

public slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

public:
    QString folder;
    QString name;
    QUrl    url;
    QString localFile;
    QString md5;
    QString downloadRate;
    QString stateString;
    State   state;
    QString size;
    int     progress;
    QTime   progressTime;
};
#endif // IMAGE_H
