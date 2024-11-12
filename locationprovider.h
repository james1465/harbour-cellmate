#ifndef LOCATIONPROVIDER_H
#define LOCATIONPROVIDER_H

#include <QObject>
#include <QGeoPositionInfoSource>
#include <QDebug>

class LocationProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString longitude READ getLongitude  NOTIFY longitudeChanged)
    Q_PROPERTY(QString latitude READ getLatitude  NOTIFY latitudeChanged)
public:
    LocationProvider(QObject *parent = 0);
    QString getLongitude() const;
    QString getLatitude() const;

signals:
    void longitudeChanged();
    void latitudeChanged();

public slots:
    void positionUpdated(const QGeoPositionInfo &info);

private:

    QGeoCoordinate location = QGeoCoordinate();


};
#endif // LOCATIONPROVIDER_H
