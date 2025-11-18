#include "strategycreator.h"

#include "airportstrategy.h"
#include "flightstrategy.h"
#include "passengerstrategy.h"
#include "staffstrategy.h"
#include "purposestrategy.h"
#include "ticketstrategy.h"

DataStrategy* StrategyCreator::FactoryMethod(const Table& table) const
{
    if (table == Table::AIRPORT)
        return new AirportStrategy;
    else if (table == Table::FLIGHT)
        return new FlightStrategy;
    else if (table == Table::PASSENGER)
        return new PassengerStrategy;
    else if (table == Table::STAFF)
        return new StaffStrategy;
    else if (table == Table::PURPOSE)
        return new PurposeStrategy;
    else if (table == Table::TICKET)
        return new TicketStrategy;
    else
        return NULL;
}
