# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = XPlay2
DESTDIR = ../../bin/win32
QT += core opengl gui multimedia widgets openglextensions
INCLUDEPATH += $$PWD/../../include
CONFIG += debug console
LIBS += -L"./../../lib/win32" \
    -lopengl32 \
    -lglu32
DEPENDPATH += .

OBJECTS_DIR += debug


include(XPlay2.pri)