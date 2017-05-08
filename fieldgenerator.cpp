#include "fieldgenerator.h"

#include "cell.h"

// This constructor generates exactly the same field as in lab task
FieldGenerator::FieldGenerator(Cell** cells)
{
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++)
            cells[i][j] = EMPTY;

    for (int i = 1; i <= 10; i++) cells[0][i] = APPLE;
    for (int i = 1; i <= 10; i++) cells[i][10] = APPLE;
    for (int i = 10; i >= 3; i--) cells[10][i] = APPLE;
    for (int i = 9; i >= 5; i--) cells[i][3] = APPLE;
    for (int i = 3; i >= 0; i--) cells[5][i] = APPLE;
    // map break (on image)
    for (int i = 31; i >= 25; i--) cells[5][i] = APPLE;
    cells[5][24] = APPLEWAY;
    for (int i = 6; i <= 10; i++) cells[i][24] = APPLE;
    cells[11][24] = APPLEWAY;
    for (int i = 23; i >= 19; i--) cells[11][i] = APPLE;
    cells[11][18] = APPLEWAY;
    for (int i = 12; i <= 17; i++) cells[i][18] = APPLE;
    cells[18][18] = APPLEWAY;
    cells[19][18] = APPLEWAY;
    for (int i = 20; i <= 25; i++) cells[i][18] = APPLE;
    cells[26][18] = APPLEWAY;
    cells[27][18] = APPLEWAY;
    for (int i = 17; i >= 12; i--) cells[27][i] = APPLE;
    cells[27][11] = APPLEWAY;
    for (int i = 10; i >= 7; i--) cells[27][i] = APPLE;
    cells[27][6] = APPLEWAY;
    cells[27][5] = APPLEWAY;
    for (int i = 27; i >= 24; i--) cells[i][4] = APPLE;
    // Now APPLEWAY in for-loop
    cells[23][4] = APPLEWAY;
    cells[22][4] = APPLEWAY;
    cells[22][5] = APPLE;
    cells[22][6] = APPLEWAY;
    cells[22][7] = APPLEWAY;
    cells[21][7] = APPLE;

    for (int i = 20; i >= 18; i--) cells[i][7] = APPLEWAY;
    cells[18][8] = APPLE;
    for (int i = 9; i <= 11; i++) cells[18][i] = APPLEWAY;
    cells[17][11] = APPLE;
    for (int i = 16; i >= 15; i--) cells[i][11] = APPLEWAY;
    cells[15][12] = APPLE;
    for (int i = 13; i <= 15; i++) cells[15][i] = APPLEWAY;
    cells[14][15] = APPLE;
    for (int i = 13; i >= 12; i--) cells[i][15] = APPLEWAY;
    cells[12][14] = APPLE;
    for (int i = 13; i >= 11; i--) cells[12][i] = APPLEWAY;
    cells[11][11] = APPLE;
    for (int i = 10; i >= 8; i--) cells[i][11] = APPLEWAY;
    cells[8][12] = APPLE;
    for (int i = 13; i <= 14; i++) cells[8][i] = APPLEWAY;
    cells[7][14] = APPLE;
    for (int i = 6; i >= 4; i--) cells[i][14] = APPLEWAY;
    cells[4][15] = APPLE;
}
