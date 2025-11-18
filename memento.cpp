#include "memento.h"

Memento::Memento(const unsigned& count, const Table& table, const Action& action, const QString& data)
{
    this->count = count;
    this->table = table;
    this->action = action;
    this->data = data;
}

unsigned Memento::GetCount() const
{
    return this->count;
}

Table Memento::GetTable() const
{
    return this->table;
}

Action Memento::GetAction() const
{
    return this->action;
}

QString Memento::GetData() const
{
    return this->data;
}
