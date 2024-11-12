#include "wcdmaradiosignal.h"

WcdmaRadioSignal::WcdmaRadioSignal(QSharedPointer<QOfonoExtCell> cell, QObject *parent) : RadioSignal(cell, parent)
{
    this->psc = cell->psc();
}

const QOfonoExtCell::Type WcdmaRadioSignal::RilType = QOfonoExtCell::WCDMA;


QString WcdmaRadioSignal::getIdentifier() const {
    return QString("WCDMA-") + QString::number(this->psc);
    }

void WcdmaRadioSignal::toJson(JSONLOutput& output) const
{
    if (!this->cell)
        return;
    output.addReport();
    output.addField("RAT", "UMTS");
    output.addField("PSC", this->psc);
    output.addOptionalField("UARFCN", this->getUARFCN());
    output.addOptionalField("LAC", this->getLac());
    output.addOptionalField("CID", this->getCid());
    output.addOptionalField("BER", this->getBitErrorRate());
    output.endReport();
}

std::optional<int> WcdmaRadioSignal::getPSC() const {
    return this->psc;
}

std::optional<int> WcdmaRadioSignal::getUARFCN() const {
    //TODO should this be part of the identifier
    if (this->cell)
        return this->cell->uarfcn();
    return std::nullopt;
}

std::optional<int> WcdmaRadioSignal::getLac() const
{
    if (this->cell && this->cell->lac() != INT_MAX)
        return cell->lac();
    return std::nullopt;
}

std::optional<int> WcdmaRadioSignal::getCid() const
{
    if (this->cell && this->cell->cid() != INT_MAX)
        return cell->cid();
    return std::nullopt;
}

std::optional<int> WcdmaRadioSignal::getBitErrorRate() const
{
    if (this->cell && this->cell->bitErrorRate() != INT_MAX)
        return cell->bitErrorRate();
    return std::nullopt;
}



WcdmaRadioSignal::~WcdmaRadioSignal(){};
