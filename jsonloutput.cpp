#include "jsonloutput.h"
#include "qjsondocument.h"
#include "qdebug.h"


JSONLOutput::JSONLOutput(LocationProvider* locator, QObject* parent) :
    QObject(parent), locator(locator)
{
    logFile = new QTemporaryFile("CellMate_XXXXXX.jsonl", this);
    logStream.reset(new QTextStream(logFile));
    logFile->setAutoRemove(false);
}

QString JSONLOutput::getFilename()
{
    if (logFile->open())
        return logFile->fileName();
    return QString("No Log");
}

void JSONLOutput::addReport()
{
    currentReport.reset(new QJsonObject());
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");
    (*currentReport)["timestamp"] = formattedTime;
    (*currentReport)["latitude"] = locator->getLatitude();
    (*currentReport)["longitude"] = locator->getLongitude();
}

void JSONLOutput::endReport()
{
    QJsonDocument doc = QJsonDocument(*this->currentReport);

    QByteArray ba = doc.toJson(QJsonDocument::Compact);
    (*logStream) << ba << "\n";
    currentReport.reset();
}

void JSONLOutput::addField(QString name, QString value)
{
    (*currentReport)[name] = value;
}

void JSONLOutput::addField(QString name, int value)
{
    (*currentReport)[name] = QString::number(value);
}

void JSONLOutput::close(QString fileName)
{
    this->logStream->flush();
    this->logStream->reset();
    this->logFile->rename(fileName);
    qDebug() << "Saving as: " << fileName;
    this->logFile->close();
}

JSONLOutput::~JSONLOutput()
{

}
