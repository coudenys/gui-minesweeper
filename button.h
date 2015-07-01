#ifndef BUTTON_H
#define BUTTON_H

class Gui;
class Game;

#include <QtWidgets>

class Button: public QPushButton
{
    Q_OBJECT
public:
    Button(Game*, Gui*, int row, int column, const QString &text, QWidget *parent = 0);

    //! detects a left or right click
    void mouseReleaseEvent(QMouseEvent *e);

    //! detects double click
    void mouseDoubleClickEvent(QMouseEvent *e);

    void setMarked();
    void setUnExposed();
    void setExposed(const QString &text);

private:
    Game* _gamePointer;
    Gui* _guiPointer;
    int _row;
    int _column;

};

#endif // BUTTON_H
