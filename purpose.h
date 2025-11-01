#ifndef PURPOSE_H
#define PURPOSE_H

#include <QString>

enum Nomination {FIRST_PILOT, SECOND_PILOT, CHIEF_ATTENDANT, FLIGHT_ATTENDANT, FLIGHT_ENGINEER};

class Purpose
{
private:
    Nomination name; // Специальность на борту
    QString num_flight; // Номер авиарейса
    QString num_certificate; // Номер удостоверения
public:
    Purpose();
    Purpose(const Nomination& name, const QString& num_flight, const QString& num_certificate);
    void SetName(const Nomination& name);
    Nomination GetName();
    void SetNumFlight(const QString& num_flight);
    QString GetNumFlight();
    void SetNumCertificate(const QString& num_certificate);
    QString GetNumCertificate();
};

#endif // PURPOSE_H
