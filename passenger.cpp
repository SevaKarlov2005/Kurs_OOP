#include "passenger.h"

Passenger::Passenger()
{

}

Passenger::Passenger(const QString& num_passport, const QString& place_passport, const QDate& date_passport,
                     const QString& surname, const QString& name, const QString& patronym, const QDate& birthday)
{
    this->num_passport = num_passport;
    this->place_passport = place_passport;
    this->date_passport = date_passport;
    this->surname = surname;
    this->name = name;
    this->patronym = patronym;
    this->birthday = birthday;
}

void Passenger::SetNumPassport(const QString& num_passport)
{
    this->num_passport = num_passport;
}

QString Passenger::GetNumPassport()
{
    return this->num_passport;
}

void Passenger::SetPlacePassport(const QString& place_passport)
{
    this->place_passport = place_passport;
}

QString Passenger::GetPlacePassport()
{
    return this->place_passport;
}

void Passenger::SetDatePassport(const QDate& date_passport)
{
    this->date_passport = date_passport;
}

QDate Passenger::GetDatePassport()
{
    return this->date_passport;
}

void Passenger::SetSurname(const QString& surname)
{
    this->surname = surname;
}

QString Passenger::GetSurname()
{
    return this->surname;
}

void Passenger::SetName(const QString& name)
{
    this->name = name;
}

QString Passenger::GetName()
{
    return this->name;
}

void Passenger::SetPatronym(const QString& patronym)
{
    this->patronym = patronym;
}

QString Passenger::GetPatronym()
{
    return this->patronym;
}

void Passenger::SetBirthday(const QDate& birthday)
{
    this->birthday = birthday;
}

QDate Passenger::GetBirthday()
{
    return this->birthday;
}
