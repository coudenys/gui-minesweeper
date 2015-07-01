#include <iostream>
#include "Grid.h"

using namespace std;

Grid::Grid(int rows, int columns)
: _rows(rows), _columns(columns) {
  _p_p_grid = new int*[rows];
  for(int r = 0; r < rows; r++)
    _p_p_grid[r] = new int[columns];

  fill(_p_p_grid, rows, columns, 0);
}

Grid::Grid()
  : Grid(10,26) {}

Grid::~Grid(){
  cout << "Deleting Grid" << endl;
  for(int r = 0; r < _rows; r++){
    delete[] _p_p_grid[r];
  }
  delete[] _p_p_grid;

}

void Grid::fill(int** p_p_grid, int rows, int columns, int x){
  for(int r = 0; r < rows; r++)
    for(int c = 0; c < columns; c++)
      p_p_grid[r][c] = x;
}

int Grid::getRows(){
  return _rows;
}

int Grid::getColumns(){
  return _columns;
}
