/**
    @file persona.cpp
    @brief Archivo con los métodos de la clase Persona implementados.
*/
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include "persona.h"
#include "funcionesAux.h"

/**
    @fn Persona::Persona()
    @brief Constructor de la clase Persona

    Declara una variable de la clase Persona vacío.

    @param No recibe ningún parámetro
    @return No devuelve nada

*/
Persona::Persona(){}


/**
    @fn bool Persona::setDNI(string dni)
    @brief Asigna el dni a un alumno si es correcto
    @param dni
    @return Devuelve un booleano, true si se asigna y false en caso contrario
*/
bool Persona::setDNI(string dni){
    QWidget *parent= new QWidget;
	bool correcto=false;
    char cadDni[9];

    strcpy(cadDni, dni.c_str());

    dni[8] = toupper(dni[8]);
    if(strlen(cadDni) != 9){
        QMessageBox::critical(parent, "Title", "El DNI introducido no es correcto");
        correcto= false;
    }
    else{
        char letra[] = "TRWAGMYFPDXBNJZSQVHLCKE";
        if(letra[atoi(cadDni)%23] == dni[8]){
            dni_=dni;
            correcto =true;
        }else{
            QMessageBox::critical(parent, "Title", "El DNI introducido no es correcto");
            correcto =false;
        }
    }
	return correcto;
}

/**
    @fn void Persona::setNombre(string nombre)
    @brief Asigna el nombre a un alumno
    @param nombre
    @return No devuelve nada
*/
void Persona::setNombre(string nombre){
    nombre_ = nombre;
}

/**
    @fn void Persona::setApellidos(string apellidos)
    @brief Asigna los apellidos a un alumno
    @param apellidos
    @return No devuelve nada
*/
void Persona::setApellidos(string apellidos){
    apellidos_ = apellidos;
}

/**
    @fn bool Persona::setTelefono(int telefono)
    @brief Asigna el telefono a un alumno si es correcto
    @param telefono
    @return Devuelve un booleano, true si se asigna y false en caso contrario
*/
bool Persona::setTelefono(int telefono){
    QWidget *parent= new QWidget;
	bool correcto= false;
    string s = to_string(telefono);
    if(s.size()==9){

        telefono_ = atoi(s.c_str());
         correcto= true;
    }
    else{
        QMessageBox::critical(parent, "Title", "El Telefono introducido no es correcto");
        correcto= false;
    }
	return correcto;
}

/**
    @fn void Persona::setDireccion(string direccion)
    @brief Asigna la direccion a un alumno
    @param direccion
    @return No devuelve nada
*/
void Persona::setDireccion(string direccion){
    direccion_ = direccion;
}

/**
    @fn bool Persona::setEmail(string email)
    @brief Asigna el email a un alumno si es correcto
    @param email
    @return Devuelve un booleano, true si se asigna y false en caso contrario
*/
bool Persona::setEmail(string email){
    QWidget *parent= new QWidget;
    bool correcto = true, bandera=false;

    size_t at = email.find('@'); //Busca dentro de la cadena un "@"
    if(at == string::npos){
        correcto = false;
    }

    size_t dot = email.find('.', at+1); //Busca dentro de la cadena un "."
    if(dot == string::npos){
        correcto = false;
    }

    if(correcto==true){
        email_ = email;
        bandera= true;
    }
    else{
         QMessageBox::critical(parent, "Title", "El Email introducido no es correcto");
        bandera= false;
    }
	return bandera;
}

/**
    @fn bool Persona::setFechaNacimiento(string fecha_nacimiento)
    @brief Asigna la fecha de nacimiento a un alumno si es correcta
    @param fecha_nacimiento
    @return Devuelve un booleano, true si se asigna y false en caso contrario
*/
bool Persona::setFechaNacimiento(string fecha_nacimiento){
    bool correcto=true;
    QWidget *parent= new QWidget;
    char linea[10];
    strcpy(linea, fecha_nacimiento.c_str());
    unsigned d, m, a;
    bool correctoM = false, correctoD = false, bandera=false;

    strcpy(linea, fecha_nacimiento.c_str());
    if(linea == NULL){
        return EXIT_FAILURE;
    }
    //Comprueba que el formato de la fecha sea correcto, es decir, dd/mm/aaaa
    if(sscanf(linea, "%2u/%2u/%4u", &d, &m, &a) == 3){
        //Comprueba que el dia no sea menor de 1 ni mayor de 31
        if(d >= 1 && d <= 31){
            correctoD = true;
        }
        else{
            correctoD = false;
        }

        //Comprueba que el mes no sea menor de 1 ni mayor de 12
        if(m >= 1 && m <= 12){
            correctoM = true;
        }
        else{
            correctoM = false;
        }
    }
    else{
        correcto = false;
    }

    if(correcto && correctoD && correctoM){
        correcto = true;
    }
    else{
        correcto = false;
    }

    if(correcto==true){
        fechaNacimiento_ = fecha_nacimiento;
        bandera= true;
    }
    else{
         QMessageBox::critical(parent, "Title", "La Fecha introducida no es correcta. Debe usar el formato dd/MM/aaaa");
        bandera= false;
    }
	return bandera;
}
