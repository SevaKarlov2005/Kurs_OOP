#include "database.h"

#include "strategycreator.h"

DataBase::DataBase(const QString& db_name)
{
    this->count = 0;
    this->index = 0;
    this->state = true;

    this->connection = new Connection(db_name);
}

DataBase::~DataBase()
{
    delete connection;
}

unsigned DataBase::GetIndex() const
{
    return this->index;
}

void DataBase::Save(const Memento& memento) const
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

void DataBase::SetPreviousState(const Memento& memento)
{
    if (memento.GetTable() == Table::AIRPORT)
    {
        if (memento.GetAction() == Action::INSERT)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->airport_st.FindItem(Airport(str_list[0], 0, 0, 0, 0),
                                                [](const Airport& cur, const Airport& seek) { return cur.GetName() == seek.GetName(); }) * 10 + 1;

            this->airport_st.RemoveItem(this->index / 10);
        }
        else if (memento.GetAction() == Action::UPDATE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->airport_st.FindItem(Airport(str_list[5], 0, 0, 0, 0),
                                                [](const Airport& cur, const Airport& seek) { return cur.GetName() == seek.GetName(); }) * 10 + 2;

            this->airport_st.UpdateItem(Airport(str_list[0], str_list[1].toInt(), str_list[2].toInt(), str_list[3].toInt(), str_list[4].toInt()),
                                        this->index / 10);
        }
        else if (memento.GetAction() == Action::DELETE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->airport_st.AddItem(Airport(str_list[0], str_list[1].toInt(), str_list[2].toInt(), str_list[3].toInt(), str_list[4].toInt()));

            this->index = (this->airport_st.GetSize() - 1) * 10 + 3;
        }

        emit ChangeAirport();
    }
    else if (memento.GetTable() == Table::PASSENGER)
    {
        if (memento.GetAction() == Action::INSERT)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->passenger_st.FindItem(Passenger(str_list[0], "", QDate(), "", "", "", QDate()),
                                                [](const Passenger& cur, const Passenger& seek) { return cur.GetNumPassport() == seek.GetNumPassport(); }) * 10 + 1;

            this->passenger_st.RemoveItem(this->index / 10);
        }
        else if (memento.GetAction() == Action::UPDATE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->passenger_st.FindItem(Passenger(str_list[7], "", QDate(), "", "", "", QDate()),
                                                [](const Passenger& cur, const Passenger& seek) { return cur.GetNumPassport() == seek.GetNumPassport(); }) * 10 + 2;

            this->passenger_st.UpdateItem(Passenger(str_list[0], str_list[1], QDate::fromString(str_list[2], "dd.MM.yyyy"), str_list[3], str_list[4], str_list[5],
                                                    QDate::fromString(str_list[6], "dd.MM.yyyy")), this->index / 10);
        }
        else if (memento.GetAction() == Action::DELETE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->passenger_st.AddItem(Passenger(str_list[0], str_list[1], QDate::fromString(str_list[2], "dd.MM.yyyy"), str_list[3], str_list[4], str_list[5],
                                                 QDate::fromString(str_list[6], "dd.MM.yyyy")));

            this->index = (this->passenger_st.GetSize() - 1) * 10 + 3;
        }

        emit ChangePassenger();
    }
    else if (memento.GetTable() == Table::TICKET)
    {
        if (memento.GetAction() == Action::INSERT)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->ticket_st.FindItem(Ticket(str_list[0], "", ""),
                                                  [](const Ticket& cur, const Ticket& seek) { return cur.GetNumTicket() == seek.GetNumTicket(); }) * 10 + 1;

            this->ticket_st.RemoveItem(this->index / 10);
        }
        else if (memento.GetAction() == Action::UPDATE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->ticket_st.FindItem(Ticket(str_list[3], "", ""),
                                                  [](const Ticket& cur, const Ticket& seek) { return cur.GetNumTicket() == seek.GetNumTicket(); }) * 10 + 2;

            this->ticket_st.UpdateItem(Ticket(str_list[0], str_list[1], str_list[2]), this->index / 10);
        }
        else if (memento.GetAction() == Action::DELETE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->ticket_st.AddItem(Ticket(str_list[0], str_list[1], str_list[2]));

            this->index = (this->ticket_st.GetSize() - 1) * 10 + 3;
        }

        emit ChangeTicket();
    }
    else if (memento.GetTable() == Table::FLIGHT)
    {
        if (memento.GetAction() == Action::INSERT)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->flight_st.FindItem(Flight(str_list[0], "", "", "", QDate(), QTime(), FlightState::ON_TIME, 0, 0),
                                                   [](const Flight& cur, const Flight& seek) { return cur.GetNumFlight() == seek.GetNumFlight(); }) * 10 + 1;

            this->flight_st.RemoveItem(this->index / 10);
        }
        else if (memento.GetAction() == Action::UPDATE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->flight_st.FindItem(Flight(str_list[9], "", "", "", QDate(), QTime(), FlightState::ON_TIME, 0, 0),
                                                   [](const Flight& cur, const Flight& seek) { return cur.GetNumFlight() == seek.GetNumFlight(); }) * 10 + 2;

            FlightState state;

            if (str_list[6] == "По расписанию")
                state = FlightState::ON_TIME;
            else if (str_list[6] == "Регистрация")
                state = FlightState::CHECK_IN;
            else if (str_list[6] == "Посадка")
                state = FlightState::BOARDING;
            else if (str_list[6] == "Вылетел")
                state = FlightState::DIVERTED;
            else if (str_list[6] == "Задерживается")
                state = FlightState::DELAYED;
            else if (str_list[6] == "Отменён")
                state = FlightState::CANCELLED;

            this->flight_st.UpdateItem(Flight(str_list[0], str_list[1], str_list[2], str_list[3], QDate::fromString(str_list[4], "dd.MM.yyyy"),
                                              QTime::fromString(str_list[5]), state, str_list[7].toInt(), str_list[8].toInt()), this->index / 10);
        }
        else if (memento.GetAction() == Action::DELETE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            FlightState state;

            if (str_list[6] == "По расписанию")
                state = FlightState::ON_TIME;
            else if (str_list[6] == "Регистрация")
                state = FlightState::CHECK_IN;
            else if (str_list[6] == "Посадка")
                state = FlightState::BOARDING;
            else if (str_list[6] == "Вылетел")
                state = FlightState::DIVERTED;
            else if (str_list[6] == "Задерживается")
                state = FlightState::DELAYED;
            else if (str_list[6] == "Отменён")
                state = FlightState::CANCELLED;

            this->flight_st.AddItem(Flight(str_list[0], str_list[1], str_list[2], str_list[3], QDate::fromString(str_list[4], "dd.MM.yyyy"),
                                           QTime::fromString(str_list[5]), state, str_list[7].toInt(), str_list[8].toInt()));

            this->index = (this->flight_st.GetSize() - 1) * 10 + 3;
        }

        emit ChangeFlight();
    }
    else if (memento.GetTable() == Table::STAFF)
    {
        if (memento.GetAction() == Action::INSERT)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->staff_st.FindItem(Staff(str_list[0], "", "", "", Profession::PILOT),
                                                   [](const Staff& cur, const Staff& seek) { return cur.GetNumCertificate() == seek.GetNumCertificate(); }) * 10 + 1;

            this->staff_st.RemoveItem(this->index / 1);
        }
        else if (memento.GetAction() == Action::UPDATE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->staff_st.FindItem(Staff(str_list[5], "", "", "", Profession::PILOT),
                                                   [](const Staff& cur, const Staff& seek) { return cur.GetNumCertificate() == seek.GetNumCertificate(); }) * 10 + 2;

            Profession profession;

            if (str_list[4] == "Пилот")
                profession = Profession::PILOT;
            else if (str_list[4] == "Бортпроводник")
                profession = Profession::ATTENDANT;
            else if (str_list[4] == "Инженер")
                profession = Profession::ENGINEER;

            this->staff_st.UpdateItem(Staff(str_list[0], str_list[1], str_list[2], str_list[3], profession), this->index / 10);
        }
        else if (memento.GetAction() == Action::DELETE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            Profession profession;

            if (str_list[4] == "Пилот")
                profession = Profession::PILOT;
            else if (str_list[4] == "Бортпроводник")
                profession = Profession::ATTENDANT;
            else if (str_list[4] == "Инженер")
                profession = Profession::ENGINEER;

            this->staff_st.AddItem(Staff(str_list[0], str_list[1], str_list[2], str_list[3], profession));

            this->index = (this->staff_st.GetSize() - 1) * 10 + 3;
        }

        emit ChangeStaff();
    }
    else if (memento.GetTable() == Table::PURPOSE)
    {
        if (memento.GetAction() == Action::INSERT)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->purpose_st.FindItem(Purpose(Nomination::FIRST_PILOT, str_list[1], str_list[2]),
                                                  [](const Purpose& cur, const Purpose& seek)
                                                  {
                                                      return cur.GetNumFlight() == seek.GetNumFlight() &&
                                                             cur.GetNumCertificate() == seek.GetNumCertificate();
                                                  }) * 10 + 1;

            this->purpose_st.RemoveItem(this->index / 10);
        }
        else if (memento.GetAction() == Action::UPDATE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->purpose_st.FindItem(Purpose(Nomination::FIRST_PILOT, str_list[4], str_list[5]),
                                                  [](const Purpose& cur, const Purpose& seek)
                                                    {
                                                        return cur.GetNumFlight() == seek.GetNumFlight() &&
                                                               cur.GetNumCertificate() == seek.GetNumCertificate();
                                                    }) * 10 + 2;

            Nomination nomination;

            if (str_list[0] == "Первый пилот")
                nomination = Nomination::FIRST_PILOT;
            else if (str_list[0] == "Второй пилот")
                nomination = Nomination::SECOND_PILOT;
            else if (str_list[0] == "Старший бортпроводник")
                nomination = Nomination::CHIEF_ATTENDANT;
            else if (str_list[0] == "Младший бортпроводник")
                nomination = Nomination::FLIGHT_ATTENDANT;
            else if (str_list[0] == "Бортовой инженер")
                nomination = Nomination::FLIGHT_ENGINEER;

            this->purpose_st.UpdateItem(Purpose(nomination, str_list[1], str_list[2]), this->index / 10);
        }
        else if (memento.GetAction() == Action::DELETE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            Nomination nomination;

            if (str_list[0] == "Первый пилот")
                nomination = Nomination::FIRST_PILOT;
            else if (str_list[0] == "Второй пилот")
                nomination = Nomination::SECOND_PILOT;
            else if (str_list[0] == "Старший бортпроводник")
                nomination = Nomination::CHIEF_ATTENDANT;
            else if (str_list[0] == "Младший бортпроводник")
                nomination = Nomination::FLIGHT_ATTENDANT;
            else if (str_list[0] == "Бортовой инженер")
                nomination = Nomination::FLIGHT_ENGINEER;

            this->purpose_st.AddItem(Purpose(nomination, str_list[1], str_list[2]));

            this->index = (this->purpose_st.GetSize() - 1) * 10 + 3;
        }

        emit ChangePurpose();
    }
}

Memento DataBase::GetLastState()
{
    Memento memento(this->count, this->table, this->action, this->data);

    if (this->state)
        this->count = 0;

    return memento;
}

void DataBase::Load()
{
    this->connection->Load(&this->airport_st, &this->flight_st, &this->passenger_st, &this->purpose_st, &this->staff_st, &this->ticket_st);

    emit Reload();
}

void DataBase::ChangeState(const bool flag)
{
    this->state = flag;
}

void DataBase::AddAirport(const Airport& airport, const bool& flag)
{
    this->airport_st.AddItem(airport);

    this->table = Table::AIRPORT;
    this->action = Action::INSERT;
    this->index = (this->airport_st.GetSize() - 1) * 10 + 1;
    this->data = airport.GetName() + "*" +
                 QString::number(airport.GetRainfall()) + "*" +
                 QString::number(airport.GetSpeed()) + "*" +
                 QString::number(airport.GetDirection()) + "*" +
                 QString::number(airport.GetTemperature());

    this->count++;


    if (flag)
        emit ChangeAirport();
}

Airport DataBase::GetAirport(const int& index) const
{
    return this->airport_st.GetItem(index);
}

int DataBase::FindAirport(const Airport& airport, bool (*func)(const Airport& cur, const Airport& seek)) const
{
    return this->airport_st.FindItem(airport, func);
}

void DataBase::RemoveAirport(const int& index, const bool& flag)
{
    Airport airport = this->airport_st.GetItem(index);
    this->airport_st.RemoveItem(index);

    this->table = Table::AIRPORT;
    this->action = Action::DELETE;
    this->data = airport.GetName() + "*" +
                 QString::number(airport.GetRainfall()) + "*" +
                 QString::number(airport.GetSpeed()) + "*" +
                 QString::number(airport.GetDirection()) + "*" +
                 QString::number(airport.GetTemperature());
    this->index = index * 10 + 3;

    this->count++;

    if (flag)
        emit ChangeAirport();
}

void DataBase::UpdateAirport(const Airport& value, const int& index, const bool& flag)
{
    Airport airport = this->airport_st.GetItem(index);
    this->airport_st.UpdateItem(value, index);

    this->table = Table::AIRPORT;
    this->action = Action::UPDATE;
    this->data = airport.GetName() + "*" +
                 QString::number(airport.GetRainfall()) + "*" +
                 QString::number(airport.GetSpeed()) + "*" +
                 QString::number(airport.GetDirection()) + "*" +
                 QString::number(airport.GetTemperature()) + "*" +
                 value.GetName() + "*" +
                 QString::number(value.GetRainfall()) + "*" +
                 QString::number(value.GetSpeed()) + "*" +
                 QString::number(value.GetDirection()) + "*" +
                 QString::number(value.GetTemperature());
    this->index = index * 10 + 2;

    this->count++;

    if (flag)
        emit ChangeAirport();
}

unsigned DataBase::GetAirportSize() const
{
    return this->airport_st.GetSize();
}

void DataBase::AddFlight(const Flight& flight, const bool& flag)
{
    this->flight_st.AddItem(flight);

    this->table = Table::FLIGHT;
    this->action = Action::INSERT;
    this->index = (this->flight_st.GetSize() - 1) * 10 + 1;

    QString state;

    if (flight.GetState() == FlightState::ON_TIME)
        state = "По расписанию";
    else if (flight.GetState() == FlightState::CHECK_IN)
        state = "Регистрация";
    else if (flight.GetState() == FlightState::BOARDING)
        state = "Посадка";
    else if (flight.GetState() == FlightState::DIVERTED)
        state = "Вылетел";
    else if (flight.GetState() == FlightState::DELAYED)
        state = "Задерживается";
    else if (flight.GetState() == FlightState::CANCELLED)
        state = "Отменён";

    this->data = flight.GetNumFlight() + "*" +
                 flight.GetCompany() + "*" +
                 flight.GetFrom() + "*" +
                 flight.GetTo() + "*" +
                 flight.GetDate().toString("dd.MM.yyyy") + "*" +
                 flight.GetTime().toString("HH:mm") + "*" +
                 state + "*" +
                 QString::number(flight.GetAllPlace()) + "*" +
                 QString::number(flight.GetFreePlace());

    this->count++;

    if (flag)
        emit ChangeFlight();
}

Flight DataBase::GetFlight(const int& index) const
{
    return this->flight_st.GetItem(index);
}

int DataBase::FindFlight(const Flight& flight, bool (*func)(const Flight& cur, const Flight& seek)) const
{
    return this->flight_st.FindItem(flight, func);
}

void DataBase::RemoveFlight(const int& index, const bool& flag)
{
    Flight flight = this->flight_st.GetItem(index);
    this->flight_st.RemoveItem(index);

    this->table = Table::FLIGHT;
    this->action = Action::DELETE;

    QString state;

    if (flight.GetState() == FlightState::ON_TIME)
        state = "По расписанию";
    else if (flight.GetState() == FlightState::CHECK_IN)
        state = "Регистрация";
    else if (flight.GetState() == FlightState::BOARDING)
        state = "Посадка";
    else if (flight.GetState() == FlightState::DIVERTED)
        state = "Вылетел";
    else if (flight.GetState() == FlightState::DELAYED)
        state = "Задерживается";
    else if (flight.GetState() == FlightState::CANCELLED)
        state = "Отменён";

    this->data = flight.GetNumFlight() + "*" +
                 flight.GetCompany() + "*" +
                 flight.GetFrom() + "*" +
                 flight.GetTo() + "*" +
                 flight.GetDate().toString("dd.MM.yyyy") + "*" +
                 flight.GetTime().toString("HH:mm") + "*" +
                 state + "*" +
                 QString::number(flight.GetAllPlace()) + "*" +
                 QString::number(flight.GetFreePlace());
    this->index = index * 10 + 3;

    this->count++;

    if (flag)
        emit ChangeFlight();
}

void DataBase::UpdateFlight(const Flight& value, const int& index, const bool& flag)
{
    Flight flight = this->flight_st.GetItem(index);
    this->flight_st.UpdateItem(value, index);

    this->table = Table::FLIGHT;
    this->action = Action::UPDATE;

    QString state;

    if (flight.GetState() == FlightState::ON_TIME)
        state = "По расписанию";
    else if (flight.GetState() == FlightState::CHECK_IN)
        state = "Регистрация";
    else if (flight.GetState() == FlightState::BOARDING)
        state = "Посадка";
    else if (flight.GetState() == FlightState::DIVERTED)
        state = "Вылетел";
    else if (flight.GetState() == FlightState::DELAYED)
        state = "Задерживается";
    else if (flight.GetState() == FlightState::CANCELLED)
        state = "Отменён";

    QString new_state;

    if (value.GetState() == FlightState::ON_TIME)
        new_state = "По расписанию";
    else if (value.GetState() == FlightState::CHECK_IN)
        new_state = "Регистрация";
    else if (value.GetState() == FlightState::BOARDING)
        new_state = "Посадка";
    else if (value.GetState() == FlightState::DIVERTED)
        new_state = "Вылетел";
    else if (value.GetState() == FlightState::DELAYED)
        new_state = "Задерживается";
    else if (value.GetState() == FlightState::CANCELLED)
        new_state = "Отменён";

    this->data = flight.GetNumFlight() + "*" +
                 flight.GetCompany() + "*" +
                 flight.GetFrom() + "*" +
                 flight.GetTo() + "*" +
                 flight.GetDate().toString("dd.MM.yyyy") + "*" +
                 flight.GetTime().toString("HH:mm") + "*" +
                 state + "*" +
                 QString::number(flight.GetAllPlace()) + "*" +
                 QString::number(flight.GetFreePlace()) + "*" +
                 value.GetNumFlight() + "*" +
                 value.GetCompany() + "*" +
                 value.GetFrom() + "*" +
                 value.GetTo() + "*" +
                 value.GetDate().toString("dd.MM.yyyy") + "*" +
                 value.GetTime().toString("HH:mm") + "*" +
                 new_state + "*" +
                 QString::number(value.GetAllPlace()) + "*" +
                 QString::number(value.GetFreePlace());

    this->index = index * 10 + 2;

    this->count++;

    if (flag)
        emit ChangeFlight();
}

unsigned DataBase::GetFlightSize() const
{
    return this->flight_st.GetSize();
}

void DataBase::AddPassenger(const Passenger& passenger, const bool& flag)
{
    this->passenger_st.AddItem(passenger);

    this->table = Table::PASSENGER;
    this->action = Action::INSERT;
    this->index = (this->passenger_st.GetSize() - 1) * 10 + 1;
    this->data = passenger.GetNumPassport() + "*" +
                 passenger.GetPlacePassport() + "*" +
                 passenger.GetDatePassport().toString("dd.MM.yyyy") + "*" +
                 passenger.GetSurname() + "*" +
                 passenger.GetName() + "*" +
                 passenger.GetPatronym() + "*" +
                 passenger.GetBirthday().toString("dd.MM.yyyy");

    this->count++;

    if (flag)
        emit ChangePassenger();
}

Passenger DataBase::GetPassenger(const int& index) const
{
    return this->passenger_st.GetItem(index);
}

int DataBase::FindPassenger(const Passenger& passenger, bool (*func)(const Passenger& cur, const Passenger& seek)) const
{
    return this->passenger_st.FindItem(passenger, func);
}

void DataBase::RemovePassenger(const int& index, const bool& flag)
{
    Passenger passenger = this->passenger_st.GetItem(index);
    this->passenger_st.RemoveItem(index);

    this->table = Table::PASSENGER;
    this->action = Action::DELETE;
    this->data = passenger.GetNumPassport() + "*" +
                 passenger.GetPlacePassport() + "*" +
                 passenger.GetDatePassport().toString("dd.MM.yyyy") + "*" +
                 passenger.GetSurname() + "*" +
                 passenger.GetName() + "*" +
                 passenger.GetPatronym() + "*" +
                 passenger.GetBirthday().toString("dd.MM.yyyy");
    this->index = index * 10 + 3;

    this->count++;

    if (flag)
        emit ChangePassenger();
}

void DataBase::UpdatePassenger(const Passenger& value, const int& index, const bool& flag)
{
    Passenger passenger = this->passenger_st.GetItem(index);
    this->passenger_st.UpdateItem(value, index);

    this->table = Table::PASSENGER;
    this->action = Action::UPDATE;
    this->data = passenger.GetNumPassport() + "*" +
                 passenger.GetPlacePassport() + "*" +
                 passenger.GetDatePassport().toString("dd.MM.yyyy") + "*" +
                 passenger.GetSurname() + "*" +
                 passenger.GetName() + "*" +
                 passenger.GetPatronym() + "*" +
                 passenger.GetBirthday().toString("dd.MM.yyyy") + "*" +
                 value.GetNumPassport() + "*" +
                 value.GetPlacePassport() + "*" +
                 value.GetDatePassport().toString("dd.MM.yyyy") + "*" +
                 value.GetSurname() + "*" +
                 value.GetName() + "*" +
                 value.GetPatronym() + "*" +
                 value.GetBirthday().toString("dd.MM.yyyy");

    this->index = index * 10 + 2;

    this->count++;

    if (flag)
        emit ChangePassenger();
}

unsigned DataBase::GetPassengerSize() const
{
    return this->passenger_st.GetSize();
}

void DataBase::AddPurpose(const Purpose& purpose, const bool& flag)
{
    this->purpose_st.AddItem(purpose);

    this->table = Table::PURPOSE;
    this->action = Action::INSERT;
    this->index = (this->purpose_st.GetSize() - 1) * 10 + 1;

    QString nomination;

    if (purpose.GetName() == Nomination::FIRST_PILOT)
        nomination = "Первый пилот";
    else if (purpose.GetName() == Nomination::SECOND_PILOT)
        nomination = "Второй пилот";
    else if (purpose.GetName() == Nomination::CHIEF_ATTENDANT)
        nomination = "Старший бортпроводник";
    else if (purpose.GetName() == Nomination::FLIGHT_ATTENDANT)
        nomination = "Младший бортпроводник";
    else if (purpose.GetName() == Nomination::FLIGHT_ENGINEER)
        nomination = "Бортовой инженер";

    this->data = nomination + "*" +
                 purpose.GetNumFlight() + "*" +
                 purpose.GetNumCertificate();

    this->count++;

    if (flag)
        emit ChangePurpose();
}

Purpose DataBase::GetPurpose(const int& index) const
{
    return this->purpose_st.GetItem(index);
}

int DataBase::FindPurpose(const Purpose& purpose, bool (*func)(const Purpose& cur, const Purpose& seek)) const
{
    return this->purpose_st.FindItem(purpose, func);
}

void DataBase::RemovePurpose(const int& index, const bool& flag)
{
    Purpose purpose = this->purpose_st.GetItem(index);
    this->purpose_st.RemoveItem(index);

    this->table = Table::PURPOSE;
    this->action = Action::DELETE;

    QString nomination;

    if (purpose.GetName() == Nomination::FIRST_PILOT)
        nomination = "Первый пилот";
    else if (purpose.GetName() == Nomination::SECOND_PILOT)
        nomination = "Второй пилот";
    else if (purpose.GetName() == Nomination::CHIEF_ATTENDANT)
        nomination = "Старший бортпроводник";
    else if (purpose.GetName() == Nomination::FLIGHT_ATTENDANT)
        nomination = "Младший бортпроводник";
    else if (purpose.GetName() == Nomination::FLIGHT_ENGINEER)
        nomination = "Бортовой инженер";

    this->data = nomination + "*" +
                 purpose.GetNumFlight() + "*" +
                 purpose.GetNumCertificate();
    this->index = index * 10 + 3;

    this->count++;

    if (flag)
        emit ChangePurpose();
}

void DataBase::UpdatePurpose(const Purpose& value, const int& index, const bool& flag)
{
    Purpose purpose = this->purpose_st.GetItem(index);
    this->purpose_st.UpdateItem(value, index);

    this->table = Table::PURPOSE;
    this->action = Action::UPDATE;

    QString nomination;

    if (purpose.GetName() == Nomination::FIRST_PILOT)
        nomination = "Первый пилот";
    else if (purpose.GetName() == Nomination::SECOND_PILOT)
        nomination = "Второй пилот";
    else if (purpose.GetName() == Nomination::CHIEF_ATTENDANT)
        nomination = "Старший бортпроводник";
    else if (purpose.GetName() == Nomination::FLIGHT_ATTENDANT)
        nomination = "Младший бортпроводник";
    else if (purpose.GetName() == Nomination::FLIGHT_ENGINEER)
        nomination = "Бортовой инженер";

    QString new_nomination;

    if (value.GetName() == Nomination::FIRST_PILOT)
        new_nomination = "Первый пилот";
    else if (value.GetName() == Nomination::SECOND_PILOT)
        new_nomination = "Второй пилот";
    else if (value.GetName() == Nomination::CHIEF_ATTENDANT)
        new_nomination = "Старший бортпроводник";
    else if (value.GetName() == Nomination::FLIGHT_ATTENDANT)
        new_nomination = "Младший бортпроводник";
    else if (value.GetName() == Nomination::FLIGHT_ENGINEER)
        new_nomination = "Бортовой инженер";

    this->data = nomination + "*" +
                 purpose.GetNumFlight() + "*" +
                 purpose.GetNumCertificate() + "*" +
                 new_nomination + "*" +
                 value.GetNumFlight() + "*" +
                 value.GetNumCertificate();

    this->index = index * 10 + 2;

    this->count++;

    if (flag)
        emit ChangePurpose();
}

unsigned DataBase::GetPurposeSize() const
{
    return this->purpose_st.GetSize();
}

void DataBase::AddStaff(const Staff& staff, const bool& flag)
{
    this->staff_st.AddItem(staff);

    this->table = Table::STAFF;
    this->action = Action::INSERT;
    this->index = (this->staff_st.GetSize() - 1) * 10 + 1;

    QString profession;

    if (staff.GetProfession() == Profession::PILOT)
        profession = "Пилот";
    else if (staff.GetProfession() == Profession::ATTENDANT)
        profession = "Бортпроводник";
    else if (staff.GetProfession() == Profession::ENGINEER)
        profession = "Инженер";

    this->data = staff.GetNumCertificate() + "*" +
                 staff.GetSurname() + "*" +
                 staff.GetName() + "*" +
                 staff.GetPatronym() + "*" +
                 profession;

    this->count++;

    if (flag)
        emit ChangeStaff();
}

Staff DataBase::GetStaff(const int& index) const
{
    return this->staff_st.GetItem(index);
}

int DataBase::FindStaff(const Staff& staff, bool (*func)(const Staff& cur, const Staff& seek)) const
{
    return this->staff_st.FindItem(staff, func);
}

void DataBase::RemoveStaff(const int& index, const bool& flag)
{
    Staff staff = this->staff_st.GetItem(index);
    this->staff_st.RemoveItem(index);

    this->table = Table::STAFF;
    this->action = Action::DELETE;

    QString profession;

    if (staff.GetProfession() == Profession::PILOT)
        profession = "Пилот";
    else if (staff.GetProfession() == Profession::ATTENDANT)
        profession = "Бортпроводник";
    else if (staff.GetProfession() == Profession::ENGINEER)
        profession = "Инженер";

    this->data = staff.GetNumCertificate() + "*" +
                 staff.GetSurname() + "*" +
                 staff.GetName() + "*" +
                 staff.GetPatronym() + "*" +
                 profession;
    this->index = index * 10 + 3;

    this->count++;

    if (flag)
        emit ChangeStaff();
}

void DataBase::UpdateStaff(const Staff& value, const int& index, const bool& flag)
{
    Staff staff = this->staff_st.GetItem(index);
    this->staff_st.UpdateItem(value, index);

    this->table = Table::STAFF;
    this->action = Action::UPDATE;

    QString profession;

    if (staff.GetProfession() == Profession::PILOT)
        profession = "Пилот";
    else if (staff.GetProfession() == Profession::ATTENDANT)
        profession = "Бортпроводник";
    else if (staff.GetProfession() == Profession::ENGINEER)
        profession = "Инженер";

    QString new_profession;

    if (value.GetProfession() == Profession::PILOT)
        new_profession = "Пилот";
    else if (value.GetProfession() == Profession::ATTENDANT)
        new_profession = "Бортпроводник";
    else if (value.GetProfession() == Profession::ENGINEER)
        new_profession = "Инженер";

    this->data = staff.GetNumCertificate() + "*" +
                 staff.GetSurname() + "*" +
                 staff.GetName() + "*" +
                 staff.GetPatronym() + "*" +
                 profession + "*" +
                 value.GetNumCertificate() + "*" +
                 value.GetSurname() + "*" +
                 value.GetName() + "*" +
                 value.GetPatronym() + "*" +
                 new_profession;

    this->index = index * 10 + 2;

    this->count++;

    if (flag)
        emit ChangeStaff();
}

unsigned DataBase::GetStaffSize() const
{
    return this->staff_st.GetSize();
}

void DataBase::AddTicket(const Ticket& ticket, const bool& flag)
{
    this->ticket_st.AddItem(ticket);

    this->table = Table::TICKET;
    this->action = Action::INSERT;
    this->index = (this->ticket_st.GetSize() - 1) * 10 + 1;
    this->data = ticket.GetNumTicket() + "*" +
                 ticket.GetNumPassport() + "*" +
                 ticket.GetNumFlight();

    this->count++;

    if (flag)
        emit ChangeTicket();
}

Ticket DataBase::GetTicket(const int& index) const
{
    return this->ticket_st.GetItem(index);
}

int DataBase::FindTicket(const Ticket& ticket, bool (*func)(const Ticket& cur, const Ticket& seek)) const
{
    return this->ticket_st.FindItem(ticket, func);
}

void DataBase::RemoveTicket(const int& index, const bool& flag)
{
    Ticket ticket = this->ticket_st.GetItem(index);
    this->ticket_st.RemoveItem(index);

    this->table = Table::TICKET;
    this->action = Action::DELETE;
    this->data = ticket.GetNumTicket() + "*" +
                 ticket.GetNumPassport() + "*" +
                 ticket.GetNumFlight();
    this->index = index * 10 + 3;

    this->count++;

    if (flag)
        emit ChangeTicket();
}

void DataBase::UpdateTicket(const Ticket& value, const int& index, const bool& flag)
{
    Ticket ticket = this->ticket_st.GetItem(index);
    this->ticket_st.UpdateItem(value, index);

    this->table = Table::TICKET;
    this->action = Action::UPDATE;
    this->data = ticket.GetNumTicket() + "*" +
                 ticket.GetNumPassport() + "*" +
                 ticket.GetNumFlight() + "*" +
                 value.GetNumTicket() + "*" +
                 value.GetNumPassport() + "*" +
                 value.GetNumFlight();

    this->index = index * 10 + 2;

    this->count++;

    if (flag)
        emit ChangeTicket();
}

unsigned DataBase::GetTicketSize() const
{
    return this->ticket_st.GetSize();
}
