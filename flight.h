#ifndef FLIGHT_H
#define FLIGHT_H

#include <QString>
#include <QDate>
#include <QTime>

enum FlightState {CHECK_IN, BOARDING, DELAYED, ESTIMATED, CANCELLED};

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
    QString GetNumFlight();
    void SetCompany(const QString& company);
    QString GetCompany();
    void SetFrom(const QString& from);
    QString GetFrom();
    void SetTo(const QString& to);
    QString GetTo();
    void SetDate(const QDate& date);
    QDate GetDate();
    void SetTime(const QTime& time);
    QTime GetTime();
    void SetState(const FlightState& state);
    FlightState GetState();
    void SetAllPlace(const unsigned short& all_place);
    unsigned short GetAllPlace();
    void SetFreePlace(const unsigned short& free_place);
    unsigned short GetFreePlace();
};

#endif // FLIGHT_H
