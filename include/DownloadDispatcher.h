#ifndef DOWNLOADDISPATCHER_H
#define DOWNLOADDISPATCHER_H

#include "Downloader.h"
#include "DataQueue.h"

#include <QObject>
#include <QThread>

class DownloadDispatcher : public QThread
{
public:
    DownloadDispatcher(QObject *parent = 0);
    ~DownloadDispatcher();

    void setDestination(QObject* destiantion);

public slots:
    void startDispatch();
    void stopDispatch();

private:
    void run();

private:
    bool    m_stop;
};

#endif // DOWNLOADDISPATCHER_H
