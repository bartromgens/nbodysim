QT       += core gui

TARGET = tests
TEMPLATE = app

LIBS += -L../../lib
LIBS += -lnbodysim

#include general example project settings
INCLUDEPATH += ../../src/
DEPENDPATH += $$INCLUDEPATH
VPATH += $$INCLUDEPATH

SOURCES += \
  main.cpp \

HEADERS  += \

CONFIG += silent

# compiler settings
QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -Wall

