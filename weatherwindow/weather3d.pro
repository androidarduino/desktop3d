# -------------------------------------------------
# Project created by QtCreator 2009-08-18T20:39:20
# -------------------------------------------------
QT += opengl network xml
TARGET = weather3d
TEMPLATE = app
SOURCES += main.cpp \
    ../common/widget.cpp \
    weatherwindow.cpp \
    weatherinfo.cpp
HEADERS += ../common/widget.h \
    weatherwindow.h \
    weatherinfo.h
RESOURCES += res.qrc
INCLUDE += ../common
