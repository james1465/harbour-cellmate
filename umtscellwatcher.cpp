#include <QObject>
#include "umtscellwatcher.h"



UMTSCellWatcher::UMTSCellWatcher(CellWatcher* cellWatcher, QObject *parent) : TechSpecificListModel<WcdmaRadioSignal>(cellWatcher, parent)
{
        connect(cellWatcher, &CellWatcher::newSignal, this, &UMTSCellWatcher::onNewSignal);
        connect(cellWatcher, &CellWatcher::signalChanged, this, &UMTSCellWatcher::onSignalChanged);
        qDebug() << "Listening for new Signal";
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(onPurge()));
        timer->start(1000);
}

void UMTSCellWatcher::onNewSignal(RadioSignal* newSignal)
{
    addNewSignal(newSignal);
}

void UMTSCellWatcher::onSignalChanged(RadioSignal* radioSignal)
{
    qDebug() << radioSignal;
    if (!radioSignal)
    {
        qDebug() << "Null pointer passed";
    }
    qDebug() << "UMTS Watcher Handling change in " << radioSignal->getIdentifier();
    auto modelIndex = handleSignalChanged(radioSignal);
    if (modelIndex.isValid()) {
        qDebug() << "Data changed" << modelIndex.row();
            emit dataChanged(modelIndex,
                     modelIndex,
                     {PSCRole, UARFCNRole, SignalStrengthRole});
    }
    else
        qDebug() << "Invalid model index";
}

void UMTSCellWatcher::onPurge()
{
     this->deleteStaleSignals(QDateTime::currentMSecsSinceEpoch());
}


QHash<int, QByteArray> UMTSCellWatcher::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PSCRole] = "PSC";
    roles[UARFCNRole] = "UARFCN";
    roles[SignalStrengthRole] = "SignalStrength";
    roles[ServingRole] = "Serving";
    return roles;
}


QVariant UMTSCellWatcher::data(const QModelIndex &index, int role) const
{
    qDebug() << "Fetching Data For: " << role << " " << index.row();
    qDebug() << this->radio_signals->size();
    if (!index.isValid()) {
        return QVariant();
    }
    if (role == PSCRole) {
        return convertOptionalIntToString(this->radio_signals->at(index.row())->getPSC());
    }
    if (role == UARFCNRole) {
        return convertOptionalIntToString(this->radio_signals->at(index.row())->getUARFCN());
    }
    if (role == SignalStrengthRole) {
        return convertOptionalIntToString(this->radio_signals->at(index.row())->getSignalStrength());
    }
    if (role == ServingRole) {
        return QVariant(this->radio_signals->at(index.row())->isServing());
    }
    return QVariant();
}
