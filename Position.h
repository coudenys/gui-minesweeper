#ifndef POSITION_H
#define POSITION_H

class Position{

  public:
    Position(int row, int column);
    Position();

    static Position randomPosition(int rows, int columns);
    bool isValid(int height, int width);

    int getRow();
    int getColumn();

  private:
    int _row, _column;
};

#endif



