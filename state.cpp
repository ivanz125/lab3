#include "state.h"

State::State()
{
}

State::State(Transit foodT, Transit noFoodT)
{
    foodTransit = foodT;
    noFoodTransit = noFoodT;
}

void State::operator=(const State & state)
{
    foodTransit = state.foodTransit;
    noFoodTransit = state.noFoodTransit;
}

bool State::operator==(State state)
{
    if (foodTransit == state.foodTransit && noFoodTransit == state.noFoodTransit)
        return true;
    return false;
}

 int State::transition(bool food , Action& action)
{
    if (food) {
        action = foodTransit.action;
        return foodTransit.toState;
    }
    else {
        action = noFoodTransit.action;
        return noFoodTransit.toState;
    }

}
