#include "button.h"
#include "Game.h"
Button::Button(Game* gamePointer, Gui* guiPointer,
   int row, int column, const QString &text, QWidget *parent)
        : QPushButton(text, parent), _gamePointer(gamePointer),
          _guiPointer(guiPointer), _row(row), _column(column)
{
    this->setFixedSize(20,20);
}

void Button::setMarked(){
    this->setText("F");
}

void Button::setUnExposed(){
    this->setText("");
}

void Button::setExposed(const QString &text){
    this->setText(text);
    this->setFlat(true);
    this->clearFocus();
}

void Button::mouseReleaseEvent(QMouseEvent *e){
    if(e->button() == Qt::RightButton){
        _gamePointer->mark(_guiPointer,_row, _column);
    }

    if(e->button() == Qt::LeftButton){
        _gamePointer->click(_guiPointer, _row, _column);
    }
    //TODO:
    //double click should expose all surounding fields
    //that are not already exposed
}

void Button::mouseDoubleClickEvent(QMouseEvent *e){
    _gamePointer->exposeSurroundingAndUnexposed(_guiPointer, _row, _column);
}
