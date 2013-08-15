#-------------------------------------------------
#
# Project created by QtCreator 2013-03-19T22:31:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fast-dictionary
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x
DEFINES += _ELPP_STACKTRACE_ON_CRASH \

SOURCES += main.cc\
        mainwindow.cc \
    listwithsearch.cc

HEADERS  += mainwindow.hh \
    listwithsearch.hh \
    easylogging++.h

FORMS    += mainwindow.ui
