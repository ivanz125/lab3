#include "ant.h"
#include "gamefield.h"

#include "behaviorgenerator.h"

Ant::Ant() : behavior(1)
{
}

Ant::Ant(GameField * field, Behavior behavior, int startRow, int startColumn) :
    gameField(field), behavior(behavior), rowPosition(startRow), columnPosition(startColumn), direction(WEST)
{
    eatenApples = 0;
    action = FRONT;
    direction = EAST;
}

Ant::Ant(GameField * field, int startRow, int startColumn) :
    gameField(field), behavior(7), rowPosition(startRow), columnPosition(startColumn), direction(WEST)
{
    eatenApples = 0;
    action = FRONT;
    direction = EAST;
    BehaviorGenerator bGen(*gameField, startRow, startColumn);
    initBehavior(bGen);
}

void Ant::operator=(const Ant & a)
{
    behavior = a.behavior;
    direction = a.direction;
    action = a.action;
    gameField = a.gameField;
    columnPosition = a.columnPosition;
    rowPosition = a.rowPosition;
    eatenApples = a.eatenApples;
}

void Ant::move()
{
    action = behavior.choseAction(isFoodInFront());
    if (gameField->isFoodCell(rowPosition, columnPosition))
    {
        gameField->deleteApple(rowPosition, columnPosition);
        eatenApples++;
    }
    switch (action)
    {
    case FRONT:
        gameField->directMove(direction, rowPosition, columnPosition);
        break;
    case LEFT:
        direction = gameField->leftDirection(direction);
        break;
    case RIGHT:
        direction = gameField->rightDirection(direction);
        break;
    case NOTHING:
        break;
    default:
        break;
    }

}

int Ant::eatenApplesCount()
{
    return eatenApples;
}

bool Ant::isFoodInFront()
{
    int frontRow = rowPosition;
    int frontColumn = columnPosition;
    gameField->directMove(direction, frontRow, frontColumn);
    return gameField->isFoodCell(frontRow, frontColumn);
}

void Ant::initBehavior(BehaviorGenerator & behaviorGenerator)
{
    behavior = behaviorGenerator.findBehavior();
    /*Behavior b(5);
    State s0(Transit(0, FRONT), Transit(1, RIGHT));
    State s1(Transit(0, FRONT), Transit(2, RIGHT));
    State s2(Transit(0, FRONT), Transit(3, RIGHT));
    State s3(Transit(0, FRONT), Transit(4, RIGHT));
    State s4(Transit(0, FRONT), Transit(0, FRONT));
    b.currentState = s0;
    b.states[0] = s0;
    b.states[1] = s1;
    b.states[2] = s2;
    b.states[3] = s3;
    b.states[4] = s4;
    behavior = b;*/
}

void Ant::getPosition(int & row, int & col)
{
    row = rowPosition;
    col = columnPosition;
}
