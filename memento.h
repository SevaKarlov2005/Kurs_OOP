#ifndef MEMENTO_H
#define MEMENTO_H

#include <QString>

enum Table {AIRPORT, FLIGHT, PASSENGER, PURPOSE, STAFF, TICKET};
enum Action {INSERT, DELETE, UPDATE};

class Memento
{
private:
    unsigned count;
    Table table;
    Action action;
    QString data;
public:
    Memento(const unsigned& count, const Table& table, const Action& action, const QString& data);
    unsigned GetCount();
    Table GetTable();
    Action GetAction();
    QString GetData();
};

#endif // MEMENTO_H
