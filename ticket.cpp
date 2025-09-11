#include "ticket.h"

Ticket::Ticket()
{

}

Ticket::Ticket(const QString& num_ticket, const QString& num_passport, const QString& num_flight)
{
    this->num_ticket = num_ticket;
    this->num_passport = num_passport;
    this->num_flight = num_flight;
}

void Ticket::SetNumTicket(const QString& num_ticket)
{
    this->num_ticket = num_ticket;
}

QString Ticket::GetNumTicket()
{
    return this->num_ticket;
}

void Ticket::SetNumPassport(const QString& num_passport)
{
    this->num_passport = num_passport;
}

QString Ticket::GetNumPassport()
{
    return this->num_passport;
}

void Ticket::SetNumFlight(const QString& num_flight)
{
    this->num_flight = num_flight;
}

QString Ticket::GetNumFlight()
{
    return this->num_flight;
}
