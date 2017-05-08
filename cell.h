#ifndef CELL_H
#define CELL_H

enum CellType {
    EMPTY,
    APPLE,
    APPLEWAY,
    PASSED,
    EATEN
};

class Cell {
public:
    Cell();
    Cell(bool isApple);

    void operator=(bool cell);
    void operator=(const Cell& cell);
    void operator=(CellType celltype);
    operator int();
    int cellFactor;

private:
    CellType type;
};

#endif // CELL_H
