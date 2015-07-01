#ifndef GRID_H
#define GRID_H
/*
 * this is just a grid
 * that can be filled with integers
 */
class Grid{

  public:
    Grid();
    Grid(int rows, int columns);
    virtual ~Grid();

    static void fill(int**,int rows, int columns, int fillage);

    int getRows();
    int getColumns();
    
  protected:
    // p_p stands for pointer to pointer
    // that is the underlying structure of the grid
    int** _p_p_grid;
    int _rows, _columns;
};

#endif


