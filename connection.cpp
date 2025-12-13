#include "connection.h"
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
                      "patronym VARCHAR(20) NOT NULL,"
                      "birthday VARCHAR(10) NOT NULL"
                      ")");

    this->query->exec("CREATE TABLE IF NOT EXISTS staff"
                      "("
                      "id_staff INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "num_certificate VARCHAR(9) NOT NULL UNIQUE,"
                      "surname VARCHAR(20) NOT NULL,"
                      "name VARCHAR(20) NOT NULL,"
                      "patronym VARCHAR(20) NOT NULL,"
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
                      "time VARCHAR(5) NOT NULL,"
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
                      "purpose_name VARCHAR(30) NOT NULL,"
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

void Connection::Insert(const QString& data) const
{
    this->strategy->Insert(this->query, data);
}

void Connection::Update(const QString& data) const
{
    this->strategy->Update(this->query, data);
}

void Connection::Delete(const QString& data) const
{
    this->strategy->Delete(this->query, data);
}

void Connection::Load(Storage<Airport>* airport_st, Storage<Flight>* flight_st, Storage<Passenger>* passenger_st,
                      Storage<Purpose>* purpose_st, Storage<Staff>* staff_st, Storage<Ticket>* ticket_st) const
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
        unsigned short temperature = (short)this->query->value("temperature").toInt();

        airport_st->AddItem(Airport(name, rainfall, speed, direction, temperature));
    }

    this->query->exec("SELECT * FROM passenger");

    while (this->query->next())
    {
        QString num_passport = this->query->value("num_passport").toString();
        QString place_passport = this->query->value("place_passport").toString();
        QDate date_passport = QDate::fromString(this->query->value("date_passport").toString(), "dd.MM.yyyy");
        QString surname = this->query->value("surname").toString();
        QString name = this->query->value("name").toString();
        QString patronym = this->query->value("patronym").toString();
        QDate birthday = QDate::fromString(this->query->value("birthday").toString(), "dd.MM.yyyy");

        passenger_st->AddItem(Passenger(num_passport, place_passport, date_passport, surname, name, patronym, birthday));
    }

    this->query->exec("SELECT * FROM staff");

    while (this->query->next())
    {
        QString num_certificate = this->query->value("num_certificate").toString();
        QString surname = this->query->value("surname").toString();
        QString name = this->query->value("name").toString();
        QString patronym = this->query->value("patronym").toString();

        QString prof = this->query->value("profession").toString();
        Profession profession;

        if (prof == "Пилот")
            profession = Profession::PILOT;
        else if (prof == "Бортпроводник")
            profession = Profession::ATTENDANT;
        else if (prof == "Инженер")
            profession = Profession::ENGINEER;

        staff_st->AddItem(Staff(num_certificate, surname, name, patronym, profession));
    }

    this->query->exec("SELECT f.num_flight, f.company, a1.airport_name as fr, a2.airport_name as too, f.date, f.time, f.state, f.all_place, f.free_place "
                      "FROM flight as f "
                      "JOIN airport as a1 ON f.id_from = a1.id_airport "
                      "JOIN airport as a2 ON f.id_to = a2.id_airport");

    while (this->query->next())
    {
        QString num_flight = this->query->value("num_flight").toString();
        QString company = this->query->value("company").toString();
        QString from = this->query->value("fr").toString();
        QString to = this->query->value("too").toString();
        QDate date = QDate::fromString(this->query->value("date").toString(), "dd.MM.yyyy");
        QTime time = this->query->value("time").toTime();

        QString st = this->query->value("state").toString();
        FlightState state;

        if (st == "По расписанию")
            state = FlightState::ON_TIME;
        else if (st == "Регистрация")
            state = FlightState::CHECK_IN;
        else if (st == "Посадка")
            state = FlightState::BOARDING;
        else if (st == "Вылетел")
            state = FlightState::DIVERTED;
        else if (st == "Задерживается")
            state = FlightState::DELAYED;
        else if (st == "Отменён")
            state = FlightState::CANCELLED;

        unsigned short all_place = (unsigned)this->query->value("all_place").toInt();
        unsigned short free_place = (unsigned)this->query->value("free_place").toInt();

        flight_st->AddItem(Flight(num_flight, company, from, to, date, time, state, all_place, free_place));
    }

    this->query->exec("SELECT t.num_ticket, p.num_passport, f.num_flight "
                      "FROM ticket as t "
                      "JOIN passenger as p ON t.id_passenger = p.id_passenger "
                      "JOIN flight as f ON t.id_flight = f.id_flight");

    while (this->query->next())
    {
        QString num_ticket = this->query->value("num_ticket").toString();
        QString num_passport = this->query->value("num_passport").toString();
        QString num_flight = this->query->value("num_flight").toString();

        ticket_st->AddItem(Ticket(num_ticket, num_passport, num_flight));
    }

    this->query->exec("SELECT f.num_flight, s.num_certificate, p.purpose_name "
                      "FROM purpose as p "
                      "JOIN flight as f ON p.id_flight = f.id_flight "
                      "JOIN staff as s ON p.id_staff = s.id_staff");

    while (this->query->next())
    {
        QString num_flight = this->query->value("num_flight").toString();
        QString num_certificate = this->query->value("num_certificate").toString();

        QString nm = this->query->value("purpose_name").toString();
        Nomination nomination;

        if (nm == "Первый пилот")
            nomination = Nomination::FIRST_PILOT;
        else if (nm == "Второй пилот")
            nomination = Nomination::SECOND_PILOT;
        else if (nm == "Старший бортпроводник")
            nomination = Nomination::CHIEF_ATTENDANT;
        else if (nm == "Младший бортпроводник")
            nomination = Nomination::FLIGHT_ATTENDANT;
        else if (nm == "Бортовой инженер")
            nomination = Nomination::FLIGHT_ENGINEER;

        purpose_st->AddItem(Purpose(nomination, num_flight, num_certificate));
    }
}
