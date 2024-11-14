#ifndef JSONLOUTPUT_H
#define JSONLOUTPUT_H

#include <QObject>
#include <QJsonObject>
#include <QtCore>
#include <locationprovider.h>

class JSONLOutput : QObject
{
public:
    JSONLOutput(LocationProvider* locator, QObject* parent);
    ~JSONLOutput();
    QString getFilename();
    void addReport();
    void endReport();
    void addField(QString name, QString value);
    void addField(QString name, int value);
    void close(QString filename);

    template<class T>
    void addOptionalField(QString name, std::optional<T> optionalValue)
    {
        if (optionalValue)
        addField(name, optionalValue.value());
    }

private:

    QScopedPointer<QJsonObject> currentReport;
    QTemporaryFile* logFile ;
    QScopedPointer<QTextStream> logStream;
    LocationProvider* locator;
};

#endif // JSONLOUTPUT_H
