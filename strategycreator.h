#ifndef STRATEGYCREATOR_H
#define STRATEGYCREATOR_H

#include "creator.h"

class StrategyCreator : public Creator
{
public:
    DataStrategy* FactoryMethod(const Table& table) override;
};

#endif // STRATEGYCREATOR_H
