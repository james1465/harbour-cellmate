#include "gsmradiosignal.h"

GSMRadioSignal::GSMRadioSignal(QSharedPointer<QOfonoExtCell> cell, QObject *parent) : RadioSignal(cell, parent)
{
    this->arfcn = cell->arfcn();
    this->bsic = cell->bsic();
}

const QOfonoExtCell::Type GSMRadioSignal::RilType = QOfonoExtCell::GSM;

QString GSMRadioSignal::getIdentifier() const {
    return QString("GSM-") + QString::number(this->arfcn) + QString("-") + QString::number(this->bsic) ;
    }

void GSMRadioSignal::toJson(JSONLOutput& output) const
{
    if (!this->cell)
        return;
    output.addReport();
    output.addField("RAT", "GSM");
    output.addField("BSIC", this->bsic);
    output.addField("ARFCN", this->arfcn);
    output.addOptionalField("SignalStrength", this->getSignalStrength());
    output.addOptionalField<int>("ARFCN", this->getLac());
    output.addOptionalField<int>("CID", this->getCid());
    output.addOptionalField<int>("BitErrorRate", this->getBitErrorRate());
    output.endReport();
}


std::optional<int> GSMRadioSignal::getArfcn() const
{
    return this->arfcn;
}

std::optional<int> GSMRadioSignal::getBsic() const
{
    return this->bsic;
}

std::optional<int> GSMRadioSignal::getLac() const
{
    if (this->cell && this->cell->lac() != INT_MAX)
        return cell->lac();
    return std::nullopt;
}

std::optional<int> GSMRadioSignal::getCid() const
{
    if (this->cell && this->cell->cid() != INT_MAX)
        return cell->cid();
    return std::nullopt;
}

std::optional<int> GSMRadioSignal::getBitErrorRate() const
{
    if (this->cell && this->cell->bitErrorRate() != INT_MAX)
        return cell->bitErrorRate();
    return std::nullopt;
}


GSMRadioSignal::~GSMRadioSignal(){};
