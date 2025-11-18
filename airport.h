#ifndef AIRPORT_H
#define AIRPORT_H

#include <QString>

class Airport
{
private:
    QString name; // Название аэропорта
    unsigned short rainfall; // Количество осадков
    unsigned short speed; // Скорость ветра
    unsigned short direction; // Направление ветра
    unsigned short temperature; // Температура воздуха
public:
    Airport();
    Airport(const QString& name, const unsigned short& rainfall, const unsigned short& speed,
            const unsigned short& direction, const unsigned short& temperature);
    void SetName(const QString& name);
    QString GetName() const;
    void SetRainfall(const unsigned short& rainfall);
    unsigned short GetRainfall() const;
    void SetSpeed(const unsigned short& speed);
    unsigned short GetSpeed() const;
    void SetDirection(const unsigned short& direction);
    unsigned short GetDirection() const;
    void SetTemperature(const unsigned short& temperature);
    unsigned short GetTemperature() const;
};

#endif // AIRPORT_H
