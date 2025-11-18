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
                                                [](const Airport& cur, const Airport& seek) { return cur.GetName() == seek.GetName(); });

            this->airport_st.RemoveItem(this->index);
        }
        else if (memento.GetAction() == Action::UPDATE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->airport_st.FindItem(Airport(str_list[5], 0, 0, 0, 0),
                                                [](const Airport& cur, const Airport& seek) { return cur.GetName() == seek.GetName(); });

            this->airport_st.UpdateItem(Airport(str_list[0], str_list[1].toInt(), str_list[2].toInt(), str_list[3].toInt(), str_list[4].toInt()),
                                        this->index);
        }
        else if (memento.GetAction() == Action::DELETE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->airport_st.AddItem(Airport(str_list[0], str_list[1].toInt(), str_list[2].toInt(), str_list[3].toInt(), str_list[4].toInt()));

            this->index = this->airport_st.GetSize() - 1;
        }
    }
    else if (memento.GetTable() == Table::PASSENGER)
    {
        if (memento.GetAction() == Action::INSERT)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->passenger_st.FindItem(Passenger(str_list[0], "", QDate(), "", "", "", QDate()),
                                                [](const Passenger& cur, const Passenger& seek) { return cur.GetNumPassport() == seek.GetNumPassport(); });

            this->passenger_st.RemoveItem(this->index);
        }
        else if (memento.GetAction() == Action::UPDATE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->passenger_st.FindItem(Passenger(str_list[7], "", QDate(), "", "", "", QDate()),
                                                [](const Passenger& cur, const Passenger& seek) { return cur.GetNumPassport() == seek.GetNumPassport(); });

            this->passenger_st.UpdateItem(Passenger(str_list[0], str_list[1], QDate::fromString(str_list[2]), str_list[3], str_list[4], str_list[5],
                                                    QDate::fromString(str_list[6])), this->index);
        }
        else if (memento.GetAction() == Action::DELETE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->passenger_st.AddItem(Passenger(str_list[0], str_list[1], QDate::fromString(str_list[2]), str_list[3], str_list[4], str_list[5],
                                                 QDate::fromString(str_list[6])));

            this->index = this->passenger_st.GetSize() - 1;
        }
    }
    else if (memento.GetTable() == Table::TICKET)
    {
        if (memento.GetAction() == Action::INSERT)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->ticket_st.FindItem(Ticket(str_list[0], "", ""),
                                                  [](const Ticket& cur, const Ticket& seek) { return cur.GetNumTicket() == seek.GetNumTicket(); });

            this->ticket_st.RemoveItem(this->index);
        }
        else if (memento.GetAction() == Action::UPDATE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->ticket_st.FindItem(Ticket(str_list[3], "", ""),
                                                  [](const Ticket& cur, const Ticket& seek) { return cur.GetNumTicket() == seek.GetNumTicket(); });

            this->ticket_st.UpdateItem(Ticket(str_list[0], str_list[1], str_list[2]), this->index);
        }
        else if (memento.GetAction() == Action::DELETE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->ticket_st.AddItem(Ticket(str_list[0], str_list[1], str_list[2]));

            this->index = this->ticket_st.GetSize() - 1;
        }
    }
    else if (memento.GetTable() == Table::FLIGHT)
    {
        if (memento.GetAction() == Action::INSERT)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->flight_st.FindItem(Flight(str_list[0], "", "", "", QDate(), QTime(), FlightState::ON_TIME, 0, 0),
                                                   [](const Flight& cur, const Flight& seek) { return cur.GetNumFlight() == seek.GetNumFlight(); });

            this->flight_st.RemoveItem(this->index);
        }
        else if (memento.GetAction() == Action::UPDATE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->flight_st.FindItem(Flight(str_list[9], "", "", "", QDate(), QTime(), FlightState::ON_TIME, 0, 0),
                                                   [](const Flight& cur, const Flight& seek) { return cur.GetNumFlight() == seek.GetNumFlight(); });

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

            this->flight_st.UpdateItem(Flight(str_list[0], str_list[1], str_list[2], str_list[3], QDate::fromString(str_list[4]),
                                              QTime::fromString(str_list[5]), state, str_list[7].toInt(), str_list[8].toInt()), this->index);
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

            this->flight_st.AddItem(Flight(str_list[0], str_list[1], str_list[2], str_list[3], QDate::fromString(str_list[4]),
                                           QTime::fromString(str_list[5]), state, str_list[7].toInt(), str_list[8].toInt()));

            this->index = this->flight_st.GetSize() - 1;
        }
    }
    else if (memento.GetTable() == Table::STAFF)
    {
        if (memento.GetAction() == Action::INSERT)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->staff_st.FindItem(Staff(str_list[0], "", "", "", Profession::PILOT),
                                                   [](const Staff& cur, const Staff& seek) { return cur.GetNumCertificate() == seek.GetNumCertificate(); });

            this->staff_st.RemoveItem(this->index);
        }
        else if (memento.GetAction() == Action::UPDATE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->staff_st.FindItem(Staff(str_list[5], "", "", "", Profession::PILOT),
                                                   [](const Staff& cur, const Staff& seek) { return cur.GetNumCertificate() == seek.GetNumCertificate(); });

            Profession profession;

            if (str_list[4] == "Пилот")
                profession = Profession::PILOT;
            else if (str_list[4] == "Бортпроводник")
                profession = Profession::ATTENDANT;
            else if (str_list[4] == "Инженер")
                profession = Profession::ENGINEER;

            this->staff_st.UpdateItem(Staff(str_list[0], str_list[1], str_list[2], str_list[3], profession), this->index);
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

            this->index = this->staff_st.GetSize() - 1;
        }
    }
    else if (memento.GetTable() == Table::PURPOSE)
    {
        if (memento.GetAction() == Action::INSERT)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->staff_st.FindItem(Staff(str_list[0], "", "", "", Profession::PILOT),
                                                  [](const Staff& cur, const Staff& seek) { return cur.GetNumCertificate() == seek.GetNumCertificate(); });

            this->staff_st.RemoveItem(this->index);
        }
        else if (memento.GetAction() == Action::UPDATE)
        {
            QStringList str_list = memento.GetData().split('*', Qt::SkipEmptyParts);

            this->index = this->purpose_st.FindItem(Purpose(Nomination::FIRST_PILOT, str_list[4], str_list[5]),
                                                  [](const Purpose& cur, const Purpose& seek)
                                                    {
                                                        return cur.GetNumFlight() == seek.GetNumFlight() &&
                                                               cur.GetNumCertificate() == seek.GetNumCertificate();
                                                    });

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

            this->purpose_st.UpdateItem(Purpose(nomination, str_list[1], str_list[2]), this->index);
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

            this->index = this->purpose_st.GetSize() - 1;
        }
    }
}

Memento DataBase::GetLastState() const
{

}

void DataBase::Load()
{
    this->connection->Load(&this->airport_st, &this->flight_st, &this->passenger_st, &this->purpose_st, &this->staff_st, &this->ticket_st);
}

void DataBase::AddAirport(const Airport& airport, const bool& flag)
{

}

Airport DataBase::GetAirport(const int& index) const
{
    return this->airport_st.GetItem(index);
}

int DataBase::FindAirport(const Airport& airport, bool (*func)(const Airport& cur, const Airport& seek)) const
{

}

void DataBase::RemoveAirport(const int& index, const bool& flag)
{

}

void DataBase::UpdateAirport(const Airport& value, const int& index, const bool& flag)
{

}

unsigned DataBase::GetAirportSize() const
{
    return this->airport_st.GetSize();
}
