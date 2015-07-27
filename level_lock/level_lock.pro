TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    hierarchical_mutex.cpp
LIBS += -lpthread

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    hierarchical_mutex.h

