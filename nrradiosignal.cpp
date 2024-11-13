#include "nrradiosignal.h"

NrRadioSignal::NrRadioSignal(QSharedPointer<QOfonoExtCell> cell, QObject *parent) : RadioSignal(cell, parent)
{
    this->earfcn = cell->earfcn();
    this->pci = cell->pci();
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

std::optional<int> NrRadioSignal::getPCI() const {
    return this->pci;
}


std::optional<int> NrRadioSignal::getTac() const{
    if (this->cell)
        return this->cell->tac();
    return std::nullopt;
}

std::optional<QString> NrRadioSignal::getNciString() const{
    if (this->cell)
        return this->cell->nciString();
    return std::nullopt;
}

std::optional<int> NrRadioSignal::getNrarfcn() const{
    if (this->cell)
        return this->cell->nrarfcn();
    return std::nullopt;
}

std::optional<int> NrRadioSignal::getSsRsrp() const{
    if (this->cell)
        return this->cell->ssRsrp();
    return std::nullopt;
}

std::optional<int> NrRadioSignal::getSsRsrq() const{
    if (this->cell)
        return this->cell->ssRsrq();
    return std::nullopt;
}

std::optional<int> NrRadioSignal::getSsSinr() const{
    if (this->cell)
        return this->cell->ssSinr();
    return std::nullopt;
}

std::optional<int> NrRadioSignal::getCsiRsrp() const{
    if (this->cell)
        return this->cell->csiRsrp();
    return std::nullopt;
}

std::optional<int> NrRadioSignal::getCsiRsrq() const{
    if (this->cell)
        return this->cell->csiRsrq();
    return std::nullopt;
}

std::optional<int> NrRadioSignal::getCsiSinr() const{
    if (this->cell)
        return this->cell->csiSinr();
    return std::nullopt;
}

NrRadioSignal::~NrRadioSignal(){};
