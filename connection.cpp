#include "connection.h"
#include <QDebug>
#include <QCoreApplication>

Connection::Connection(const QString& db_name)
{
    this->db = QSqlDatabase::addDatabase("QSQLITE", "connection");
    this->db.setDatabaseName(QCoreApplication::applicationDirPath() + "/" + db_name + ".db");

    this->query = new QSqlQuery(db);

    this->db.open();

    this->query->exec("CREATE TABLE IF NOT EXISTS airport"
                      "("
                      "id_airport INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "airport_name VARCHAR(30) NOT NULL UNIQUE,"
                      "rainfall INTEGER NOT NULL,"
                      "speed INTEGER NOT NULL,"
                      "direction INTEGER NOT NULL,"
                      "temperature INTEGER NOT NULL"
                      ")");

    this->query->exec("CREATE TABLE IF NOT EXISTS passenger"
                      "("
                      "id_passenger INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "num_passport VARCHAR(11) NOT NULL UNIQUE,"
                      "place_passport VARCHAR(50) NOT NULL,"
                      "date_passport VARCHAR(10) NOT NULL,"
                      "surname VARCHAR(20) NOT NULL,"
                      "name VARCHAR(20) NOT NULL,"
                      "patronym VARCHAR(20),"
                      "birthday VARCHAR(10) NOT NULL"
                      ")");

    this->query->exec("CREATE TABLE IF NOT EXISTS staff"
                      "("
                      "id_staff INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "num_certificate VARCHAR(9) NOT NULL UNIQUE,"
                      "surname VARCHAR(20) NOT NULL,"
                      "name VARCHAR(20) NOT NULL,"
                      "patronym VARCHAR(20),"
                      "profession VARCHAR(30) NOT NULL"
                      ")");

    this->query->exec("CREATE TABLE IF NOT EXISTS flight"
                      "("
                      "id_flight INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "num_flight VARCHAR(7) NOT NULL UNIQUE,"
                      "company VARCHAR(30) NOT NULL,"
                      "id_from INTEGER NOT NULL,"
                      "id_to INTEGER NOT NULL,"
                      "date VARCHAR(10) NOT NULL,"
                      "time VARCHAR(8) NOT NULL,"
                      "state VARCHAR(20) NOT NULL,"
                      "all_place INTEGER,"
                      "free_place INTEGER,"
                      "FOREIGN KEY (id_from) REFERENCES airport (id_airport) ON DELETE CASCADE ON UPDATE RESTRICT,"
                      "FOREIGN KEY (id_to) REFERENCES airport (id_airport) ON DELETE CASCADE ON UPDATE RESTRICT"
                      ")");

    this->query->exec("CREATE TABLE IF NOT EXISTS ticket"
                      "("
                      "id_ticket INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "num_ticket VARCHAR(9) NOT NULL UNIQUE,"
                      "id_passenger INTEGER NOT NULL,"
                      "id_flight INTEGER NOT NULL,"
                      "FOREIGN KEY (id_passenger) REFERENCES passenger (id_passenger) ON DELETE CASCADE ON UPDATE RESTRICT,"
                      "FOREIGN KEY (id_flight) REFERENCES flight (id_flight) ON DELETE CASCADE ON UPDATE RESTRICT"
                      ")");

    this->query->exec("CREATE TABLE IF NOT EXISTS purpose"
                      "("
                      "id_purpose INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "id_flight INTEGER NOT NULL,"
                      "id_staff INTEGER NOT NULL,"
                      "FOREIGN KEY (id_flight) REFERENCES flight (id_flight) ON DELETE CASCADE ON UPDATE RESTRICT,"
                      "FOREIGN KEY (id_staff) REFERENCES staff (id_staff) ON DELETE CASCADE ON UPDATE RESTRICT"
                      ")");

    this->strategy = nullptr;
}

Connection::~Connection()
{
    if (this->strategy)
    {
        delete this->strategy;
        this->strategy = nullptr;
    }

    if (this->query)
    {
        delete this->query;
        this->query = nullptr;
    }

    if (db.isOpen())
        db.close();

    QSqlDatabase::removeDatabase("connection");
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
    airport_st->Clear();
    flight_st->Clear();
    passenger_st->Clear();
    purpose_st->Clear();
    staff_st->Clear();
    ticket_st->Clear();

    this->query->exec("SELECT * FROM airport");

    while (this->query->next())
    {
        QString name = this->query->value("airport_name").toString();
        unsigned short rainfall = (unsigned short)this->query->value("rainfall").toInt();
        unsigned short speed = (unsigned short)this->query->value("speed").toInt();
        unsigned short direction = (unsigned short)this->query->value("direction").toInt();
        unsigned short temperature = (unsigned short)this->query->value("temperature").toInt();

        airport_st->AddItem(Airport(name, rainfall, speed, direction, temperature));
    }
}
