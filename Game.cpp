#include <iostream>
#include <string>
#include "Position.h"
#include "Game.h"
#include "Player.h"
#include "MineGrid.h"
#include "gui.h"
#include <vector>

using namespace std;

Game::Game()
  : _player("wouter"), _minegrid(10,26,20) {}

Game::Game(string namePlayer, int rows, int columns, int mines)
        : _player(namePlayer), _minegrid(rows, columns, mines) {}

void Game::mark(Gui* guiPointer, int row, int column){

  if(_minegrid.getSurfaceGrid(row,column) == MARKED_RIGHT ||
     _minegrid.getSurfaceGrid(row,column) == MARKED_WRONG) {

    _minegrid.setSurfaceGrid(row, column, NOT_EXPOSED);
    //removes the Flag on the button
    guiPointer->getButton(row, column)->setUnExposed();

    _minegrid.setNumberOfMinesLeft(_minegrid.getNumberOfMinesLeft() + 1);
    checkForGameWon(guiPointer);

      }
  else if(_minegrid.getSurfaceGrid(row,column) == NOT_EXPOSED) {
     //mark the button with an F
     //and set the underlying surfaceGrid to MARKED_RIGHT
     // or MARKED_WRONG
     if(_minegrid.getPPGrid(row,column) == MINE) {
       _minegrid.setSurfaceGrid(row, column, MARKED_RIGHT);
     } else {
       _minegrid.setSurfaceGrid(row, column, MARKED_WRONG);
     }
     //! set flag on button
     guiPointer->getButton(row,column)->setMarked();

     _minegrid.setNumberOfMinesLeft(_minegrid.getNumberOfMinesLeft() - 1);
     checkForGameWon(guiPointer);

  }

  //if EXPOSED nothing happens
  //nothing happens to the button as well, it stays inactive

}

void Game::click(Gui* guiPointer,int row, int column){

  if(_minegrid.getSurfaceGrid(row, column) == EXPOSED)
    return;

  if(_minegrid.getPPGrid(row,column) == ZERO){
    _minegrid.exposeAdjacentZeroFields(guiPointer, row,column);
    //exposeAdjacentZeroFields also needs a pointer
    //to the gui
  } else if ( _minegrid.getPPGrid(row,column) == MINE){

    guiPointer->getButton(row,column)->setExposed("M");
    guiPointer->getButton(row,column)->setPalette(QPalette(Qt::green));
    for(int r = 0; r < _minegrid.getRows(); r++){
        for(int c = 0; c < _minegrid.getColumns(); c++){
            if(_minegrid.getSurfaceGrid(r,c) == NOT_EXPOSED &&
               _minegrid.getPPGrid(r,c) == MINE){
                guiPointer->getButton(r,c)->setPalette(QPalette(Qt::green));
                guiPointer->getButton(r,c)->setExposed("M");
            }

            if(_minegrid.getSurfaceGrid(r,c) == MARKED_WRONG){
                guiPointer->getButton(r,c)->setPalette(QPalette(Qt::red));
                guiPointer->getButton(r,c)->setExposed("X");
            }
            guiPointer->getButton(r,c)->setEnabled(false);
        }
    }
    guiPointer->getVictoryLabel()->setText("You lost");
    cout << "You stepped on a mine" << endl;

  } else {
    _minegrid.setSurfaceGrid(row, column, EXPOSED);
    //set exposed and set the make number of surrounding
    //mines visible
    guiPointer->getButton(row,column)->setExposed(
      QString::number(_minegrid.getPPGrid(row,column)));
  }
}
// this function clicks on all surrounding fields
// of the field that was double clicked
void Game::exposeSurroundingAndUnexposed(Gui * guiPointer, int r, int c){

  vector<Position> surroundingPositions;
  surroundingPositions.push_back(Position(r-1,c+1));
  surroundingPositions.push_back(Position(r-1,c));
  surroundingPositions.push_back(Position(r-1,c-1));
  surroundingPositions.push_back(Position(r,c+1));
  surroundingPositions.push_back(Position(r,c-1));
  surroundingPositions.push_back(Position(r+1,c+1));
  surroundingPositions.push_back(Position(r+1,c));
  surroundingPositions.push_back(Position(r+1,c-1));

  //a surrounding field is clicked, if and only if it has
  //a valid position and it is NOT_EXPOSED
  for (Position p: surroundingPositions){
      if (p.isValid(_minegrid.getRows(), _minegrid.getColumns())
          && _minegrid.getSurfaceGrid(p.getRow(), p.getColumn()) == NOT_EXPOSED){
          this->click(guiPointer, p.getRow(), p.getColumn());

      }
  }


}
void Game::checkForGameWon(Gui* guiPointer){

      guiPointer->getMinesLeftLabel()->setText(
     QString::number(_minegrid.getNumberOfMinesLeft()));

      // if number of mines left is zero
      // check if there are the same amount of MARKED_RIGHTS
      // as there are mines
      // and no MARKED_WRONGS
      if (_minegrid.getNumberOfMinesLeft() == 0){
        int markedRightCounter = 0;
          for(int r = 0; r < _minegrid.getRows(); r++){
              for(int c = 0; c < _minegrid.getColumns(); c++){
                 if (_minegrid.getSurfaceGrid(r,c) == MARKED_WRONG)
                     return;
                 if (_minegrid.getSurfaceGrid(r,c) == MARKED_RIGHT){
                     markedRightCounter++;
                 }
              }
          }
          if (markedRightCounter == _minegrid.getNumberOfMines()){
              guiPointer->getVictoryLabel()->setText("You have won!");
              // setAll button disabled
              for(int r = 0; r < _minegrid.getRows(); r++){
                  for(int c = 0 ; c < _minegrid.getColumns(); c++){
                      guiPointer->getButton(r,c)->setEnabled(false);
                  }
              }

          }
      }

}

