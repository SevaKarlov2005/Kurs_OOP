#include "purpose.h"

Purpose::Purpose()
{

}

Purpose::Purpose(const Nomination& name, const QString& num_flight, const QString& num_certificate)
{
    this->name = name;
    this->num_flight = num_flight;
    this->num_certificate = num_certificate;
}

void Purpose::SetName(const Nomination& name)
{
    this->name = name;
}

Nomination Purpose::GetName()
{
    return this->name;
}

void Purpose::SetNumFlight(const QString& num_flight)
{
    this-> num_flight = num_flight;
}

QString Purpose::GetNumFlight()
{
    return this->num_flight;
}

void Purpose::SetNumCertificate(const QString& num_certificate)
{
    this-> num_certificate = num_certificate;
}

QString Purpose::GetNumCertificate()
{
    return this->num_certificate;
}
