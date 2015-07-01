SOURCES += \
    Game.cpp \
    Grid.cpp \
    MineGrid.cpp \
    Player.cpp \
    Position.cpp \
    main.cpp \
    gui.cpp \
    button.cpp \
    #settingsdialog.cpp

HEADERS += \
    Game.h \
    Grid.h \
    MineGrid.h \
    Player.h \
    Position.h \
    gui.h \
    button.h \
    #settingsdialog.h

QMAKE_CXXFLAGS += --std=c++11

QT += core gui widgets
