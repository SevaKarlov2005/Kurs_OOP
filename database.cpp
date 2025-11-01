#include "database.h"

#include "strategycreator.h"

DataBase::DataBase(const QString& db_name)
{
    this->connection = new Connection(db_name);
}

DataBase::~DataBase()
{
    delete connection;
}

unsigned DataBase::GetIndex()
{
    return this->index;
}

void DataBase::Save(Memento& memento)
{
    StrategyCreator creator;

    this->connection->ChangeStrategy(creator.FactoryMethod(memento.GetTable()));

    if (memento.GetAction() == Action::INSERT)
        this->connection->Insert(memento.GetData());
    else if (memento.GetAction() == Action::DELETE)
        this->connection->Delete(memento.GetData());
    else if (memento.GetAction() == Action::UPDATE)
        this->connection->Update(memento.GetData());
}

void DataBase::SetPreviousState(Memento& memento)
{
    if (memento.GetAction() == Action::INSERT)
    {
        QStringList str_list = data.split('*', Qt::SkipEmptyParts);

        int index = FindAirport(Airport(str_list[0], 0, 0, 0, 0), [](Airport& cur, Airport& seek) { return cur.GetName() == seek.GetName(); });

        RemoveAirport(index, true);
    }
    else if (memento.GetAction() == Action::DELETE)
    {

    }
}

Memento DataBase::GetLastState()
{

}

void DataBase::Load()
{
    this->connection->Load(&this->airport_st, NULL, NULL, NULL, NULL, NULL);
}

void DataBase::AddAirport(const Airport& airport, const bool& flag)
{

}

Airport DataBase::GetAirport(const int& index)
{
    return this->airport_st.GetItem(index);
}

int DataBase::FindAirport(const Airport& airport, bool (*func)(Airport& cur, Airport& seek))
{

}

void DataBase::RemoveAirport(const int& index, const bool& flag)
{

}

void DataBase::UpdateAirport(const Airport& value, const int& index, const bool& flag)
{

}

unsigned DataBase::GetAirportSize()
{
    return this->airport_st.GetSize();
}
