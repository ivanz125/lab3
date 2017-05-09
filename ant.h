#ifndef ANT_H
#define ANT_H

#include "Direction.h"
#include "behavior.h"

class BehaviorGenerator;
class GameField;

class Ant
{
public:
    Ant();
    Ant(GameField *field, Behavior behavior, int startRow, int startColumn);
    Ant(GameField *field, int startRow, int startColumn);
    void operator=(const Ant& a);
    void move();
    int eatenApplesCount();
    bool isFoodInFront();
    void initBehavior(BehaviorGenerator & behaviorGenerator);
    void getPosition(int &row, int &col);
    Direction getDirection();
private:
    Behavior  behavior;
    Direction  direction;
    Action action;
    GameField*  gameField;
    int columnPosition;
    int  rowPosition;
    int eatenApples;
};

#endif // ANT_H
