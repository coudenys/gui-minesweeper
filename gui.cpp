#include "gui.h"
#include "button.h"
#include "Game.h"
#include <QtWidgets>
#include <vector>
using namespace std;

Gui::Gui(QWidget *parent)
        : QWidget(parent), _guiRows(30), _guiColumns(65),
          _guiMines(400),
          _game("wouter",_guiRows, _guiColumns, _guiMines)
{


   // ask for number of rows and columns

   for(int r = 0; r < _guiRows; r++){
       vector<Button*> row;
       _buttons.push_back(row);
   }

   for(int r = 0; r < _guiRows; r++){
       for(int c = 0; c < _guiColumns; c++){
           _buttons[r].push_back(new Button(&_game, this, r,c, ""));
       }
   }

   _buttonLayout = new QGridLayout;
   _buttonLayout->setHorizontalSpacing(0);
   _buttonLayout->setVerticalSpacing(0);

   for(int r = 0; r < _guiRows; r++){
       for(int c = 0; c < _guiColumns; c++){
           _buttonLayout->addWidget(_buttons[r][c], r, c);

       }
   }

   _minesLeftLabel = new QLabel(QString::number(_guiMines));
   _victoryLabel = new QLabel("You have not won yet");
   _statusLayout = new QHBoxLayout;
   _statusLayout->addWidget(new QLabel("Mines left:"));
   _statusLayout->addWidget(_minesLeftLabel);
   _statusLayout->addStretch();
   _statusLayout->addWidget(_victoryLabel);

   _mainLayout = new QGridLayout;
   _mainLayout->addLayout(_buttonLayout,0,0);
   _mainLayout->addLayout(_statusLayout,1,0);


   setLayout(_mainLayout);
   setWindowTitle("MineSweeper");

}

Gui::~Gui(){
    delete _buttonLayout;
    delete _mainLayout;
    delete _statusLayout;
    delete _minesLeftLabel;
    delete _victoryLabel;
    //is it necessary to delete a vector of pointers?


}

Button* Gui::getButton(int row, int column){
    return _buttons[row][column];

}

QLabel *Gui::getVictoryLabel()
{
   return _victoryLabel;
}

QLabel* Gui::getMinesLeftLabel(){
    return _minesLeftLabel;
}
