#include <string>
#include <iostream>
#include "MineGrid.h"
#include "Player.h"

using namespace std;

Player::Player()
  : _name("wouter") {
  }

Player::Player(string name)
  : _name(name) {
  }
