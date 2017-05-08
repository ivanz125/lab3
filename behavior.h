#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "Action.h"
#include "state.h"
#include <QVector>

class Behavior
{
public:
    Behavior();
    Behavior(int states);
    Behavior(const Behavior &b);
    State currentState;
    QVector<State> states;
    void operator=(Behavior b);

    bool operator>(Behavior b);
    bool operator<(Behavior b);
    bool operator>=(Behavior b);
    bool operator<=(Behavior b);

    Action choseAction(bool isFoodInFront);
    int fitness;
};

#endif // BEHAVIOR_H
