#-------------------------------------------------
#
# Project created by QtCreator 2013-04-16T23:28:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogViewer
TEMPLATE = app

DEFINES += _ELPP_QT_LOGGING \
         _ELPP_STL_LOGGING  \

SOURCES += main.cc\
        mainwindow.cc

HEADERS  += easylogging++.h \
        mainwindow.hh \


FORMS    += mainwindow.ui
