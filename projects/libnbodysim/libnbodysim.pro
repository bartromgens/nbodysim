TEMPLATE = lib
#CONFIG += staticlib
CONFIG -= qt
TARGET = nbodysim
DESTDIR = ../../lib

INCLUDEPATH += ../../src/
DEPENDPATH += $$INCLUDEPATH
VPATH += $$INCLUDEPATH

SOURCES += \
  body.cpp \
  environment.cpp \
  integrator.cpp

HEADERS += \
  body.h \
  environment.h \
  integrator.h

UI_DIR += ./generated
MOC_DIR += ./generated

# use c++11
QMAKE_CXXFLAGS += -std=c++11 -pthread

# for std::thread
QMAKE_CXXFLAGS += -pthread

# warnings
QMAKE_CXXFLAGS += -Wall

# clean compile output
CONFIG += silent

