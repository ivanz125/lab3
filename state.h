#ifndef STATE_H
#define STATE_H

#define STATE_COUNT 7

#include "transit.h"

class State
{
public:
    State();
    State(Transit foodT, Transit noFoodT);
    void operator=(const State &state);
    Transit  foodTransit;
    Transit  noFoodTransit;
    bool operator==(State state);
    int transition(bool food , Action& action);
};

#endif // STATE_H
