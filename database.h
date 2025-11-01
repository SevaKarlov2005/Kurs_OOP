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
public:
    DataBase(const QString& db_name);
    ~DataBase();
    unsigned GetIndex();
    void Save(Memento& memento);
    void SetPreviousState(Memento& memento);
    Memento GetLastState();
    void Load();
    void AddAirport(const Airport& airport, const bool& flag);
    Airport GetAirport(const int& index);
    int FindAirport(const Airport& airport, bool (*func)(Airport& cur, Airport& seek));
    void RemoveAirport(const int& index, const bool& flag);
    void UpdateAirport(const Airport& value, const int& index, const bool& flag);
    unsigned GetAirportSize();
};

#endif // DATABASE_H
