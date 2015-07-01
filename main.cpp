#include "gui.h"
#include <QtWidgets>
#include <QtCore>
#include <ctime>

int main(int argc, char **argv){
    srand(time(0));
    QApplication app(argc, argv);
    Gui *g = new Gui;
    g->show();
    return app.exec();
}
