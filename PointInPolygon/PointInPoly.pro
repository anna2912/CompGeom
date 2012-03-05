TEMPLATE = app
TARGET = PointInPoly

CONFIG += QtGui
QT += opengl

OBJECTS_DIR = bin

QMAKE_CXXFLAGS = -std=c++0x -Wall

CONFIG += precompile_header
PRECOMPILED_HEADER = src/stdafx.h

DEPENDPATH += src \
              visualization/headers \
              visualization/headers/common \
              visualization/headers/io \
              visualization/headers/visualization \

INCLUDEPATH += src \
               visualization/headers \
               geom \

HEADERS += src/stdafx.h \
           src/viewer.h \
    geom/PointInPolygon.h

SOURCES += src/main.cpp \
    geom/PointInPolygon.cpp

LIBS += -Lvisualization -lvisualization
