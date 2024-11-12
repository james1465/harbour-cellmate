#ifndef UMTSCELLWATCHER_H
#define UMTSCELLWATCHER_H

#include <optional>
#include <QObject>
#include <QStringListModel>
#include <CellWatcher.h>
#include <RadioSignal.h>
#include <wcdmaradiosignal.h>
#include <TechSpecificListModel.h>

class UMTSCellWatcher : public TechSpecificListModel<WcdmaRadioSignal>
{
    Q_OBJECT
public:
    explicit UMTSCellWatcher(CellWatcher* cellWatcher, QObject *parent = nullptr);

        enum UMTSWatcherRoles {
        PSCRole = Qt::UserRole + 1,
        UARFCNRole = Qt::UserRole + 2,
        SignalStrengthRole = Qt::UserRole + 3,
        ServingRole = Qt::UserRole + 4,
    };

    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:

public slots:
        void onNewSignal(RadioSignal* newSignal);
        void onSignalChanged(RadioSignal* radioSignal);
        void onPurge();

private:
    CellWatcher* cellWatcher;
};


#endif // UMTSCELLWATCHER_H
