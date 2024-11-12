#include "locationprovider.h"


    LocationProvider::LocationProvider(QObject *parent)
        : QObject(parent)
    {
        QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(this);
        if (source) {
            connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
                    this, SLOT(positionUpdated(QGeoPositionInfo)));
            source->startUpdates();
        }
    }

    QString LocationProvider::getLongitude() const
    {
        if (location.isValid())
        return QString::number(location.longitude());
        else
            return QString("Unknown");

    }

    QString LocationProvider::getLatitude() const
    {
        if (location.isValid())
        return QString::number(location.latitude());
        else
            return QString("Unknown");
    }

     void LocationProvider::positionUpdated(const QGeoPositionInfo &info)
    {
            qDebug() << "Location" << info;
            location = info.coordinate();
            emit longitudeChanged();
            emit latitudeChanged();
    }
