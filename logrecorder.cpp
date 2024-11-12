#include "logrecorder.h"

LogRecorder::LogRecorder(CellWatcher* watcher,
                         LocationProvider* locator)
    : watcher(watcher), locator(locator)
{
    timer = new QTimer(this); // let QT handle the destruction
    connect(timer, SIGNAL(timeout()), this, SLOT(periodicRecord()));
}

void LogRecorder::startRecording()
    {
    this->isRecording=true;
    emit recordingChanged();
    logger.reset(new JSONLOutput(locator, this));
        timer->start(1000);
    this->filename = logger->getFilename();
    qDebug() << "Logging to: " << this->filename;
    emit filenameChanged();
    }

void LogRecorder::stopRecording()
    {
    this->isRecording=false;
    emit recordingChanged();
    timer->stop();
    }

void LogRecorder::periodicRecord()
{
    this->watcher->logCells(*this->logger);

}
