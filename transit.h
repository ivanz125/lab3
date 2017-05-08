#ifndef TRANSIT_H
#define TRANSIT_H

#include "Action.h"

class Transit
{
public:
    Transit();
    Transit(int toState, Action action);
    void operator=(const Transit &t);
    bool operator==(Transit t);
    Action  action;
    int  toState;
};

#endif // TRANSIT_H
