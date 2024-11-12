#include "gsmcellwatcher.h"


GSMCellWatcher::GSMCellWatcher(CellWatcher* cellWatcher, QObject *parent) : TechSpecificListModel<GSMRadioSignal>(cellWatcher, parent)
{
        connect(cellWatcher, &CellWatcher::newSignal, this, &GSMCellWatcher::onNewSignal);
        connect(cellWatcher, &CellWatcher::signalChanged, this, &GSMCellWatcher::onSignalChanged);
        qDebug() << "Listening for new Signal";
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(onPurge()));
        timer->start(1000);
}

void GSMCellWatcher::onNewSignal(RadioSignal* newSignal)
{
    addNewSignal(newSignal);
}

void GSMCellWatcher::onSignalChanged(RadioSignal* radioSignal)
{
    qDebug() << radioSignal;
    if (!radioSignal)
    {
        qDebug() << "Null pointer passed";
    }
    else
    {
    qDebug() << "GSM Watcher Handling change in " << radioSignal->getIdentifier();
    auto modelIndex = handleSignalChanged(radioSignal);
    if (modelIndex.isValid()) {
        qDebug() << "Data changed" << modelIndex.row();
            emit dataChanged(modelIndex,
                     modelIndex,
                     {ARFCNRole, BSICRole, SignalStrengthRole});
    }
    else
        qDebug() << "Invalid model index";
    }
}

void GSMCellWatcher::onPurge()
{
     this->deleteStaleSignals(QDateTime::currentMSecsSinceEpoch());
}


QHash<int, QByteArray> GSMCellWatcher::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ARFCNRole] = "ARFCN";
    roles[BSICRole] = "BSIC";
    roles[SignalStrengthRole] = "SignalStrength";
    roles[ServingRole] = "Serving";
    return roles;
}


QVariant GSMCellWatcher::data(const QModelIndex &index, int role) const
{
    qDebug() << "Fetching Data For: " << role << " " << index.row();
    qDebug() << this->radio_signals->size();
    if (!index.isValid()) {
        return QVariant();
    }
    if (role == ARFCNRole) {
        return convertOptionalIntToString(this->radio_signals->at(index.row())->getArfcn());
    }
    if (role == BSICRole) {
        return convertOptionalIntToString(this->radio_signals->at(index.row())->getBsic());
    }
    if (role == SignalStrengthRole) {
        return convertOptionalIntToString(this->radio_signals->at(index.row())->getSignalStrength());
    }
    if (role == ServingRole) {
        return QVariant(this->radio_signals->at(index.row())->isServing());
    }
    return QVariant();
}
