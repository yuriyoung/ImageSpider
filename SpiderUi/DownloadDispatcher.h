#ifndef DOWNLOADDISPATCHER_H
#define DOWNLOADDISPATCHER_H

#include <QObject>
#include "Image.h"
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class DownloadDispatcher : public QObject
{
    Q_OBJECT
public:
    DownloadDispatcher(QObject *parent = 0);
    ~DownloadDispatcher();

    void setDestination(QObject* destiantion);

signals:
    void dispatchImage(const QString &title, const QString &sizeString,
                       const QUrl &url);

public slots:
    void startDispatch(bool);
    void stopDispatch(bool);
    void dispatchNext();

private:
    void run();
    QString sizeWithUnit(qint64 bytes);
    void newImage(const QString &title, const QUrl &url);

private:
    bool    m_stop;
    int     m_limitCount;
    int     m_currentCount;

};

#endif // DOWNLOADDISPATCHER_H
