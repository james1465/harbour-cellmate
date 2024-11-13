#ifndef NRRADIOSIGNAL_H
#define NRRADIOSIGNAL_H

#include <QObject>
#include <RadioSignal.h>
#include <qofonoext/qofonoext_types.h>

class NrRadioSignal:  public RadioSignal
{
    Q_OBJECT
public:
    explicit NrRadioSignal(QSharedPointer<QOfonoExtCell> cell,
                           QObject *parent = nullptr);
    virtual QString getIdentifier() const override;
    virtual void toJson(JSONLOutput& output) const override;

    std::optional<int> getPCI() const;
    std::optional<int> getTac() const;
    std::optional<QString> getNciString() const;
    std::optional<int> getNrarfcn() const;
    std::optional<int> getSsRsrp() const;
    std::optional<int> getSsRsrq() const;
    std::optional<int> getSsSinr() const;
    std::optional<int> getCsiRsrp() const;
    std::optional<int> getCsiRsrq() const;
    std::optional<int> getCsiSinr() const;

    ~NrRadioSignal();

signals:

private:
    int earfcn;
    int pci;

};

#endif // NRRADIOSIGNAL_H
