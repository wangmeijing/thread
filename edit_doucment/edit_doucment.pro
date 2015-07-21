TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    user_command.cpp
LIBS += -lpthread

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    user_command.h

