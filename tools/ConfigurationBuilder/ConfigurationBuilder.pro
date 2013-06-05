#-------------------------------------------------
#
# Project created by QtCreator 2013-05-28T11:28:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConfigurationBuilder
TEMPLATE = app

DEFINES += _ELPP_QT_LOGGING

SOURCES += main.cpp\
        maindialog.cpp \
    fileselector.cpp \
    configurationchooser.cpp \
    formatbuilderdialog.cc

HEADERS  += maindialog.h \
    fileselector.h \
    configurationchooser.h \
    easylogging++.h \
    formatbuilderdialog.hh

FORMS    += maindialog.ui \
    fileselector.ui \
    configurationchooser.ui \
    formatbuilderdialog.ui
