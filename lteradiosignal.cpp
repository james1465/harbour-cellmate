#include "lteradiosignal.h"

LTERadioSignal::LTERadioSignal(QSharedPointer<QOfonoExtCell> cell, QObject *parent) : RadioSignal(cell, parent)
{
    this->pci = cell->pci();
}

const QOfonoExtCell::Type LTERadioSignal::RilType = QOfonoExtCell::LTE;

QString LTERadioSignal::getIdentifier() const {
    return QString("LTE-") + QString::number(this->pci);
    }

void LTERadioSignal::toJson(JSONLOutput& output) const
{
    if (!this->cell)
        return;
    output.addReport();
    output.addField("RAT", "LTE");
    output.addField("PCI", this->pci);
    output.addOptionalField("EARFCN", this->getEARFCN());
    output.addOptionalField("SignalStrength", this->getSignalStrength());
    output.addOptionalField("RSRP", this->getRSRP());
    output.addOptionalField("RSRQ", this->getRSRQ());
    output.addOptionalField("CI", this->getCI());
    output.addOptionalField("TAC", this->getTAC());
    output.endReport();

}

std::optional<int> LTERadioSignal::getPCI() const {
    return this->pci;
}

std::optional<int> LTERadioSignal::getRSRP() const {
    if (this->cell)
        return this->cell->rsrp();
    return std::nullopt;
}

std::optional<int> LTERadioSignal::getRSRQ() const {
    if (this->cell)
        return this->cell->rsrq();
    return std::nullopt;
}

std::optional<int> LTERadioSignal::getCI() const{
    if (this->cell && this->cell->ci() != INT_MAX)
    {
        return this->cell->ci();
    }
    return std::nullopt;
}

std::optional<int> LTERadioSignal::getTAC() const{
    if (this->cell && this->cell->tac() != INT_MAX)
    {
        return this->cell->tac();
    }
    return std::nullopt;
}

std::optional<int> LTERadioSignal::getEARFCN() const{
    if (this->cell)
    {
        return this->cell->earfcn();
    }
    return std::nullopt;
}

LTERadioSignal::~LTERadioSignal(){};
