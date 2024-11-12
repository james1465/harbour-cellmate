#ifndef GSMRADIOSIGNAL_H
#define GSMRADIOSIGNAL_H

#include <QObject>
#include <RadioSignal.h>
#include <qofonoext/qofonoext_types.h>
#include <jsonloutput.h>

class GSMRadioSignal : public RadioSignal
{
Q_OBJECT
public:
    explicit GSMRadioSignal(QSharedPointer<QOfonoExtCell> cell, QObject *parent = nullptr);
    static const QOfonoExtCell::Type RilType;
    virtual QString getIdentifier() const override;
    virtual void toJson(JSONLOutput& output) const override;
    std::optional<int> getArfcn() const;
    std::optional<int> getBsic() const;
    std::optional<int> getLac() const;
    std::optional<int> getCid() const;
    std::optional<int> getBitErrorRate() const;
    ~GSMRadioSignal();

signals:

private:
    int arfcn;
    int bsic;
};

#endif // GSMRADIOSIGNAL_H
