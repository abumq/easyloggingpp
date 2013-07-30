
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = building-blocks
TEMPLATE = app

DEFINES += _ALWAYS_CLEAN_LOGS BUILDING_BLOCKS_DEVELOPMENT_STAGE \
 _ELPP_QT_LOGGING _ELPP_STL_LOGGING


SOURCES += \
    game/gameplay.cc \
    game/main.cc \
    engine/engine.cc \
    engine/internal/point.cc \
    engine/internal/line.cc \
    engine/internal/board.cc \
    game/gameboard.cc \
    engine/internal/player.cc \
    engine/internal/block.cc

HEADERS  += \
    game/gameplay.hh \
    engine/easylogging++.h \
    engine/engine.hh \
    engine/internal/point.hh \
    engine/internal/line.hh \
    engine/internal/board.hh \
    game/gameboard.hh \
    engine/internal/player.hh \
    engine/internal/block.hh

FORMS    +=

OTHER_FILES += \
    todo-list.txt
