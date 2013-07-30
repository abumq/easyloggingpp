#-------------------------------------------------
#
# Project created by QtCreator 2013-04-05T19:21:20
#
#-------------------------------------------------

QT       -= core gui

TARGET = lib2
TEMPLATE = lib

DEFINES += LIB2_LIBRARY

SOURCES += lib2.cc

HEADERS += lib2.hh\
        lib2_global.hh\
        easylogging++.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
