QT       += core
greaterThan(QT_MAJOR_VERSION, 4)

CONFIG += static
DEFINES += _ALWAYS_CLEAN_LOGS \
          _ELPP_QT_LOGGING    \
          _ELPP_STL_LOGGING   \
          _ELPP_GNUC_LOGGING

TARGET = main.cpp.bin
TEMPLATE = app

SOURCES += main.cpp
HEADERS += easylogging++.h \
           mythread.h

OTHER_FILES += \
    test_conf.conf
