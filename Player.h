#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "MineGrid.h"

using namespace std;

class Player{

  public:
    Player(string name);
    Player();
  private:
    string _name;

};

#endif

