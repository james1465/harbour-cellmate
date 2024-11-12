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
    ~NrRadioSignal();

signals:

private:
    int earfcn;

};

#endif // NRRADIOSIGNAL_H
