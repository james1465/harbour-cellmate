#include "RadioSignal.h"

RadioSignal::RadioSignal(QSharedPointer<QOfonoExtCell> cell,
                         QObject *parent) :QObject(parent), cell(cell)
{
    this->last_report=QDateTime::currentMSecsSinceEpoch();

}

void RadioSignal::setCell(QSharedPointer<QOfonoExtCell> cell)
{
    if (cell != this->cell)
    {
    if (this->cell != nullptr)
        this->cell->disconnect(this);
    this->cell = cell;
    this->updateExpected=false;
    emit rilCellChanged();
    connect(cell.data(), &QOfonoExtCell::propertyChanged, this, &RadioSignal::onCellChanged);
    this->last_report = QDateTime::currentMSecsSinceEpoch();
    }
    this->updateExpected = false;
}

QSharedPointer<QOfonoExtCell> RadioSignal::getCell()
{
    return this->cell;
}


void RadioSignal::clearCell()
{
    if (serving)
    {
        serving=false;
        emit servingStatusChanged();
    }
    if (this->cell){
        this->cell->disconnect(this);
        this->cell = QSharedPointer<QOfonoExtCell>();
        this->updateExpected=false;
        this->last_report = QDateTime::currentMSecsSinceEpoch();
        emit rilCellChanged();
    }
}

void RadioSignal::expectUpdate()
{
    this->updateExpected=true;
}

void RadioSignal::clearIfNotUpdated()
{
   if (updateExpected)
   {
       qDebug() << "Cell: " << this->getIdentifier() << " not reported in this update";
       this->clearCell();
   }
}

bool RadioSignal::isServing() const
{
    if (this->cell)
        if (this->cell->registered())
            return true;
    return false;
}

bool RadioSignal::isRIL() const
{
    if (this->cell)
            return true;
    return false;
}

QOfonoExtCell::Type RadioSignal::type()
{
    if (this->cell) {
        return this->cell->type();
    }
    else
    {
        return QOfonoExtCell::Type::UNKNOWN;
    }
}

std::optional<int> RadioSignal::getMCC() const
{
    if (this->cell){
        return this->cell->mcc();
    }
    return std::nullopt;
}

std::optional<int> RadioSignal::getMNC() const
{
    if (this->cell){
        return this->cell->mnc();
    }
    return std::nullopt;
}

std::optional<int> RadioSignal::getSignalStrength() const
{
    if (this->cell){
        return this->cell->signalLevelDbm();
    }
    return std::nullopt;
}

std::optional<int> RadioSignal::getSignalLevelDbm() const
{
    if (this->cell){
        return this->cell->signalLevelDbm();
    }
    return std::nullopt;
}


void RadioSignal::onCellChanged(QString aName, int aValue)
{
    QOfonoExtCell* cell = (QOfonoExtCell*)sender();
    qDebug() << cell->path() << aName << "=>" << aValue;
    this->last_report = QDateTime::currentMSecsSinceEpoch();
    emit rilCellChanged();

}



RadioSignal::~RadioSignal(){};

