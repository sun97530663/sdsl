#-------------------------------------------------
#
# Project created by QtCreator 2016-07-21T09:47:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    modifytext.cpp \
    msplashscreen.cpp \
    mtreewidget.cpp \
    CrashModule/ccrashstack.cpp

HEADERS  += mainwindow.h \
    struct.h \
    modifytext.h \
    msplashscreen.h \
    mtreewidget.h \
    CrashModule/ccrashstack.h

FORMS    += mainwindow.ui \
    modifytext.ui \
    dialog.ui

RESOURCES += \
    rc.qrc
RC_FILE=icon.rc


#QMAKE_LFLAGS_RELEASE = /INCREMENTAL:NO /DEBUG

#QMAKE_CXXFLAGS_RELEASE += ./
#QMAKE_CFLAGS_RELEASE += ./
#QMAKE_LFLAGS_RELEASE = -mthreads -Wall

#QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
#QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

 #QMAKE_LFLAGS_RELEASE += /debug /opt:ref
#前两行意识意思为在release版本中增加debug信息；第三行意思为release版本中去掉-s参数，这样就生成对应符号表，可以调试跟踪；
