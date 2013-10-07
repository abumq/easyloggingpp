QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-gtest-proj
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

COMPILER = g++
QMAKE_CC = $$COMPILER
QMAKE_CXX = $$COMPILER
QMAKE_LINK = $$COMPILER

DEFINES += _ELPP_STOP_ON_FIRST_ASSERTION \
           _ELPP_STL_LOGGING \
           _ELPP_FORCE_ENV_VAR_FROM_BASH \
           _ELPP_ENABLE_THREADING \
           _ELPP_DISABLE_VMODULES_EXTENSION \
           _ELPP_STACKTRACE_ON_CRASH \
           _ELPP_STRICT_SIZE_CHECK \
           _ELPP_SYSLOG

LIBS += -lgtest

SOURCES += main.cc

HEADERS  += \
    configurations-test.h \
    enum-helper-test.h \
    hit-counter-test.h \
    registry-test.h \
    test.h \
    typed-configurations-test.h \
    utilities-test.h \
    helpers-test.h \
    write-all-test.h \
    easylogging++.h \
    global-configurations-test.h \
    loggable-test.h \
    logger-test.h \
    verbose-app-arguments-test.h \
    custom-format-specifier-test.h \
    syslog-test.h
