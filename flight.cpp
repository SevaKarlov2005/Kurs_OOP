#include "flight.h"

Flight::Flight()
{

}

Flight::Flight(const QString& num_flight, const QString& company, const QString& from, const QString& to,
               const QDate& date, const QTime& time, const unsigned& all_place, const unsigned& free_place)
{
    this->num_flight = num_flight;
    this->company = company;
    this->from = from;
    this->to = to;
    this->date = date;
    this->time = time;
    this->all_place = all_place;
    this->free_place = free_place;
}

void Flight::SetNumFlight(const QString& num_flight)
{
    this->num_flight = num_flight;
}

QString Flight::GetNumFlight()
{
    return this->num_flight;
}

void Flight::SetCompany(const QString& company)
{
    this->company = company;
}

QString Flight::GetCompany()
{
    return this->company;
}

void Flight::SetFrom(const QString& from)
{
    this->from = from;
}

QString Flight::GetFrom()
{
    return this->from;
}

void Flight::SetTo(const QString& to)
{
    this->to = to;
}

QString Flight::GetTo()
{
    return this->to;
}

void Flight::SetDate(const QDate& date)
{
    this->date = date;
}

QDate Flight::GetDate()
{
    return this->date;
}

void Flight::SetTime(const QTime& time)
{
    this->time = time;
}

QTime Flight::GetTime()
{
    return this->time;
}

void Flight::SetAllPlace(const unsigned& all_place)
{
    this->all_place = all_place;
}

unsigned Flight::GetAllPlace()
{
    return this->all_place;
}

void Flight::SetFreePlace(const unsigned& free_place)
{
    this->free_place = free_place;
}

unsigned Flight::GetFreePlace()
{
    return this->free_place;
}
