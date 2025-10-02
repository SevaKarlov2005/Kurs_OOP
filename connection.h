#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include "datastrategy.h"
#include "storage.h"
#include "airport.h"
#include "flight.h"
#include "passenger.h"
#include "purpose.h"
#include "staff.h"
#include "ticket.h"

class Connection
{
private:
    QSqlDatabase db;
    QSqlQuery* query;
    DataStrategy* strategy;
public:
    Connection(const QString& db_name);
    ~Connection();
    void ChangeStrategy(DataStrategy* strategy);
    void Insert(const QString& data);
    void Update(const QString& data);
    void Delete(const QString& data);
    void Load(Storage<Airport>* airport_st, Storage<Flight>* flight_st, Storage<Passenger>* passenger_st,
              Storage<Purpose>* purpose_st, Storage<Staff>* staff_st, Storage<Ticket>* ticket_st);
};

#endif // CONNECTION_H
