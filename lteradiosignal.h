#ifndef LTERADIOSIGNAL_H
#define LTERADIOSIGNAL_H

#include <optional>
#include <QObject>
#include<RadioSignal.h>
#include <qofonoext/qofonoext_types.h>

class LTERadioSignal : public RadioSignal
{
    Q_OBJECT
public:
    explicit LTERadioSignal(QSharedPointer<QOfonoExtCell> cell, QObject *parent = nullptr);
    static const QOfonoExtCell::Type RilType;
    virtual QString getIdentifier() const override;
    virtual void toJson(JSONLOutput& output) const override;
    std::optional<int> getPCI() const;
    std::optional<int> getRSRP() const;
    std::optional<int> getRSRQ() const;
    std::optional<int> getCI() const;
    std::optional<int> getTAC() const;
    std::optional<int> getEARFCN() const;
    ~LTERadioSignal();


signals:


private:
    int pci;

};


#endif // LTERADIOSIGNAL_H
