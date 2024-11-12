#ifndef GSMCELLWATCHER_H
#define GSMCELLWATCHER_H

#include <optional>
#include <QObject>
#include <QStringListModel>
#include <CellWatcher.h>
#include <RadioSignal.h>
#include <gsmradiosignal.h>
#include <TechSpecificListModel.h>


class GSMCellWatcher : public TechSpecificListModel<GSMRadioSignal>
{
    Q_OBJECT
public:
    explicit GSMCellWatcher(CellWatcher* cellWatcher, QObject *parent = nullptr);

        enum GSMWatcherRoles {
        ARFCNRole = Qt::UserRole + 1,
        BSICRole = Qt::UserRole + 2,
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



#endif // GSMCELLWATCHER_H

