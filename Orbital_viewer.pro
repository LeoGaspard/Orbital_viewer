#-------------------------------------------------
#
# Project created by QtCreator 2021-04-03T09:56:39
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Orbital_viewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/C3Vec.cpp \
    src/grid.cpp \
    src/hydrogenoidorbital.cpp \
    src/marchingcube.cpp \
    src/sphericalharmonic.cpp \
    src/surface.cpp \
    src/openglwidget.cpp

HEADERS += \
    hdr/mainwindow.h \
    hdr/C3Vec.hpp \
    hdr/grid.hpp \
    hdr/hydrogenoidorbital.hpp \
    hdr/marchingcube.hpp \
    hdr/sphericalharmonic.hpp \
    hdr/surface.hpp \
    hdr/openglwidget.h \
    hdr/utils.hpp

FORMS += \
    uis/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    SyNet.qss
