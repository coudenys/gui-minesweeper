#ifndef GUI_H
#define GUI_H
#include <vector>
#include "button.h"
#include "Game.h"

using namespace std;

class Gui: public QWidget {
    Q_OBJECT
public:
      Gui(QWidget *parent = 0);
      ~Gui();
      Button* getButton(int, int);
      QLabel* getVictoryLabel();
      QLabel* getMinesLeftLabel();

private:
      int _guiRows;
      int _guiColumns;
      int _guiMines;
      QLabel* _victoryLabel;
      QLabel* _minesLeftLabel;
      QHBoxLayout *_statusLayout;
      QGridLayout *_buttonLayout;
      QGridLayout *_mainLayout;
      vector<vector<Button*> > _buttons;
      Game _game;



};


#endif // GUI_H
