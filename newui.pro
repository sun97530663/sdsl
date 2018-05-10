#-------------------------------------------------
#
# Project created by QtCreator 2016-07-21T09:47:40
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    modifytext.cpp \
    msplashscreen.cpp \
    mtreewidget.cpp \
    QtXlsxWriter/xlsxsheetmodel.cpp \
    QtXlsxWriter/xlsxinterface.cpp \
    start.cpp \
    materialpriceset.cpp \
    reportoutput.cpp \
    about.cpp \
    DateBase/database.cpp

HEADERS  += mainwindow.h \
    struct.h \
    modifytext.h \
    msplashscreen.h \
    mtreewidget.h \
    QtXlsxWriter/xlsxsheetmodel.h \
    QtXlsxWriter/xlsxsheetmodel_p.h \
    QtXlsxWriter/xlsxinterface.h \
    start.h \
    materialpriceset.h \
    reportoutput.h \
    about.h \
    DateBase/database.h

FORMS    += mainwindow.ui \
    modifytext.ui \
    dialog.ui \
    start.ui \
    materialpriceset.ui \
    reportoutput.ui \
    about.ui

RESOURCES += \
    rc.qrc
RC_FILE=icon.rc

include(QtXlsxWriter/src/xlsx/qtxlsx.pri)
