#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
#include "connection.h"
#include "storage.h"
#include "memento.h"

class DataBase : public QObject
{
    Q_OBJECT

private:
    Connection* connection;
    unsigned count;
    Table table;
    Action action;
    QString data;
    unsigned index;
    bool state;
    Storage<Airport> airport_st;
    Storage<Flight> flight_st;
    Storage<Passenger> passenger_st;
    Storage<Purpose> purpose_st;
    Storage<Staff> staff_st;
    Storage<Ticket> ticket_st;
public:
    DataBase(const QString& db_name);
    ~DataBase();
    unsigned GetIndex() const;
    void Save(const Memento& memento) const;
    void SetPreviousState(const Memento& memento);
    Memento GetLastState();
    void Load();
    void ChangeState(const bool flag);
    void AddAirport(const Airport& airport, const bool& flag);
    Airport GetAirport(const int& index) const;
    int FindAirport(const Airport& airport, bool (*func)(const Airport& cur, const Airport& seek)) const;
    void RemoveAirport(const int& index, const bool& flag);
    void UpdateAirport(const Airport& value, const int& index, const bool& flag);
    unsigned GetAirportSize() const;
    void AddFlight(const Flight& flight, const bool& flag);
    Flight GetFlight(const int& index) const;
    int FindFlight(const Flight& flight, bool (*func)(const Flight& cur, const Flight& seek)) const;
    void RemoveFlight(const int& index, const bool& flag);
    void UpdateFlight(const Flight& value, const int& index, const bool& flag);
    unsigned GetFlightSize() const;
    void AddPassenger(const Passenger& passenger, const bool& flag);
    Passenger GetPassenger(const int& index) const;
    int FindPassenger(const Passenger& passenger, bool (*func)(const Passenger& cur, const Passenger& seek)) const;
    void RemovePassenger(const int& index, const bool& flag);
    void UpdatePassenger(const Passenger& value, const int& index, const bool& flag);
    unsigned GetPassengerSize() const;
    void AddPurpose(const Purpose& purpose, const bool& flag);
    Purpose GetPurpose(const int& index) const;
    int FindPurpose(const Purpose& purpose, bool (*func)(const Purpose& cur, const Purpose& seek)) const;
    void RemovePurpose(const int& index, const bool& flag);
    void UpdatePurpose(const Purpose& value, const int& index, const bool& flag);
    unsigned GetPurposeSize() const;
    void AddStaff(const Staff& staff, const bool& flag);
    Staff GetStaff(const int& index) const;
    int FindStaff(const Staff& staff, bool (*func)(const Staff& cur, const Staff& seek)) const;
    void RemoveStaff(const int& index, const bool& flag);
    void UpdateStaff(const Staff& value, const int& index, const bool& flag);
    unsigned GetStaffSize() const;
    void AddTicket(const Ticket& ticket, const bool& flag);
    Ticket GetTicket(const int& index) const;
    int FindTicket(const Ticket& ticket, bool (*func)(const Ticket& cur, const Ticket& seek)) const;
    void RemoveTicket(const int& index, const bool& flag);
    void UpdateTicket(const Ticket& value, const int& index, const bool& flag);
    unsigned GetTicketSize() const;
signals:
    void ChangeAirport();
    void ChangeFlight();
    void ChangePassenger();
    void ChangePurpose();
    void ChangeStaff();
    void ChangeTicket();
    void Reload();
    void NotifyCaretaker();
};

#endif // DATABASE_H
