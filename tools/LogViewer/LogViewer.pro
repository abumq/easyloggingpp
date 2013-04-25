#-------------------------------------------------
#
# Project created by QtCreator 2013-04-25T16:36:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogViewer
TEMPLATE = app

DEINFES += _ELPP_STL_LOGGING \
           _ELPP_QT_LOGGING  \
           _ELPP_STRICT_ROLLOUT

SOURCES += main.cc\
        mainwindow.cc

HEADERS  += mainwindow.hh \
    easylogging++.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    log.conf
