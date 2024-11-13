#include "servingcellwatcher.h"
#include "nrradiosignal.h"
#include "lteradiosignal.h"
#include "wcdmaradiosignal.h"
#include "gsmradiosignal.h"

ServingCellWatcher::ServingCellWatcher(CellWatcher* watcher, QObject *parent) :
    QObject(parent),
    watcher(watcher)
{
    connect(watcher, &CellWatcher::newSignal, this, &ServingCellWatcher::onNewSignal);
    connect(watcher, &CellWatcher::signalChanged, this, &ServingCellWatcher::onSignalChanged);
    qDebug() << "Listening for new Signal";
}



void ServingCellWatcher::onNewSignal(RadioSignal* rs)
{
    if (rs->isServing())
        {
            updateServingSignal(rs);
        }
}

void ServingCellWatcher::clearServingCell()
{

}

void ServingCellWatcher::updateCommonFields(RadioSignal* rs)
{
    this->mcc = QString::number(rs->getMCC().value());
    this->mnc = QString::number(rs->getMNC().value());
    this->signalStrength = QString::number(rs->getSignalStrength().value());
    this->signalLevelDbm = QString::number(rs->getSignalLevelDbm().value());
    emit mccChanged();
    emit mncChanged();
    emit signalStrengthChanged();
    emit signalLevelDbmChanged();
}

void ServingCellWatcher::updateNRFields(RadioSignal* rs)
{
    qDebug("Updating Serving Cell Fields to NR");
    this->rat = QString("NR");
    updateCommonFields(rs);
    NrRadioSignal* nrs = qobject_cast<NrRadioSignal*>(rs);
    // LTE and NR:
    this->pci = QString::number(nrs->getPCI().value());
    this->tac = QString::number(nrs->getTac().value());
    // NR:
    this->nciString = nrs->getNciString().value();
    this->nrarfcn = QString::number(nrs->getNrarfcn().value());
    this->ssRsrp = QString::number(nrs->getSsRsrp().value());
    this->ssRsrq = QString::number(nrs->getSsRsrq().value());
    this->ssSinr = QString::number(nrs->getSsSinr().value());
    this->csiRsrp = QString::number(nrs->getCsiRsrp().value());
    this->csiRsrq = QString::number(nrs->getCsiRsrq().value());
    this->csiSinr = QString::number(nrs->getCsiSinr().value());
    emit pciChanged();
    emit tacChanged();
    emit nciStringChanged();
    emit nrarfcnChanged();
    emit ssRsrpChanged();
    emit ssRsrqChanged();
    emit ssSinrChanged();
    emit csiRsrpChanged();
    emit csiRsrqChanged();
    emit csiSinrChanged();
}

void ServingCellWatcher::updateLTEFields(RadioSignal* rs)
{
    qDebug("Updating Serving Cell Fields to LTE");
    this->rat = QString("LTE");
    updateCommonFields(rs);
    LTERadioSignal* lrs = qobject_cast<LTERadioSignal*>(rs);
    this->ci = QString::number(lrs->getCI().value());
    this->tac = QString::number(lrs->getTAC().value());
    this->mcc = QString::number(lrs->getMCC().value());
    this->mnc = QString::number(lrs->getMNC().value());
    this->pci = QString::number(lrs->getPCI().value());
    this->rsrp = QString::number(lrs->getRSRP().value());
    this->rsrq = QString::number(lrs->getRSRQ().value());
    this->earfcn = QString::number(lrs->getEARFCN().value());
    emit ratChanged();
    emit ciChanged();
    emit tacChanged();
    emit mccChanged();
    emit mncChanged();
    emit pciChanged();
    emit rsrpChanged();
    emit rsrqChanged();
    emit earfcnChanged();
}

void ServingCellWatcher::updateUMTSFields(RadioSignal* rs)
{
   this->rat = QString("UMTS");
    updateCommonFields(rs);
    WcdmaRadioSignal * wrs = qobject_cast<WcdmaRadioSignal*>(rs);
    this->psc = QString::number(wrs->getPSC().value());
    this->uarfcn = QString::number(wrs->getUARFCN().value());
    this->lac = QString::number(wrs->getLac().value());
    this->cid = QString::number(wrs->getCid().value());
    this->bitErrorRate = QString::number(wrs->getBitErrorRate().value());
    emit ratChanged();
    emit pscChanged();
    emit uarfcnChanged();
    emit lacChanged();
    emit cidChanged();
    emit bitErrorRateChanged();

}

void ServingCellWatcher::updateGSMFields(RadioSignal* rs)
{
    this->rat = QString("GSM");
    updateCommonFields(rs);
    GSMRadioSignal * grs = qobject_cast<GSMRadioSignal*>(rs);
    this->arfcn = QString::number(grs->getArfcn().value());
    this->bsic = QString::number(grs->getBsic().value());
    this->lac = QString::number(grs->getLac().value());
    this->cid = QString::number(grs->getCid().value());
    this->bitErrorRate = QString::number(grs->getBitErrorRate().value());
    emit ratChanged();
    emit arfcnChanged();
    emit bsicChanged();
    emit lacChanged();
    emit cidChanged();
    emit bitErrorRateChanged();
}


void ServingCellWatcher::onSignalChanged(RadioSignal* rs)
{
    if (rs->isServing())
    {
        if (!this->ServingSignal || rs != this->ServingSignal)
        {
            clearServingCell();
            updateServingSignal(rs);
        }
        else
        {
            updateServingSignal(rs);
        }
    }
    else
    {
        if (this->ServingSignal && rs == this->ServingSignal)
        {
            clearServingCell();
        }
    }
}

void ServingCellWatcher::updateServingSignal(RadioSignal* rs)
{
    this->ServingSignal = rs;
    qDebug() << "Reporting on Serving Cell" << rs;
    switch (rs->type()) {
        case QOfonoExtCell::GSM:
            updateGSMFields(rs);
        break;
        case QOfonoExtCell::WCDMA:
            updateUMTSFields(rs);
        break;
        case QOfonoExtCell::LTE:
            updateLTEFields(rs);
        break;
        case QOfonoExtCell::NR:
            updateNRFields(rs);
        break;
        case QOfonoExtCell::Unknown:
            qDebug() << "Unexpected cell type";
            clearServingCell();
        default:
            qDebug() << "Unexpected cell type";
            clearServingCell();
    }


    }

