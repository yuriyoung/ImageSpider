#include "Image.h"
#include <QDebug>


Image::Image(QObject *parent) :
    QObject(parent)
{
    progress = 0;
}

void Image::setState(Image::State state)
{
    this->state = state;
    switch (state)
    {
    case Image::Stopping:
        stateString = QT_TRANSLATE_NOOP(Image, "Stopping");
        break;
    case Image::Paused:
        stateString = QT_TRANSLATE_NOOP(Image, "Paused");
        break;
    case Image::Preparing:
        stateString = QT_TRANSLATE_NOOP(Image, "Preparing");
        break;
    case Image::WarmingUp:
        stateString = QT_TRANSLATE_NOOP(Image, "Warming up");
        break;
    case Image::Downloading:
        stateString = QT_TRANSLATE_NOOP(Image, "Downloading");
        break;
    case Image::Finished:
        stateString = QT_TRANSLATE_NOOP(Image, "Finished");
        break;
    }
    emit stateChanged();
}

void Image::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
//    Image* image = qobject_cast<Image*>(sender());
    double speed = bytesReceived * 1000.0 / progressTime.elapsed();
    QString unit;
    if (speed < 1024)
    {
        unit = "bytes/sec";
    }
    else if (speed < 1024*1024)
    {
        speed /= 1024;
        unit = "KB/s";
    }
    else
    {
        speed /= 1024*1024;
        unit = "MB/s";
    }

    downloadRate = QString::fromLatin1("%1 %2").arg(speed, 3, 'f', 1).arg(unit);
    int percent = bytesReceived * 100 / bytesTotal;
    progress = percent;

    emit downloadRateUpdated();
    emit progressUpdated();

    if( progress == 100 )
    {
        setState(Image::Finished);
    }
}
