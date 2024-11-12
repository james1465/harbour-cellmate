#include <CellWatcher.h>
#include <QStringListModel>
#include <RadioSignal.h>
#include <lteradiosignal.h>
#include <wcdmaradiosignal.h>
#include <gsmradiosignal.h>
#include <nrradiosignal.h>

//https://doc.qt.io/qt-6/model-view-programming.html

CellWatcher::CellWatcher(QObject* aParent) :
    QObject(aParent),
    iWatcher(new QOfonoExtCellWatcher(this))
{
    connect(iWatcher, SIGNAL(cellsChanged()), SLOT(onCellsChanged()));
    cellMap = QMap<QString, RadioSignal*> {};
    // Add child objects with a list of GSM UMTS and LTE cells
}

void CellWatcher::onCellsChanged()
{
    RadioSignal* rs;

    for (auto signal : cellMap) {
        signal->expectUpdate();
    }


    for (auto cell : iWatcher->cells())
    {
        switch (cell->type()) {
            case QOfonoExtCell::GSM:
                rs = new GSMRadioSignal {cell, this};
                break;
            case QOfonoExtCell::WCDMA:
                rs = new WcdmaRadioSignal {cell, this};
                break;
            case QOfonoExtCell::LTE:
                rs = new LTERadioSignal {cell, this};
                break;
            case QOfonoExtCell::NR:
                rs = new NrRadioSignal {cell, this};
                break;
            case QOfonoExtCell::Unknown:
                continue;
        }
        if (cellMap.contains(rs->getIdentifier()))
        {
            qDebug() << "Cell " << rs->getIdentifier() << " already detected";
            cellMap[rs->getIdentifier()]->setCell(cell);
            delete rs;
        }
        else {
            cellMap.insert(rs->getIdentifier() , rs);
            connect(rs, &RadioSignal::rilCellChanged, this, &CellWatcher::onSignalChanged);
            qDebug() << "New Cell " << rs->getIdentifier() << " reported";
            emit newSignal(rs);
        }
    }

    for (auto signal : cellMap) {
        signal->clearIfNotUpdated();
    }
}

void CellWatcher::onCellChanged(QString aName, int aValue)
{
    QOfonoExtCell* cell = (QOfonoExtCell*)sender();
    qDebug() << cell->path() << aName << "=>" << aValue;

}


void CellWatcher::logCells(JSONLOutput& logger)
{
    for (auto signal : cellMap) {
        signal->toJson(logger);
    }

}


void CellWatcher::onSignalChanged()
{
    RadioSignal* radio_signal= qobject_cast<RadioSignal *>(sender());
    emit signalChanged(radio_signal);
}



