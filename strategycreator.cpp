#include "strategycreator.h"

#include "airportstrategy.h"

DataStrategy* StrategyCreator::FactoryMethod(const Table& table)
{
    Q_UNUSED(table);

    return new AirportStrategy;
}
