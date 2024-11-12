#ifndef RADIOSIGNAL_H
#define RADIOSIGNAL_H

#include <qofonoext/qofonoext_types.h>
#include <qofonoext/qofonoextcellwatcher.h>
#include <QObject>
#include <jsonloutput.h>

class RadioSignal : public QObject
{
    Q_OBJECT
public:
    explicit RadioSignal(QSharedPointer<QOfonoExtCell> cell,
                         QObject *parent = nullptr);
    void setCell(QSharedPointer<QOfonoExtCell> cell);
    QSharedPointer<QOfonoExtCell> getCell();
    void clearCell();
    void expectUpdate();
    void clearIfNotUpdated();
    bool isServing() const;
    bool isRIL() const;
    QOfonoExtCell::Type type();
    virtual QString getIdentifier() const =0;
    virtual void toJson(JSONLOutput& output) const =0;
    qint64 last_report;

    std::optional<int> getMNC() const;
    std::optional<int> getMCC() const;
    std::optional<int> getSignalStrength() const;
    std::optional<int> getSignalLevelDbm() const;

    virtual ~RadioSignal();

protected:
    QSharedPointer<QOfonoExtCell> cell;

public slots:
    void onCellChanged(QString aName, int aValue);

signals:
    void rilCellChanged();
    void servingStatusChanged();

private:
    bool updateExpected=false;
    bool serving=false;
};



#endif // RADIOSIGNAL_H
