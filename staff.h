#ifndef STAFF_H
#define STAFF_H

#include <QString>

enum Profession {Pilot, FlightAttendant};

class Staff
{
private:
    QString num_certificate;
    QString surname;
    QString name;
    QString patronym;
    Profession profession;
public:
    Staff();
    Staff(const QString& num_certificate, const QString& surname, const QString& name, const QString& patronym, const Profession& profession);
    void SetNumCertificate(const QString& num_certificate);
    QString GetNumCertificate();
    void SetSurname(const QString& surname);
    QString GetSurname();
    void SetName(const QString& name);
    QString GetName();
    void SetPatronym(const QString& patronym);
    QString GetPatronym();
    void SetProfession(const Profession& num_certificate);
    Profession GetProfession();
};

#endif // STAFF_H
