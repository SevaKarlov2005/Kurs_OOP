#ifndef PURPOSE_H
#define PURPOSE_H

#include <QString>

enum Nomination {FirstPilot, SecondPilot, ChiefAttendant, Attendant};

class Purpose
{
private:
    Nomination name;
    QString num_flight;
    QString num_certificate;
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
