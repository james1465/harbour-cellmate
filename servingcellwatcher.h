#ifndef SERVINGCELLWATCHER_H
#define SERVINGCELLWATCHER_H

#include <QObject>
#include <QAbstractListModel>
#include "CellWatcher.h"
#include <optional>

class ServingCellWatcher : public QObject
{
    Q_OBJECT
    // All types:
    Q_PROPERTY(QString rat MEMBER rat NOTIFY ratChanged)
    Q_PROPERTY(QString mcc MEMBER mcc NOTIFY mccChanged);
    Q_PROPERTY(QString mnc MEMBER mnc NOTIFY mncChanged);
    Q_PROPERTY(QString signalStrength MEMBER signalStrength NOTIFY signalStrengthChanged);
    Q_PROPERTY(QString signalLevelDbm MEMBER signalLevelDbm NOTIFY signalLevelDbmChanged);

    // GSM:
    Q_PROPERTY(QString arfcn MEMBER arfcn NOTIFY arfcnChanged);
    Q_PROPERTY(QString bsic MEMBER bsic NOTIFY bsicChanged);

    // GSM and WCDMA:
    Q_PROPERTY(QString cid MEMBER cid NOTIFY cidChanged);
    Q_PROPERTY(QString lac MEMBER lac NOTIFY lacChanged);
    Q_PROPERTY(QString bitErrorRate MEMBER bitErrorRate NOTIFY bitErrorRateChanged);

    // WCDMA:
    Q_PROPERTY(QString psc MEMBER psc NOTIFY pscChanged);
    Q_PROPERTY(QString uarfcn MEMBER uarfcn NOTIFY uarfcnChanged);

    // LTE:
    Q_PROPERTY(QString ci MEMBER ci NOTIFY ciChanged);
    Q_PROPERTY(QString earfcn MEMBER earfcn NOTIFY earfcnChanged);
    Q_PROPERTY(QString rsrp MEMBER rsrp NOTIFY rsrpChanged);
    Q_PROPERTY(QString rsrq MEMBER rsrq NOTIFY rsrqChanged);
    Q_PROPERTY(QString rssnr MEMBER rssnr NOTIFY rssnrChanged);
    Q_PROPERTY(QString cqi MEMBER cqi NOTIFY cqiChanged);
    Q_PROPERTY(QString timingAdvance MEMBER timingAdvance NOTIFY timingAdvanceChanged);

    // LTE and NR:
    Q_PROPERTY(QString pci MEMBER pci NOTIFY pciChanged);
    Q_PROPERTY(QString tac MEMBER tac NOTIFY tacChanged);

    // NR:
    Q_PROPERTY(QString nciString MEMBER nciString NOTIFY nciStringChanged);
    Q_PROPERTY(QString nrarfcn MEMBER nrarfcn NOTIFY nrarfcnChanged);
    Q_PROPERTY(QString ssRsrp MEMBER ssRsrp NOTIFY ssRsrpChanged);
    Q_PROPERTY(QString ssRsrq MEMBER ssRsrq NOTIFY ssRsrqChanged);
    Q_PROPERTY(QString ssSinr MEMBER ssSinr NOTIFY ssSinrChanged);
    Q_PROPERTY(QString csiRsrp MEMBER csiRsrp NOTIFY csiRsrpChanged);
    Q_PROPERTY(QString csiRsrq MEMBER csiRsrq NOTIFY csiRsrqChanged);
    Q_PROPERTY(QString csiSinr MEMBER csiSinr NOTIFY csiSinrChanged);


public:
    explicit ServingCellWatcher(CellWatcher* watcher, QObject *parent = nullptr);

private:
    CellWatcher* watcher;
    std::optional<RadioSignal*> ServingSignal;
    void updateServingSignal(RadioSignal* rs);
    void clearServingCell();
    void updateCommonFields(RadioSignal* rs);
    void updateNRFields(RadioSignal* rs);
    void updateLTEFields(RadioSignal* rs);
    void updateUMTSFields(RadioSignal* rs);
    void updateGSMFields(RadioSignal* rs);

    // All types:
    QString rat;
    QString mcc;
    QString mnc;
    QString signalStrength;
    QString signalLevelDbm;

    // GSM:
    QString arfcn;
    QString bsic;

    // GSM and WCDMA:
    QString lac;
    QString cid;
    QString bitErrorRate;

    // WCDMA:
    QString psc;
    QString uarfcn;

    // LTE:
    QString ci;
    QString earfcn;
    QString rsrp;
    QString rsrq;
    QString rssnr;
    QString cqi;
    QString timingAdvance;

    // LTE and NR:
    QString pci;
    QString tac;

    // NR:
    QString nciString;
    QString nrarfcn;
    QString ssRsrp;
    QString ssRsrq;
    QString ssSinr;
    QString csiRsrp;
    QString csiRsrq;
    QString csiSinr;

signals:


    // All types:
    void ratChanged();
    void mccChanged();
    void mncChanged();
    void signalStrengthChanged();
    void signalLevelDbmChanged();

    // GSM:
    void arfcnChanged();
    void bsicChanged();

    // GSM and WCDMA:
    void lacChanged();
    void cidChanged();
    void bitErrorRateChanged();

    // WCDMA:
    void pscChanged();
    void uarfcnChanged();

    // LTE:
    void ciChanged();
    void earfcnChanged();
    void rsrpChanged();
    void rsrqChanged();
    void rssnrChanged();
    void cqiChanged();
    void timingAdvanceChanged();

    // LTE and NR:
    void pciChanged();
    void tacChanged();

    // NR:
    void nciStringChanged();
    void nrarfcnChanged();
    void ssRsrpChanged();
    void ssRsrqChanged();
    void ssSinrChanged();
    void csiRsrpChanged();
    void csiRsrqChanged();
    void csiSinrChanged();

public slots:
    void onNewSignal(RadioSignal* rs);
    void onSignalChanged(RadioSignal* rs);

};

#endif // SERVINGCELLWATCHER_H
