#-------------------------------------------------
#
# Project created by QtCreator 2013-04-05T19:22:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += _ALWAYS_CLEAN_LOGS

TARGET = libtester
TEMPLATE = app

DEPENDPATH += . ../lib1
DEPENDPATH += . ../lib2
INCLUDEPATH +=  ../lib1
INCLUDEPATH +=  ../lib2
LIBS+=  -L../lib1-buildqt/ -llib1
LIBS+=  -L../lib2-buildqt/ -llib2

SOURCES += main.cc

HEADERS  +=\
            easylogging++.h

FORMS    +=
