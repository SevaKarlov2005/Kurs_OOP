#ifndef STAFF_H
#define STAFF_H

#include <QString>

enum Profession {PILOT, ATTENDANT, ENGINEER};

class Staff
{
private:
    QString num_certificate; // Номер удостоверения
    QString surname; // Фамилия сотрудника
    QString name; // Имя сотрудника
    QString patronym; // Отчество сотрудника
    Profession profession; // Профессия сотрудника
public:
    Staff();
    Staff(const QString& num_certificate, const QString& surname, const QString& name, const QString& patronym, const Profession& profession);
    void SetNumCertificate(const QString& num_certificate);
    QString GetNumCertificate() const;
    void SetSurname(const QString& surname);
    QString GetSurname() const;
    void SetName(const QString& name);
    QString GetName() const;
    void SetPatronym(const QString& patronym);
    QString GetPatronym() const;
    void SetProfession(const Profession& num_certificate);
    Profession GetProfession() const;
};

#endif // STAFF_H
