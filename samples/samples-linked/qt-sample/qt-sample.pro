QT       += core
greaterThan(QT_MAJOR_VERSION, 4)

CONFIG += static

TARGET = main.cpp.bin
TEMPLATE = app

SOURCES += main.cpp \
           ../../../easylogging++.cc

HEADERS += mythread.h \
           ../../../easylogging++.h
