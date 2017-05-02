#-------------------------------------------------
#
# Project created by QtCreator 2017-04-26T09:07:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = FuzzyControl
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    fuzzy.cpp \
    qcustomplot.cpp \
    connection.cpp \
    signal.cpp \
    fuzzycontrol.cpp \
    functionwindow.cpp \
    rulewindow.cpp

HEADERS  += mainwindow.h \
    fuzzy.h \
    tanque.h \
    signal.h \
    connection.h \
    qcustomplot.h \
    quanser.h \
    fuzzycontrol.h \
    functionwindow.h \
    rulewindow.h

FORMS    += mainwindow.ui \
    connection.ui \
    functionwindow.ui \
    rulewindow.ui
