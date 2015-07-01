#include <iostream>
#include <cstdlib>
#include "Position.h"

using namespace std;

Position::Position(int row, int column)
  : _row(row), _column(column) {
  }

Position::Position()
  : _row(0), _column(0) {}

bool Position::isValid(int rows, int columns){
  if(_row < 0 || _column < 0)
    return false;

  if(_row >= rows || _column >= columns)
    return false;

  return true;
}

//static method that return a random position
//within the confines of the minefield
Position Position::randomPosition(int rows, int columns){
  int r = rand() % rows;
  int c = rand() % columns;

  return Position(r,c);
}

int Position::getRow(){
  return _row;
}

int Position::getColumn(){
  return _column;
}
