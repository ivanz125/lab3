#include "behavior.h"

Behavior::Behavior(){}

Behavior::Behavior(int numStates)
{
    states.resize(numStates);
    currentState = states[0];
    fitness = -1;
}

Behavior::Behavior(const Behavior & b)
{
    states.resize(b.states.size());
    currentState = b.currentState;
    for (int i = 0; i < b.states.size(); i++)
        states[i] = b.states[i];
    fitness = b.fitness;
}

void Behavior::operator=(Behavior b)
{
    states.resize(b.states.size());
    currentState = b.currentState;
    for (int i = 0; i < b.states.size(); i++)
        states[i] = b.states[i];
    fitness = b.fitness;
}

bool Behavior::operator>(Behavior b)
{
    return fitness > b.fitness;
}

bool Behavior::operator<(Behavior b)
{
    return fitness < b.fitness;
}

bool Behavior::operator>=(Behavior b)
{
    return fitness >= b.fitness;
}

bool Behavior::operator<=(Behavior b)
{
    return fitness >= b.fitness;
}

Action Behavior::choseAction(bool isFoodInFront)
{
    Action a;
    currentState = states[currentState.transition(isFoodInFront, a)];
    return a;
}
