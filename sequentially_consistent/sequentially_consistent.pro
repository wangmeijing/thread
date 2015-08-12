TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
LIBS += -lpthread

include(deployment.pri)
qtcAddDeployment()

