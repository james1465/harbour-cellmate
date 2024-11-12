#ifndef LTECELLWATCHER_H
#define LTECELLWATCHER_H

#include <optional>
#include <QObject>
#include <QStringListModel>
#include <CellWatcher.h>
#include <RadioSignal.h>
#include <lteradiosignal.h>
#include <TechSpecificListModel.h>

class LTECellWatcher : public TechSpecificListModel<LTERadioSignal>
{
    Q_OBJECT
public:
    explicit LTECellWatcher(CellWatcher* cellWatcher, QObject *parent = nullptr);

        enum LTEWatcherRoles {
        EARFCNRole = Qt::UserRole + 1,
        PCIRole = Qt::UserRole + 2,
        RSRQRole = Qt::UserRole + 3,
        RSRPRole = Qt::UserRole + 4,
        ServingRole = Qt::UserRole + 5,
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


#endif // LTECELLWATCHER_H
