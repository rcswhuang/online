#-------------------------------------------------
#
# Project created by huangw 2018-04-16T16:02:27
#
#-------------------------------------------------

QT       += core gui
QT += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = online
TEMPLATE = app

INCLUDEPATH += \
             ../include \
             ../include/H5IconGui \
             ../include/H5IconHelp \

SOURCES += main.cpp\
        honlinemainwindow.cpp \
    honlinetreewidget.cpp \
    honlinemgr.cpp \
    honlinescene.cpp \
    honlineview.cpp \
    honlinedoc.cpp

HEADERS  += honlinemainwindow.h \
    honlinetreewidget.h \
    honlinemgr.h \
    honlineview.h \
    honlinescene.h \
    honlinedoc.h

FORMS    += onlinemainwindow.ui

RESOURCES += \
    images.qrc

unix{

    LIBS += -L ../lib/ -lH5IconGui -lH5IconHelp -ldatafile
}

win32{
   LIBS += \
        ../lib/H5IconGui.lib \
        ../lib/H5IconHelp.lib \
        ../lib/datafile.lib
}
