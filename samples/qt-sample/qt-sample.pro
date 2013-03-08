QT       += core
greaterThan(QT_MAJOR_VERSION, 4)

CONFIG += static
DEFINES += _ALWAYS_CLEAN_LOGS
TARGET = main.cpp.bin
TEMPLATE = app

SOURCES += main.cpp
HEADERS += mythread.h \
    ../../easylogging++.h
