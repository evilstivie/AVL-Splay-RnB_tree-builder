#-------------------------------------------------
#
# Project created by QtCreator 2018-10-24T19:03:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tree
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    avl_tree.cpp \
    rb-tree.cpp \
    splay_tree.cpp

HEADERS  += mainwindow.h \
    backend.h

FORMS    += mainwindow.ui

DISTFILES += \
    tree_bg.jpeg

RESOURCES += \
    tree_bg.qrc \
    images.qrc
