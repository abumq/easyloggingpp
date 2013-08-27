QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-gtest-proj-intel
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

QMAKE_CC = icpc
QMAKE_CXX = icpc
QMAKE_LINK = icpc

DEFINES += _ELPP_STOP_ON_FIRST_ASSERTION

LIBS += -lgtest

SOURCES += main.cc

HEADERS  += \
    configurations-test.h \
    enum-helper-tests.h \
    hit-counter-test.h \
    loggers-test.h \
    registry-test.h \
    test-helpers.h \
    typed-configurations-test.h \
    utilities-test.h \
    vmodule-tests.h \
    write-all-test.h \
    easylogging++.h \
    global-configurations-test.h \
    loggable-test.h
