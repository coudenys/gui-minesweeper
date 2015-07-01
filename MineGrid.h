#ifndef MINEGRID_H
#define MINEGRID_H

#include "Grid.h"

class Gui;

enum Number{ ZERO, ONE, TWO, THREE, FOUR, FIVE,
             SIX, SEVEN, EIGHT, MINE };

enum Flag { MARKED_RIGHT, MARKED_WRONG, EXPOSED, NOT_EXPOSED };
/*
 * A minegrid exist of an underlying grid, in which each field
 * contains either a mine or the number of surrounding mines
 * AND
 * a surface grid that keeps track of visualization of the
 * mine field
 */
class MineGrid: public Grid{
  
  public:
    MineGrid(int rows, int columns, int numberOfMines);
    MineGrid();
    ~MineGrid();
    

    void setSurfaceGrid(int row, int column, Flag f);
    int getSurfaceGrid(int row, int column);

    int getPPGrid(int row, int column);

    void exposeAdjacentZeroFields(Gui*, int row, int column);

    int getNumberOfMines();

    int getNumberOfMinesLeft();
    void setNumberOfMinesLeft(int);

  private:
    int** _surfaceGrid;
    int _numberOfMines;
    int _numberOfMinesLeft;

};

#endif
