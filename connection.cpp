#include "connection.h"

Connection::Connection(const QString& db_name)
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(db_name + ".db");

    this->query = new QSqlQuery(db);

    this->db.open();

    this->query->exec(R"(CREATE TABLE IF NOT EXISTS airport
                      (
                        airport_id INTEGER PRIMARY KEY AUTOINCREMENT,
                        airport_name VARCHAR(30) NOT NULL UNIQUE,
                        rainfall INTEGER NOT NULL CHECK (rainfall >= 0 AND rainfall <= 40),
                        speed INTEGER NOT NULL CHECK (speed >= 0 AND speed <= 300),
                        direction INTEGER NOT NULL CHECK (direction >= 0 AND direction <= 360),
                        temperature INTEGER NOT NULL CHECK (temperature >= -60 AND temperature <= 60)
                      ))");

    this->strategy = nullptr;
}

Connection::~Connection()
{
    if (db.isOpen())
        this->db.close();

    if (this->query)
        delete this->query;

    if (this->strategy)
        delete this->strategy;
}

void Connection::ChangeStrategy(DataStrategy* strategy)
{
    if (this->strategy)
        delete this->strategy;

    this->strategy = strategy;
}

void Connection::Insert(const QString& data)
{
    this->strategy->Insert(this->query, data);
}

void Connection::Update(const QString& data)
{
    this->strategy->Update(this->query, data);
}

void Connection::Delete(const QString& data)
{
    this->strategy->Delete(this->query, data);
}

void Connection::Load(Storage<Airport>* airport_st, Storage<Flight>* flight_st, Storage<Passenger>* passenger_st,
                      Storage<Purpose>* purpose_st, Storage<Staff>* staff_st, Storage<Ticket>* ticket_st)
{

}
