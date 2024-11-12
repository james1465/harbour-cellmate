#ifndef TECHSPECIFICLISTMODEL_H
#define TECHSPECIFICLISTMODEL_H
#include "optional"
#include <QObject>
#include "QString"
#include <QStringListModel>
#include <CellWatcher.h>
#include <RadioSignal.h>

template <typename T>
class TechSpecificListModel : public QAbstractListModel
{

public:
    explicit TechSpecificListModel(CellWatcher* watcher, QObject* parent = nullptr)
           : QAbstractListModel(parent),
             cellWatcher(watcher),
             radio_signals(new QList<T*>())
    {
    }

    int rowCount(const QModelIndex&) const override
    {
        return radio_signals->size();
    }

    void addNewSignal(RadioSignal* newSignal)
    {
        qDebug() << "New Signal" << newSignal->getIdentifier();
        if (newSignal->type() == T::RilType)
            {
            T* radio_signal = static_cast<T*>(newSignal);
            auto row_count = radio_signals->size();
            this->beginInsertRows(QModelIndex(), row_count, row_count);
            radio_signals->append(radio_signal);
            endInsertRows();
            }
    }

    QModelIndex handleSignalChanged(RadioSignal* sender) {
        // Find the signal that triggered the signal.
        if (sender->type() == T::RilType)
        {
            T *radio_signal = qobject_cast<T *>(sender);
            if (!radio_signal)
                return QModelIndex(); // TODO  - return a null;
            int index = radio_signals->indexOf(radio_signal);
            if (index != -1) {
                QModelIndex modelIndex = createIndex(index, 0);
                return modelIndex;
            }
            else
            {
                addNewSignal(sender);
                return QModelIndex();
            }
            return QModelIndex();
        }
        return QModelIndex();
    }

    QVariant convertOptionalIntToString(std::optional<int> maybeInt) const
    {
        if (maybeInt.has_value())
                return QVariant(QString::number(maybeInt.value()));
        return QVariant(QString("-"));
    }

    void deleteStaleSignals(qint64 time_now)
    {
       auto cutoff = time_now - 10000;
       auto toDelete = QSharedPointer<QList<int>>{new QList<int>()};
       for (T* rs : *this->radio_signals)
       {
           if (rs->last_report < cutoff && !rs-> isRIL())
           {
               qDebug() << "Removing: " << rs->last_report;
               int row = radio_signals->indexOf(rs);
               beginRemoveRows(QModelIndex(), row, row);
               this->radio_signals->removeAt(row);
               endRemoveRows();
           }
       }
    }

protected:
    CellWatcher* cellWatcher;
    QScopedPointer<QList<T*>> radio_signals;
};


#endif // TECHSPECIFICLISTMODEL_H
