#include "nrradiosignal.h"

NrRadioSignal::NrRadioSignal(QSharedPointer<QOfonoExtCell> cell, QObject *parent) : RadioSignal(cell, parent)
{
    this->earfcn = cell->earfcn();

}


QString NrRadioSignal::getIdentifier() const {
    return QString("NR-") + QString::number(cell->nrarfcn());
}

void NrRadioSignal::toJson(JSONLOutput& output) const {
    if (!this->cell)
        return;
    output.addReport();
    output.addField("RAT", "NR");
    output.addField("EARFCN", this->earfcn);
    output.endReport();

}

NrRadioSignal::~NrRadioSignal(){};
