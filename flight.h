#ifndef FLIGHT_H
#define FLIGHT_H

#include <QString>
#include <QDate>
#include <QTime>

class Flight
{
private:
    QString num_flight;
    QString company;
    QString from;
    QString to;
    QDate date;
    QTime time;
    unsigned all_place;
    unsigned free_place;
public:
    Flight();
    Flight(const QString& num_flight, const QString& company, const QString& from, const QString& to,
           const QDate& date, const QTime& time, const unsigned& all_place, const unsigned& free_place);
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
    void SetAllPlace(const unsigned& all_place);
    unsigned GetAllPlace();
    void SetFreePlace(const unsigned& free_place);
    unsigned GetFreePlace();
};

#endif // FLIGHT_H
