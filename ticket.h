#ifndef TICKET_H
#define TICKET_H

#include <QString>

class Ticket
{
private:
    QString num_ticket; // Номер авиабилета
    QString num_passport; // Номер паспорта пассажира
    QString num_flight; // Номер авиарейса
public:
    Ticket();
    Ticket(const QString& num_ticket, const QString& num_passport, const QString& num_flight);
    void SetNumTicket(const QString& num_ticket);
    QString GetNumTicket() const;
    void SetNumPassport(const QString& num_passport);
    QString GetNumPassport() const;
    void SetNumFlight(const QString& num_flight);
    QString GetNumFlight() const;
};

#endif // TICKET_H
