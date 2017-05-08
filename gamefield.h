#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "ant.h"
#include "cell.h"
#include "fieldgenerator.h"
#include <QDebug>

#define FIELD_SIZE 32
#define APPLES_COUNT 89

class GameField
{
public:
    GameField(int startRow, int startColumn);

    void operator=(const GameField & g);
    void updateField();
    void initAnt(BehaviorGenerator &bGen);

    int correctIndex(int index);
    int applesCount();

    void getStartPosition(int &row, int &column);
    void reinit();

    void directMove(Direction direction, int& row, int &column);
    Direction leftDirection(Direction d);
    Direction rightDirection(Direction d);

    bool isFoodCell(int row, int column);
    void deleteApple(int row, int column);
    bool isApplesExist();

    Cell** getCells();

private:
    Ant ant;
    int startRow;
    int startColumn;
    int apples;
    Cell** cells;
};

#endif // GAMEFIELD_H
