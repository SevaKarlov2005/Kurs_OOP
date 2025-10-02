#include "caretaker.h"

Caretaker::Caretaker()
{

}

void Caretaker::AddState(const Memento& state)
{
    this->states.push_back(state);
}

Memento Caretaker::GetFirst()
{
    return this->states.takeFirst();
}

Memento Caretaker::GetLast()
{
    return this->states.takeLast();
}

bool Caretaker::IsEmpty()
{
    return this->states.isEmpty();
}
