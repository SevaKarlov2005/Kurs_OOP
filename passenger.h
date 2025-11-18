#ifndef PASSENGER_H
#define PASSENGER_H

#include <QString>
#include <QDate>

class Passenger
{
private:
    QString num_passport; // Номер паспорта
    QString place_passport; // Место выдачи паспорта
    QDate date_passport; // Дата выдачи паспорта
    QString surname; // Фамилия пассажира
    QString name; // Имя пассажира
    QString patronym; // Отчество пассажира
    QDate birthday; // Дата рождения
public:
    Passenger();
    Passenger(const QString& num_passport, const QString& place_passport, const QDate& date_passport,
              const QString& surname, const QString& name, const QString& patronym, const QDate& birthday);
    void SetNumPassport(const QString& num_passport);
    QString GetNumPassport() const;
    void SetPlacePassport(const QString& place_passport);
    QString GetPlacePassport() const;
    void SetDatePassport(const QDate& date_passport);
    QDate GetDatePassport() const;
    void SetSurname(const QString& surname);
    QString GetSurname() const;
    void SetName(const QString& name);
    QString GetName() const;
    void SetPatronym(const QString& patronym);
    QString GetPatronym() const;
    void SetBirthday(const QDate& birthday);
    QDate GetBirthday() const;
};

#endif // PASSENGER_H
