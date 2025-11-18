#ifndef FLIGHT_H
#define FLIGHT_H

#include <QString>
#include <QDate>
#include <QTime>

enum FlightState {ON_TIME, CHECK_IN, BOARDING, DIVERTED, DELAYED, CANCELLED};

class Flight
{
private:
    QString num_flight; // Номер авиарейса
    QString company; // Название авиакомпании
    QString from; // Название аэропорта отправления
    QString to; // Название аэропорта прибытия
    QDate date; // Дата отправления
    QTime time; // Время отправления
    FlightState state; // Статус авиарейса
    unsigned short all_place; // Количество мест
    unsigned short free_place; // Количество свободных мест
public:
    Flight();
    Flight(const QString& num_flight, const QString& company, const QString& from, const QString& to,
           const QDate& date, const QTime& time, const FlightState& state, const unsigned short& all_place,
           const unsigned short& free_place);
    void SetNumFlight(const QString& num_flight);
    QString GetNumFlight() const;
    void SetCompany(const QString& company);
    QString GetCompany() const;
    void SetFrom(const QString& from);
    QString GetFrom() const;
    void SetTo(const QString& to);
    QString GetTo() const;
    void SetDate(const QDate& date);
    QDate GetDate() const;
    void SetTime(const QTime& time);
    QTime GetTime() const;
    void SetState(const FlightState& state);
    FlightState GetState() const;
    void SetAllPlace(const unsigned short& all_place);
    unsigned short GetAllPlace() const;
    void SetFreePlace(const unsigned short& free_place);
    unsigned short GetFreePlace() const;
};

#endif // FLIGHT_H
