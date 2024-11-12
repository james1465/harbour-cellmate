#include <QObject>

template<typename T>
TechSpecificListModel::TechSpecificListModel(CellWatcher* watcher, QObject *parent)
    : QAbstractListModel(parent),
      cellWatcher(watcher),
      radio_signals(new QList<T*>())
{

    connect(watcher, &CellWatcher::newSignal, this, &LTECellWatcher::onNewSignal);
    qDebug() << "Listening for new LTE Cells";


}

void LTECellWatcher::onNewSignal(RadioSignal* newSignal)
{
    qDebug() << "New Signal" << newSignal->getIdentifier();
    if (newSignal->type() == QOfonoExtCell::LTE)
        {
        LTERadioSignal* lte_signal = static_cast<LTERadioSignal*>(newSignal);
        auto row_count = lte_signals->size();
        this->beginInsertRows(QModelIndex(), row_count, row_count);
        lte_signals->append(lte_signal);
        endInsertRows();
        }
}


int LTECellWatcher::rowCount(const QModelIndex&) const
{
    return lte_signals->size();
}


QHash<int, QByteArray> LTECellWatcher::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PCIRole] = "PCI";
    roles[RSRPRole] = "RSRP";
    roles[RSRQRole] = "RSRQ";
    roles[ServingRole] = "Serving";
    return roles;
}



QVariant LTECellWatcher::data(const QModelIndex &index, int role) const
{
    qDebug() << "Fetching Data For: " << role << " " << index.row();
    if (!index.isValid()) {
        return QVariant();
    }
    if (role == PCIRole) {
        return QVariant(this->lte_signals->at(index.row())->getIdentifier());
    }
    if (role == RSRPRole) {
        return QVariant(this->lte_signals->at(index.row())->getIdentifier());
    }
    if (role == RSRQRole) {
        return QVariant(this->lte_signals->at(index.row())->getIdentifier());
    }
    if (role == ServingRole) {
        return QVariant(this->lte_signals->at(index.row())->getIdentifier());
    }
    return QVariant();
}
