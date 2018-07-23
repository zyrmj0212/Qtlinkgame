#-------------------------------------------------
#
# Project created by QtCreator 2016-07-11T10:49:28
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtLianliankan
TEMPLATE = app


SOURCES += main.cpp\
        main_game_window.cpp \
    game_model.cpp \
    menu.cpp \
    setmenu.cpp \
    game_model2.cpp

HEADERS  += main_game_window.h \
    menu.h \
    setmenu.h \
    game_model.h \
    game_model2.h

FORMS    += main_game_window.ui \
    menu.ui \
    setmenu.ui \
    game_model2.ui

RESOURCES += \
    res.qrc \
    pic/pic.qrc \
    back.qrc

DISTFILES += \
    ../LLK2.0.zip
