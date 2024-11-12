#include <QObject>
#include "ltecellwatcher.h"



LTECellWatcher::LTECellWatcher(CellWatcher* cellWatcher, QObject *parent) : TechSpecificListModel<LTERadioSignal>(cellWatcher, parent)
{
        connect(cellWatcher, &CellWatcher::newSignal, this, &LTECellWatcher::onNewSignal);
        connect(cellWatcher, &CellWatcher::signalChanged, this, &LTECellWatcher::onSignalChanged);
        qDebug() << "Listening for new Signal";
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(onPurge()));
        timer->start(1000);
}

void LTECellWatcher::onNewSignal(RadioSignal* newSignal)
{
    addNewSignal(newSignal);
}

void LTECellWatcher::onSignalChanged(RadioSignal* radioSignal)
{
    qDebug() << radioSignal;
    if (!radioSignal)
    {
        qDebug() << "Null pointer passed";
    }
    qDebug() << "LTE Watcher Handling change in " << radioSignal->getIdentifier();
    auto modelIndex = handleSignalChanged(radioSignal);
    if (modelIndex.isValid()) {
        qDebug() << "Data changed" << modelIndex.row();
            emit dataChanged(modelIndex,
                     modelIndex,
                     {PCIRole, RSRQRole, RSRPRole});
    }
    else
        qDebug() << "Invalid model index";
}

void LTECellWatcher::onPurge()
{
     this->deleteStaleSignals(QDateTime::currentMSecsSinceEpoch());
}


QHash<int, QByteArray> LTECellWatcher::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[EARFCNRole] = "EARFCN";
    roles[PCIRole] = "PCI";
    roles[RSRPRole] = "RSRP";
    roles[RSRQRole] = "RSRQ";
    roles[ServingRole] = "Serving";
    return roles;
}


QVariant LTECellWatcher::data(const QModelIndex &index, int role) const
{
    qDebug() << "Fetching Data For: " << role << " " << index.row();
    qDebug() << this->radio_signals->size();
    if (!index.isValid()) {
        return QVariant();
    }
    if (role == EARFCNRole) {
        return convertOptionalIntToString(this->radio_signals->at(index.row())->getEARFCN());
    }
    if (role == PCIRole) {
        return convertOptionalIntToString(this->radio_signals->at(index.row())->getPCI());
    }
    if (role == RSRPRole) {
        return convertOptionalIntToString(this->radio_signals->at(index.row())->getRSRP());
    }
    if (role == RSRQRole) {
        return convertOptionalIntToString(this->radio_signals->at(index.row())->getRSRQ());
    }
    if (role == ServingRole) {
        return QVariant(this->radio_signals->at(index.row())->isServing());
    }
    return QVariant();
}
