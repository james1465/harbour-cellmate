#ifndef CELLWATCHER_H
#define CELLWATCHER_H

#include <QCoreApplication>
#include <QDebug>


#include <qofonoext/qofonoext_types.h>
#include <qofonoext/qofonoextcellwatcher.h>
#include <QStringListModel>
#include <QMap>
#include <RadioSignal.h>

class CellWatcher: public QObject
{
    Q_OBJECT

public:
    explicit CellWatcher(QObject* aParent = nullptr);
    void logCells(JSONLOutput& output);
    virtual ~CellWatcher() {};


public Q_SLOTS:
    void onCellsChanged();
    void onCellChanged(QString aName, int aValue);
    void onSignalChanged();

signals:
    void newSignal(RadioSignal* newSignal);
    void signalChanged(RadioSignal* changedSignal);

private:
    QOfonoExtCellWatcher* iWatcher;
    QMap<QString, RadioSignal*> cellMap;
   };

#endif // CELLWATCHER_H
