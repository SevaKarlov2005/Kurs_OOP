#include "airport.h"

Airport::Airport()
{

}

Airport::Airport(const QString& name, const unsigned short& rainfall, const unsigned short& speed,
                 const unsigned short& direction, const unsigned short& temperature)
{
    this->name = name;
    this->rainfall = rainfall;
    this->speed = speed;
    this->direction = direction;
    this->temperature = temperature;
}

void Airport::SetName(const QString& name)
{
    this->name = name;
}

QString Airport::GetName()
{
    return this->name;
}

void Airport::SetRainfall(const unsigned short& rainfall)
{
    this->rainfall = rainfall;
}

unsigned short Airport::GetRainfall()
{
    return this->rainfall;
}

void Airport::SetSpeed(const unsigned short& speed)
{
    this->speed = speed;
}

unsigned short Airport::GetSpeed()
{
    return this->speed;
}

void Airport::SetDirection(const unsigned short& direction)
{
    this->direction = direction;
}

unsigned short Airport::GetDirection()
{
    return this->direction;
}

void Airport::SetTemperature(const unsigned short& temperature)
{
    this->temperature = temperature;
}

unsigned short Airport::GetTemperature()
{
    return this->temperature;
}
