#-------------------------------------------------
#
# Project created by QtCreator 2013-07-31T14:44:12
#
#-------------------------------------------------

QT       += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = el-remote-logger
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

# DEFINES += _ELPP_QT_LOGGING \
#     _ELPP_STL_LOGGING

SOURCES += main.cpp \
    request_handler.cpp \
    request_thread.cpp \
    request.cpp

HEADERS  += \
    easylogging++.h \
    request_handler.h \
    request_thread.h \
    getopt.h \
    request.h

FORMS    +=

OTHER_FILES += \
    el-remote-logger-internal-logger.conf
