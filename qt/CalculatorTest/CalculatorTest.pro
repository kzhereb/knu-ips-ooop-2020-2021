QT += testlib
QT += gui widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_testmainwindow.cpp \
    ../Calculator/mainwindow.cpp

FORMS += \
    ../Calculator/mainwindow.ui

HEADERS += \
    ../Calculator/mainwindow.h

