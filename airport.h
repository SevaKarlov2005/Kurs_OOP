#ifndef AIRPORT_H
#define AIRPORT_H

#include <QString>

class Airport
{
private:
    QString name;
    unsigned short rainfall;
    unsigned short speed;
    unsigned short direction;
    unsigned short temperature;
public:
    Airport();
    Airport(const QString& name, const unsigned short& rainfall, const unsigned short& speed,
            const unsigned short& direction, const unsigned short& temperature);
    void SetName(const QString& name);
    QString GetName();
    void SetRainfall(const unsigned short& rainfall);
    unsigned short GetRainfall();
    void SetSpeed(const unsigned short& speed);
    unsigned short GetSpeed();
    void SetDirection(const unsigned short& direction);
    unsigned short GetDirection();
    void SetTemperature(const unsigned short& temperature);
    unsigned short GetTemperature();
};

#endif // AIRPORT_H
