#ifndef WCDMARADIOSIGNAL_H
#define WCDMARADIOSIGNAL_H

#include <QObject>
#include <RadioSignal.h>
#include <qofonoext/qofonoext_types.h>

class WcdmaRadioSignal : public RadioSignal
{
    Q_OBJECT
public:
    explicit WcdmaRadioSignal(QSharedPointer<QOfonoExtCell> cell, QObject *parent = nullptr);
    static const QOfonoExtCell::Type RilType;
    virtual QString getIdentifier() const override;
    virtual void toJson(JSONLOutput& output) const override;
    std::optional<int> getCI() const;
    std::optional<int> getRAC() const;
    std::optional<int> getPSC() const;
    std::optional<int> getUARFCN() const;
    std::optional<int> getLac() const;
    std::optional<int> getCid() const;
    std::optional<int> getBitErrorRate() const;
    ~WcdmaRadioSignal();

signals:

private:
    int psc;
};

#endif // WCDMARADIOSIGNAL_H
