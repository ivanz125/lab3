#include "transit.h"

Transit::Transit()
 {
     action = NOTHING;
     toState = 0;
 }

Transit::Transit(int toState, Action action)
{
    this->toState = toState;
    this->action = action;
}

void Transit::operator=(const Transit & t)
{
    toState = t.toState;
    action = t.action;
}

bool Transit::operator==(Transit t)
{
    if (action == t.action && toState == t.toState)
        return true;
    return false;
}
