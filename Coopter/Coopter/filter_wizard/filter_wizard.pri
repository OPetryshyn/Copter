INCLUDEPATH += $$PWD

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

HEADERS += $$PWD/pagefiltertype.h \
    $$PWD/pagefilterparameters.h \
    $$PWD/wizard.h \
    filter_wizard/FilterTypes.h

SOURCES += $$PWD/pagefiltertype.cpp \
    $$PWD/pagefilterparameters.cpp \
    $$PWD/wizard.cpp

FORMS += $$PWD/pagefiltertype.ui \
    $$PWD/pagefilterparameters.ui \
    $$PWD/wizard.ui
