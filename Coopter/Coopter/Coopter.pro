#-------------------------------------------------
#
# Project created by QtCreator 2014-02-02T13:32:07
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Coopter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        usbmanager.cpp \
        datamonitor.cpp \
        dataconverter.cpp \
        visualcontroller.cpp \
        glwidget.cpp \
    motioncontroller.cpp

HEADERS  += mainwindow.h \
        usbmanager.h \
        datamonitor.h \
        dataconverter.h \
        visualcontroller.h \
        glwidget.h \
    motioncontroller.h

FORMS    += mainwindow.ui \
        visualcontroller.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/ -llibusb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/ -llibusb
#else:unix: LIBS += -L$$PWD/libs/linux/ -lusb
#else:unix: LIBS += -L/usr/local/lib64 -lusb
else:unix: LIBS += -L/usr/local/lib/ -lusb


INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

contains(QT_CONFIG, opengles.) {
    contains(QT_CONFIG, angle): \
        warning("Qt was built with ANGLE, which provides only OpenGL ES 2.0 on top of DirectX 9.0c")
    error("This example requires Qt to be configured with -opengl desktop")
}
