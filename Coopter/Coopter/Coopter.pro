#-------------------------------------------------
#
# Project created by QtCreator 2014-02-02T13:32:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Coopter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    usbmanager.cpp \
    datamonitor.cpp \
    dataconverter.cpp \
    visualcontroller.cpp

HEADERS  += mainwindow.h \
    usbmanager.h \
    datamonitor.h \
    dataconverter.h \
    visualcontroller.h

FORMS    += mainwindow.ui \
    visualcontroller.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/ -llibusb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/ -llibusb
else:unix: LIBS += -L$$PWD/libs/ -llibusb

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs
