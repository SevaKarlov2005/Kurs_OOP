#include "memento.h"

Memento::Memento(const Table& table, const Action& action, const QString& data)
{
    this->table = table;
    this->action = action;
    this->data = data;
}

Table Memento::GetTable()
{
    return this->table;
}

Action Memento::GetAction()
{
    return this->action;
}

QString Memento::GetData()
{
    return this->data;
}
