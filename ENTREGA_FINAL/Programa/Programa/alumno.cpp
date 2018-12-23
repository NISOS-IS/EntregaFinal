/**
    @file alumno.cpp
    @brief Archivo con los métodos de la clase Alumno implementados.
*/
#include <iostream>
#include <string>
#include "alumno.h"
#include "funcionesAux.h"

using namespace std;

/**
    @fn Alumno::Alumno():Persona()
    @brief Constructor de la clase Alumno

    Declara una variable de la clase Alumno vacío.

    @param No recibe ningún parámetro
    @return No devuelve nada

*/
Alumno::Alumno():Persona(){}

/**
    @fn bool setCurso(int curso)
    @brief Asigna el curso a un alumno si se ha introducido correctamente
    @param curso
    @return Devuelve un booleano, true si se asigna y false en caso contrario
*/
bool Alumno::setCurso(int curso){
    QWidget *parent= new QWidget;
	bool correcto=false;
    if(curso>0 && curso<5){
        curso_ = curso;
        correcto=true;
    }
    else{
        QMessageBox::critical(parent, "Title", "El numero de curso debe estar entre 1 y 4");
        correcto=false;
    }
	return correcto;
}

/**
    @fn bool setEquipo(int equipo)
    @brief Asigna el equipo a un alumno si se ha introducido correctamente
    @param equipo
    @return Devuelve un booleano, true si se asigna y false en caso contrario
*/
bool Alumno::setEquipo(int equipo){
    QWidget *parent= new QWidget;
	bool correcto=false;
    if(equipo > 0){
        equipo_ = equipo;
        correcto=true;
    }
    else{
        QMessageBox::critical(parent, "Title", "El numero de equipo debe ser positivo");
        correcto=false;
    }
	return correcto;
}

/**
    @fn void setLider(int lider)
    @brief Asigna el lider a un alumno
    @param lider
    @return No devuelve nada
*/
void Alumno::setLider(bool lider){
    lider_=lider;
}
