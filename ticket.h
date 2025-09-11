#ifndef TICKET_H
#define TICKET_H

#include <QString>

class Ticket
{
private:
    QString num_ticket;
    QString num_passport;
    QString num_flight;
public:
    Ticket();
    Ticket(const QString& num_ticket, const QString& num_passport, const QString& num_flight);
    void SetNumTicket(const QString& num_ticket);
    QString GetNumTicket();
    void SetNumPassport(const QString& num_passport);
    QString GetNumPassport();
    void SetNumFlight(const QString& num_flight);
    QString GetNumFlight();
};

#endif // TICKET_H
