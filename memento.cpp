#include "memento.h"

Memento::Memento(const unsigned& count, const Table& table, const Action& action, const QString& data)
{
    this->count = count;
    this->table = table;
    this->action = action;
    this->data = data;
}

unsigned Memento::GetCount()
{
    return this->count;
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
