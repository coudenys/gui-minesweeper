#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include <string>

class Gui;

using namespace std;
class Game{
  public:
    Game();
    Game(string player, int rows, int columns, int mines);

    //mark is called on a right-click
    void mark(Gui*, int, int);
    //click is called on a left-click
    void click(Gui*,int , int);
    //is called on double-click
    void exposeSurroundingAndUnexposed(Gui*, int row, int column);

    MineGrid getMineGrid();
  private:
    void checkForGameWon(Gui*);

    Player _player;
    MineGrid _minegrid;


};

#endif 
