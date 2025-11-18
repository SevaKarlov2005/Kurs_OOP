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
    unsigned GetCount() const;
    Table GetTable() const;
    Action GetAction() const;
    QString GetData() const;
};

#endif // MEMENTO_H
