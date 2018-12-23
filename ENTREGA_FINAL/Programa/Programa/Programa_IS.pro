#-------------------------------------------------
#
# Project created by QtCreator 2018-12-11T12:08:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Programa_IS
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    iniciarsesion.cpp \
    registrarse.cpp \
    persona.cpp \
    alumno.cpp \
    profesor.cpp \
    agenda.cpp \
    funcionesAux.cpp \
    menu.cpp \
    insertar_modificar_alumno.cpp \
    modificar.cpp \
    profesoraux.cpp

HEADERS  += widget.h \
    iniciarsesion.h \
    registrarse.h \
    persona.h \
    alumno.h \
    profesor.h \
    agenda.h \
    funcionesAux.h \
    menu.h \
    insertar_modificar_alumno.h \
    modificar.h \
    profesoraux.h

FORMS    += widget.ui \
    iniciarsesion.ui \
    registrarse.ui \
    menu.ui \
    insertar_modificar_alumno.ui \
    modificar.ui
