TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    timer.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    timer.h

