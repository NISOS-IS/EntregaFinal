/**
    @file funcionesAux.h
    @brief Archivo que contiene las funciones auxiliares.

    Todas las funciones auxiliares aquí definidas se utilizarán a lo largo del resto del código.
    También se declaran aquí tres struct auxiliares para la hora de escribir o leer de un fichero binario.
*/
#ifndef FUNCIONESAUX_H_
#define FUNCIONESAUX_H_

#include <fstream>
#include <string>
#include <iostream>
#include "agenda.h"
#include <QMessageBox>

using namespace std;

/**
    @struct Registro
    @brief Estructura que con variables de tipo char e int que nos servirá para poder trabajar con los ficheros binarios
*/
struct Registro{
    char dni[10]; ///<Variable para el DNI
    char nombre[100]; ///<Variable para el Nombre
    char apellidos[100]; ///<Variable para los Apellidos
    int telefono; ///<Variable para el Telefono
    char direccion[100]; ///<Variable para la Direccion
    char email[100]; ///<Variable para el Email
    char fechaNacimiento[100]; ///<Variable para la Fecha de Nacimiento
    char rol[20]; ///<Variable para el Rol
    char usuario[100]; ///<Variable para el Nombre de Usuario
    char contrasena[100]; ///<Variable para la Contraseña
};

/**
    @struct RegistroAlumno
    @brief Estructura que con variables de tipo char e int que nos servirá para poder trabajar con los ficheros binarios
*/
struct RegistroAlumno{
    char dni[10]; ///<Variable para el DNI
    char nombre[100]; ///<Variable para el Nombre
    char apellidos[100]; ///<Variable para los Apellidos
    int telefono; ///<Variable para el Telefono
    char direccion[100]; ///<Variable para la Direccion
    char email[100]; ///<Variable para el Email
    char fechaNacimiento[100]; ///<Variable para la Fecha de Nacimiento
    int curso; ///<Variable para el Curso
    int equipo; ///<Variable para el Número del Equipo
    char lider[100]; ///<Variable para saber si es Lider o no
};

/**
    @struct RegUsu
    @brief Estructura que con variables de tipo char e int que nos servirá para poder trabajar con los ficheros binarios
*/
struct RegUsu{
    char usuario[100]; ///<Variable para el Nombre de Usuario
    char contrasena[100]; ///<Variable para la Contraseña
    char rol[15]; ///<Variable para el Rol
};

bool comprobarExistenciaDNI(string dni);
bool comprobarLider(list<Alumno> &aux, bool lider);
bool compruebaEmailProfesor(string email);
bool compruebaUsuario(string usuario);
bool comprobarEmail(list<Alumno> &aux, string email);
string convertirBool(bool a);
string convertirBoolLider(bool a);
bool convertirStringLider(char *lider);
string mayusculas(string cadena);
bool escribirDatos(string dni, string nombre, string apellidos, int telefono, string direccion, string email, string fechaNacimiento, int curso, int equipo, bool lider);
int cuentaRegistros();
bool modificarDatos(string dni, string nombre, string apellidos, int telefono, string direccion, string email, string fechaNacimiento, int curso, int equipo, bool lider);
int leerlinea(char *cad, int max);
void mostrarListado();
bool ActualizarFicheroInicio(RegUsu reg);
bool comprobarUsuario(RegUsu reg);

#endif
