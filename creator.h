#ifndef CREATOR_H
#define CREATOR_H

#include "memento.h"
#include "datastrategy.h"

class Creator
{
public:
    virtual ~Creator() {};
    virtual DataStrategy* FactoryMethod(const Table& table) = 0;
};

#endif // CREATOR_H
