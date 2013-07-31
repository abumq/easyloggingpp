#-------------------------------------------------
#
# Project created by QtCreator 2013-04-05T19:18:52
#
#-------------------------------------------------

QT       -= core gui

TARGET = lib1
TEMPLATE = lib

DEFINES += LIB1_LIBRARY _DISABLE_MUTEX

SOURCES += lib1.cc

HEADERS += lib1.hh\
        lib1_global.hh\
        easylogging++.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
