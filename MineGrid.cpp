#include <iostream>
#include <vector>
#include "Grid.h"
#include "MineGrid.h"
#include "Position.h"
#include "gui.h"

using namespace std;

MineGrid::MineGrid(int rows, int columns, int numberOfMines)
  : Grid(rows, columns), _numberOfMines(numberOfMines)
  , _numberOfMinesLeft(_numberOfMines)
{
  //make 2D-array for surfaceGrid
  _surfaceGrid = new int*[rows];
  for(int r = 0; r < rows; r++)
    _surfaceGrid[r] = new int[columns];

  fill(_surfaceGrid, rows, columns, NOT_EXPOSED);
  
  //fill with mines and initialize
  //grid
  //e.g.:
  //1 1 2 M
  //1 M 2 1
  //1 1 1 0

  //spreads the mines onto the minefield until
  //the desired number of mines is reached
  int currentNumberOfMines = 0;
  while (currentNumberOfMines < numberOfMines){
    Position randPos = Position::randomPosition(rows,columns);
    //if there is not already a mine at that coordinate
    //plant one
    if (_p_p_grid[randPos.getRow()][randPos.getColumn()] != MINE){
      _p_p_grid[randPos.getRow()][randPos.getColumn()] = MINE;
      currentNumberOfMines++;
    }
  }
  //for all fields that are not mines
  //set the number of surrounding mines
  for(int r = 0; r < _rows; r++){
    for(int c = 0; c < _columns; c++){
      //skips the coordinate if there is a mine
      if(_p_p_grid[r][c] == MINE)
        continue;
      
      int mineCount = 0;
      //stores all surrounding positions in this
      //vector of size 8
      vector<Position> surroundingPositions;
      surroundingPositions.push_back(Position(r-1,c+1));
      surroundingPositions.push_back(Position(r-1,c));
      surroundingPositions.push_back(Position(r-1,c-1));
      surroundingPositions.push_back(Position(r,c+1));
      surroundingPositions.push_back(Position(r,c-1));
      surroundingPositions.push_back(Position(r+1,c+1));
      surroundingPositions.push_back(Position(r+1,c));
      surroundingPositions.push_back(Position(r+1,c-1));

      //checks all surrounding positions,
      //the mineCount increments if the surroundPosition
      //isValid AND is a mine
      for(Position p: surroundingPositions){
        if(p.isValid(_rows, _columns) &&
           _p_p_grid[p.getRow()][p.getColumn()] == MINE){
          mineCount++;
        }
      }
      //finally, the number of surrounding mines is set to the
      //grid
      _p_p_grid[r][c] = mineCount;

    }
  }

}
//default constructor, not used
MineGrid::MineGrid()
  : MineGrid(10,26,3) {}

//deletes all pointers to the heap
MineGrid::~MineGrid(){
  cout << "Deleting MineGrid" << endl;
  for(int r = 0; r < _rows; r++){
    delete[] _surfaceGrid[r];
  }
  delete[] _surfaceGrid;

}

void MineGrid::setSurfaceGrid(int row, int column, Flag f){
  _surfaceGrid[row][column] = f;
}

int MineGrid::getSurfaceGrid(int row, int column){
  return _surfaceGrid[row][column];
}

int MineGrid::getPPGrid(int row, int column){
  return _p_p_grid[row][column];
}

//this recursive functions exposes all the surrounding fields
//of a zero field
//if one of these surrounding fields is also a zero
//the same will happen
void MineGrid::exposeAdjacentZeroFields(Gui* guiPointer, int r, int c){
  
  //this if statement is very important
  //otherwise: infinite recursive loop
  //this is the base case
  if(_surfaceGrid[r][c] == EXPOSED)
    return;

  vector<Position> surroundingPositions;
  surroundingPositions.push_back(Position(r-1,c+1));
  surroundingPositions.push_back(Position(r-1,c));
  surroundingPositions.push_back(Position(r-1,c-1));
  surroundingPositions.push_back(Position(r,c+1));
  surroundingPositions.push_back(Position(r,c-1));
  surroundingPositions.push_back(Position(r+1,c+1));
  surroundingPositions.push_back(Position(r+1,c));
  surroundingPositions.push_back(Position(r+1,c-1));

  //sets surfacegrid to the number of surrounding mines
  for(Position p: surroundingPositions){
    if(p.isValid(_rows,_columns) &&
        _surfaceGrid[p.getRow()][p.getColumn()] != EXPOSED &&
        _p_p_grid[p.getRow()][p.getColumn()] > 0 && //not ZERO
        _p_p_grid[p.getRow()][p.getColumn()] < 9 ) { // not a MINE, enum of MINE corresponds to 9
      setSurfaceGrid(p.getRow(), p.getColumn(), EXPOSED);
      guiPointer->getButton(p.getRow(), p.getColumn())
        ->setExposed(QString::number(_p_p_grid
        [p.getRow()][p.getColumn()]));

    }
    //if that number is ZERO, then : recursive call
    else if(p.isValid(_rows, _columns) &&
       _p_p_grid[p.getRow()][p.getColumn()] == ZERO){
      setSurfaceGrid(r,c, EXPOSED);
      guiPointer->getButton(r,c)->setExposed("");
      exposeAdjacentZeroFields(guiPointer, p.getRow(), p.getColumn());
    }

  }
}

MineGrid Game::getMineGrid(){
    return _minegrid;
}
  
int MineGrid::getNumberOfMines(){
    return _numberOfMines;
}

int MineGrid::getNumberOfMinesLeft(){
    return _numberOfMinesLeft;
}

void MineGrid::setNumberOfMinesLeft(int n){
    _numberOfMinesLeft = n;

}


