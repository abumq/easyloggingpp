QT       += core
greaterThan(QT_MAJOR_VERSION, 4)

CONFIG += static
DEFINES += _ELPP_QT_LOGGING    \
          _ELPP_STL_LOGGING   \
          _ELPP_STRICT_SIZE_CHECK

TARGET = main.cpp.bin
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11
SOURCES += main.cpp
HEADERS += \
           mythread.h \
    easylogging++.h

OTHER_FILES += \
    test_conf.conf
