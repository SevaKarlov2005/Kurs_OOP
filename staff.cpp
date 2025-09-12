#include "staff.h"

Staff::Staff()
{

}

Staff::Staff(const QString& num_certificate, const QString& surname, const QString& name, const QString& patronym, const Profession& profession)
{
    this->num_certificate = num_certificate;
    this->surname = surname;
    this->name = name;
    this->patronym = patronym;
    this->profession = profession;
}
void Staff::SetNumCertificate(const QString& num_certificate)
{
    this->num_certificate = num_certificate;
}

QString Staff::GetNumCertificate()
{
    return this->num_certificate;
}

void Staff::SetSurname(const QString& surname)
{
    this->surname = surname;
}

QString Staff::GetSurname()
{
    return this->surname;
}

void Staff::SetName(const QString& name)
{
    this->name = name;
}

QString Staff::GetName()
{
    return this->name;
}

void Staff::SetPatronym(const QString& patronym)
{
    this->patronym = patronym;
}

QString Staff::GetPatronym()
{
    return this->patronym;
}

void Staff::SetProfession(const Profession& profession)
{
    this->profession = profession;
}

Profession Staff::GetProfession()
{
    return this->profession;
}
