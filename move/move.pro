TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    scoped_thread.cpp \
    func.cpp
LIBS += -lpthread

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    scoped_thread.h \
    func.h

