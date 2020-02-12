#-------------------------------------------------
#
# Project created by QtCreator 2016-04-04T09:25:08
#
#-------------------------------------------------

QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ternary_Cubic
TEMPLATE = app

SOURCES += main.cpp \
    cube.cpp \
    window.cpp \
    game.cpp \
    Cell.cpp \
    Cube_.cpp \
    Plane.cpp \
    settings.cpp \
    map.cpp \
    finish.cpp

HEADERS  += \
    cube.h \
    window.h \
    game.h \
    Cell.h \
    Cube_.h \
    Plane.h \
    settings.h \
    map.h \
    finish.h

RESOURCES += \
    texture.qrc
