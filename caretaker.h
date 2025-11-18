#ifndef CARETAKER_H
#define CARETAKER_H

#include <QList>
#include "memento.h"

class Caretaker
{
private:
    QList<Memento> states;
public:
    Caretaker();
    void AddState(const Memento& state);
    Memento GetFirst();
    Memento GetLast();
    bool IsEmpty() const;
};

#endif // CARETAKER_H
