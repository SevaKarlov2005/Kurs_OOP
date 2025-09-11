#ifndef PASSENGER_H
#define PASSENGER_H

#include <QString>
#include <QDate>

class Passenger
{
private:
    QString num_passport;
    QString place_passport;
    QDate date_passport;
    QString surname;
    QString name;
    QString patronym;
    QDate birthday;
public:
    Passenger();
    Passenger(const QString& num_passport, const QString& place_passport, const QDate& date_passport,
              const QString& surname, const QString& name, const QString& patronym, const QDate& birthday);
    void SetNumPassport(const QString& num_passport);
    QString GetNumPassport();
    void SetPlacePassport(const QString& place_passport);
    QString GetPlacePassport();
    void SetDatePassport(const QDate& date_passport);
    QDate GetDatePassport();
    void SetSurname(const QString& surname);
    QString GetSurname();
    void SetName(const QString& name);
    QString GetName();
    void SetPatronym(const QString& patronym);
    QString GetPatronym();
    void SetBirthday(const QDate& birthday);
    QDate GetBirthday();
};

#endif // PASSENGER_H
