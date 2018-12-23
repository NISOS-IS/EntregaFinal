/**
    @file agenda.h
    @brief Archivo que contiene la clase Agenda con la que trabajará la clase Profesor.

    Aquí encontramos las cabeceras de los métodos de la clase Agenda, además de su variable privada.
*/
#ifndef AGENDA_H_
#define AGENDA_H_

#include <list>
#include <string>
#include "alumno.h"

using namespace std;

class Agenda{
    private:
        list<Alumno> listaAlumnos_;
    public:
        //constructor de la clase Agenda
        Agenda();

        //Busca uno o varios alumnos en el fichero binario
        list<Alumno> buscarAlumno(string dni, string apellidos, int equipo);

        //Inserta un alumno en el fichero binario
        bool insertarAlumno(Alumno alumno);

        //Borra un alumno del fichero binario
        bool borrarAlumno(string dni);

        //Modifica algunos de los datos de un alumno del fichero binario
        //bool modificarAlumno(string dni, string apellidos);
        bool modificarAlumno(Alumno alumno);

        //Muestra por pantalla el listado de alumnos del fichero binario
        list<Alumno> mostrarLista();

        //Muestra por pantalla los datos de un alumno en concreto
        list<Alumno> mostrarAlumno(string dni, string apellidos, int equipo);
};

#endif
