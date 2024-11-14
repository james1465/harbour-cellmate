#ifndef LOGRECORDER_H
#define LOGRECORDER_H

#include <QObject>
#include <jsonloutput.h>
#include <CellWatcher.h>
#include <locationprovider.h>

class LogRecorder: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRecording MEMBER isRecording NOTIFY recordingChanged)
    Q_PROPERTY(QString filename READ getFilename WRITE setFilename NOTIFY filenameChanged)
public:
    LogRecorder(CellWatcher* watcher, LocationProvider* locator);
    QString getFilename();
    void setFilename(QString fileName);

signals:
    void recordingChanged();
    void filenameChanged();

public slots:
    void startRecording();
    void stopRecording();
    void periodicRecord();



private:
    CellWatcher* watcher;
    LocationProvider* locator;
    bool isRecording = false;
    QString filename;
    QScopedPointer<JSONLOutput> logger;
    QTimer* timer;

};

#endif // LOGRECORDER_H
