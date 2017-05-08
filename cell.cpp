#include "cell.h"

Cell::Cell() : type(EMPTY), cellFactor(0)
{
}

Cell::Cell(bool isApple) : type(CellType(isApple)), cellFactor(0)
{
}

void Cell::operator=(bool cell)
{
    type = (CellType)cell;
}

void Cell::operator=(const Cell & cell)
{
    type = cell.type;
    cellFactor = cell.cellFactor;
}

void Cell::operator=(CellType celltype)
{
    type = celltype;
}


Cell::operator int()
{
    return (int)type;
}
