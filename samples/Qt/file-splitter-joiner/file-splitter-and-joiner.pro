#-------------------------------------------------
#
# Project created by QtCreator 2012-12-12T18:34:35
#
#-------------------------------------------------

QT       += core gui

TARGET = file-splitter-and-joiner
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    splitterwidget.cpp \
    joinerwidget.cpp \
    splitablefiledelegate.cpp \
    splittercore.cpp \
    partprocessor.cpp \
    addsplittedfiledialog.cpp \
    joinercore.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    easylogging++.h \
    splitterwidget.h \
    joinerwidget.h \
    splitablefiledelegate.h \
    splittercore.h \
    partprocessor.h \
    addsplittedfiledialog.h \
    joinercore.h \
    about.h

FORMS += \
    joinerwidget.ui \
    splitterwidget.ui \
    addsplittedfiledialog.ui \
    about.ui
