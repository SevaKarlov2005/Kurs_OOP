#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include "connection.h"
#include "storage.h"
#include "memento.h"

class DataBase
{
private:
    Connection* connection;
    unsigned count;
    Table table;
    Action action;
    QString data;
    unsigned index;
    Storage<Airport> airport_st;
    Storage<Flight> flight_st;
    Storage<Passenger> passenger_st;
    Storage<Purpose> purpose_st;
    Storage<Staff> staff_st;
    Storage<Ticket> ticket_st;
public:
    DataBase(const QString& db_name);
    ~DataBase();
    unsigned GetIndex() const;
    void Save(const Memento& memento) const;
    void SetPreviousState(const Memento& memento);
    Memento GetLastState() const;
    void Load();
    void AddAirport(const Airport& airport, const bool& flag);
    Airport GetAirport(const int& index) const;
    int FindAirport(const Airport& airport, bool (*func)(const Airport& cur, const Airport& seek)) const;
    void RemoveAirport(const int& index, const bool& flag);
    void UpdateAirport(const Airport& value, const int& index, const bool& flag);
    unsigned GetAirportSize() const;
};

#endif // DATABASE_H
