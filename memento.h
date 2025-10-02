#ifndef MEMENTO_H
#define MEMENTO_H

#include <QString>

enum Table {Airport, Flight, Passenger, Purpose, Staff, Ticket};
enum Action {Insert, Delete, Update};

class Memento
{
private:
    Table table;
    Action action;
    QString data;
public:
    Memento(const Table& table, const Action& action, const QString& data);
    Table GetTable();
    Action GetAction();
    QString GetData();
};

#endif // MEMENTO_H
