#include "gamefield.h"

GameField::GameField(int startRow, int startColumn)
{
    this->startColumn = startColumn;
    this->startRow = startRow;

    cells = new Cell*[FIELD_SIZE];
    for (int i = 0; i < FIELD_SIZE; i++)
        cells[i] = new Cell[FIELD_SIZE];

    FieldGenerator fGen(cells);

    apples = applesCount();
    cells[startRow][startColumn] = PASSED;

    ant = Ant(this, startRow, startColumn);
}

void GameField::operator=(const GameField & field)
{
    startRow = field.startRow;
    startColumn = field.startColumn;
    ant = field.ant;
    for (int i = 0; i < FIELD_SIZE; i++)
        for (int j = 0; j < FIELD_SIZE; j++)
            cells[i][j] = field.cells[i][j];
}

void GameField::updateField()
{
    int rowP, colP;
    ant.getPosition(rowP, colP);
    cells[rowP][colP] = EMPTY;
    ant.move();
    ant.getPosition(rowP, colP);
    cells[rowP][colP] = PASSED;
}

void GameField::initAnt(BehaviorGenerator & behaviorGenerator)
{
    ant.initBehavior(behaviorGenerator);
}

int GameField::correctIndex(int index)
{
    if (index < 0) index += FIELD_SIZE;
    return index % FIELD_SIZE;
}

int GameField::applesCount()
{
    int apples = 0;
    for (int i = 0; i < FIELD_SIZE; i++)
        for (int j = 0; j < FIELD_SIZE; j++)
            if (cells[i][j] == APPLE) apples++;
    return apples;
}

void GameField::getStartPosition(int & row, int & column)
{
    row = startRow;
    column = startColumn;
}

void GameField::reinit()
{
    apples = applesCount();
    cells[startRow][startColumn] = PASSED;

    ant = Ant(this, startRow, startColumn);
}



void GameField::directMove(Direction direction, int & row, int & col)
{
    switch (direction)
    {
        case NORTH: row = correctIndex(row - 1); break;
        case SOUTH: row = correctIndex(row + 1); break;
        case EAST: col = correctIndex(col - 1); break;
        case WEST: col = correctIndex(col + 1); break;
    }
}

Direction GameField::leftDirection(Direction d)
{
    switch (d){
        case NORTH: return EAST;
        case SOUTH: return WEST;
        case EAST: return SOUTH;
        defaut: return NORTH;
    }
}

Direction GameField::rightDirection(Direction d)
{
    switch (d){
        case NORTH: return WEST;
        case SOUTH: return EAST;
        case EAST: return NORTH;
        default: return SOUTH;
    }
}

bool GameField::isFoodCell(int row, int column)
{
   return cells[row][column] == APPLE;
}

void GameField::deleteApple(int row, int column)
{
   cells[row][column] = EMPTY;
   apples--;
}

bool GameField::isApplesExist()
{
   return ant.eatenApplesCount() < APPLES_COUNT;
}

Cell** GameField::getCells()
{
    return cells;
}
