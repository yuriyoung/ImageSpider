#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "Fetcher.h"
#include "Parser.h"
#include "DataQueue.h"
#include "Downloader.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);
    ~Worker();

    void start();

signals:

public slots:

private:
    QUrl startUrl;
    QNetworkAccessManager* network;
    Spider* spider;
    Parser* parser;
    Downloader* downloader;
};

#endif // WORKER_H
