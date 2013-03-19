#-------------------------------------------------
#
# Project created by QtCreator 2013-03-19T22:31:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fast-dictionary
TEMPLATE = app


SOURCES += main.cc\
        mainwindow.cc \
    listwithsearch.cc

HEADERS  += mainwindow.hh \
    easylogging++.h \
    listwithsearch.hh

FORMS    += mainwindow.ui
