/**
    @file funcionesAux.cpp
    @brief Archivo con las funciones auxiliares implementadas.
*/
#include <iostream>
#include<limits>
#include <stdio.h>
#include <string>
#include <ctype.h>
#include "funcionesAux.h"
#include "agenda.h"

using namespace std;

/**
    @fn bool comprobarExistenciaDNI(string dni)
    @brief Comprueba si el DNI introducido esta ya registrado
    @param dni
    @return Devuelve un booleano, true si se encuentra y false en caso contrario
*/
bool comprobarExistenciaDNI(string dni){
    bool correcto = false;
    ifstream file("alumnos.bin", ios::in | ios::binary);
    RegistroAlumno aux;
    bool encontrado = false;
    if(file.is_open()){
        while(!file.eof()){
            file.read(reinterpret_cast <char*>(&aux), sizeof(RegistroAlumno));
            if(aux.dni == dni){
                encontrado = true;
            }
        }
        if(encontrado){
            correcto = true;
        }
        else{
            correcto = false;
        }
    }
    return correcto;
}


/**
    @fn bool comprobarLider(list<Alumno> &aux, bool lider)
    @brief Comprueba si el lider de un equipo esta ya asignado
    @param aux
    @param lider
    @return Devuelve un booleano, true si se encuentra ya asignado y false en caso contrario
*/
bool comprobarLider(list<Alumno> &aux, bool lider){
    list<Alumno>::iterator i;
    bool encontrado = false;
    for(i = aux.begin(); i != aux.end(); i++){
        if(i->getLider() == lider){
            encontrado = true;
        }
    }
    if(encontrado){
        return true;
    }
    else{
        return false;
    }
}

/**
    @fn bool comrpuebaEmailProfesor(string email)
    @brief Comprueba si el email introducido está ya registrado
    @param email
    @return Devuelve un booleano, true si se encuentra asignado y false en caso contrario
*/
bool compruebaEmailProfesor(string email){
    bool correcto = false;
       ifstream file("profesores.bin", ios::in | ios::binary);
       Registro aux;
       bool encontrado = false;
       if(file.is_open()){
           while(!file.eof()){
               file.read(reinterpret_cast <char*>(&aux), sizeof(Registro));
               if(aux.email == email){
                   encontrado = true;
               }
           }
           if(encontrado==true){
               correcto = true;
           }
           else{
               correcto = false;
           }
       }
       return correcto;
}

/**
    @fn bool compruebaUsuario(string usuario)
    @brief Comprueba si un usuario ya está registrado
    @param usuario
    @return Devuelve un booleano, true si se encuentra y false en caso contrario
*/
bool compruebaUsuario(string usuario){
    bool correcto = false;
       ifstream file("profesores.bin", ios::in | ios::binary);
       Registro aux;
       bool encontrado = false;
       if(file.is_open()){
           while(!file.eof()){
               file.read(reinterpret_cast <char*>(&aux), sizeof(Registro));
               if(aux.usuario == usuario){
                   encontrado = true;
               }
           }
           if(encontrado==true){
               correcto = true;
           }
           else{
               correcto = false;
           }
       }
       return correcto;
}

/**
    @fn bool comrpuebaEmailProfesor(string email)
    @brief Comprueba si el email introducido está ya registrado
    @param email
    @return Devuelve un booleano, true si se encuentra asignado y false en caso contrario
*/
bool comprobarEmail(list<Alumno> &aux, string email){
    list<Alumno>::iterator i;
    bool encontrado = false;

    for(i = aux.begin() ; i != aux.end() ; i++){
        if(i->getEmail() == email){
            encontrado = true;
        }
    }
    if(encontrado){
        return true;
    }
    else{
        return false;
    }
}


/**
    @fn string convertirBool(bool a)
    @brief Convierte el rol del profesor a string
    @param a
    @return Devuelve un string con la cadena que le corresponda
*/
string convertirBool(bool a){
    string aux;
    if(a){
        aux = "Coordinador";
    }
    else{
        aux = "Ayudante";
    }
    return aux;
}

/**
    @fn string convertirBoolLider(bool a)
    @brief Convierte el rol del alumno a string
    @param a
    @return Devuelve un string con la cadena que le corresponda
*/
string convertirBoolLider(bool a){
    string aux;
    if(a==true){
        aux = "Lider";
    }
    else{
        aux = "No lider";
    }
    return aux;
}

/**
    @fn bool convertirStringLider(char *a)
    @brief Convierte a booleano el string recibido
    @param *a
    @return Devuelve un booleano con el valor correspondiente
*/
bool convertirStringLider(char *a){
    bool aux=false;
    string cadena;
    cadena= a;

    if(cadena=="Lider"){
        aux=true;
    }else{
        aux=false;
    }
    return aux;
}


/**
    @fn int leerlinea(char *cad, int max)
    @brief Lee todos los caracteres de una linea
    @param *cad
    @param max
    @return Devuelve un entero con el número de caracteres leidos
*/
int leerlinea(char *cad, int max){
    int i=0, c;
    while((i<max-1) && (c = getchar()) != '\n'){
        cad[i] = '\0';
        i++;
    }
    cad[i] = '\0';
    return i;
}

/**
    @fn string mayusculas(string cadena)
    @brief Convierte a mayusculas todas las letras de la cadena pasada
    @param cadena
    @return Devuelve un string con las letras convertidas
*/
string mayusculas(string cadena){
	int longitud= cadena.length();
    for(int i=0; i<longitud; i++){
        cadena[i] = toupper(cadena[i]);
    }
    return cadena;
}


/**
    @fn bool escribirDatos(string dni, string nombre, string apellidos, int telefono, string direccion, string email, string fecha_nacimiento, int curso, int equipo, bool lider)
    @brief Hace las comprobaciones necesarias de los datos y llama a la función insertarAlumno para introducirlo en el fichero
    @param dni
    @param nombre
    @param apellidos
    @param telefono
    @param direccion
    @param email
    @param fecha_nacimiento
    @param curso
    @param equipo
    @param lider
    @return Devuelve un booleano, true si no ha habido problemas al guardarlo y false en caso contrario
*/
bool escribirDatos(string dni, string nombre, string apellidos, int telefono, string direccion, string email, string fecha_nacimiento, int curso, int equipo, bool lider){
    Alumno alumno;
    Agenda agenda;
    list<Alumno> aux;
    char auxDNI[9];
    QWidget *parent= new QWidget;
    bool funcionCorrecta=false, devuelve=false, encontrado=false, guardar=true;;

    strcpy(auxDNI, dni.c_str());
    auxDNI[8]= toupper(auxDNI[8]);
    dni= auxDNI;
    encontrado= comprobarExistenciaDNI(dni);
    if(encontrado==false){
        if((alumno.setDNI(dni))==false){
            guardar=false;
        }
    }else{
        QMessageBox::critical(parent, "Title", "DNI existente. Introduzca uno distinto");
        guardar=false;
    }

    nombre= mayusculas(nombre);
    alumno.setNombre(nombre);

    apellidos= mayusculas(apellidos);
    alumno.setApellidos(apellidos);

   // variableCorrecta=alumno.setTelefono(telefono);
    if(alumno.setTelefono(telefono)==false){
        guardar=false;
    }

    direccion= mayusculas(direccion);
    alumno.setDireccion(direccion);

    aux= agenda.mostrarLista();
    if(aux.empty()){
        if((alumno.setEmail(email))==false){
            guardar=false;
        }
    }else{
        encontrado= comprobarEmail(aux, email);
        if(encontrado==false){
            if((alumno.setEmail(email))==false){
                guardar=false;
            }
        }else{
            guardar=false;
            QMessageBox::critical(parent, "Title", "Ese email ya esta registrado. Introduzca uno distinto");
        }
    }

    if((alumno.setFechaNacimiento(fecha_nacimiento))==false){
        guardar=false;
    }

    if((alumno.setCurso(curso))==false){
        guardar=false;
    }

    if((alumno.setEquipo(equipo))==false){
        guardar=false;
    }

    if(lider==true){
        aux=agenda.buscarAlumno("","",equipo);
        encontrado= comprobarLider(aux, lider);
        if(encontrado==false){
            lider=true;
        }else{
            lider=false;
        }
    }
    alumno.setLider(lider);

    if(guardar==true){
        funcionCorrecta= agenda.insertarAlumno(alumno);
            if(funcionCorrecta==true){
                devuelve= true;
            }else{
                devuelve= false;
            }
    }
    aux.clear();
    return devuelve;
}

/**
    @fn bool escribirDatos(string dni, string nombre, string apellidos, int telefono, string direccion, string email, string fecha_nacimiento, int curso, int equipo, bool lider)
    @brief Hace las comprobaciones necesarias de los datos y llama a la función insertarAlumno para introducirlo en el fichero
    @param dni
    @param nombre
    @param apellidos
    @param telefono
    @param direccion
    @param email
    @param fecha_nacimiento
    @param curso
    @param equipo
    @param lider
    @return Devuelve un booleano, true si no ha habido problemas al guardarlo y false en caso contrario
*/
bool modificarDatos(string dni, string nombre, string apellidos, int telefono, string direccion, string email, string fechaNacimiento, int curso, int equipo, bool lider){
    Alumno alumno;
    Agenda agenda;
    list<Alumno> aux;
    bool devuelve=false, funcionCorrecta=false, guardar=true, variableCorrecta=false, encontrado;

    alumno.setDNI(dni);
    nombre= mayusculas(nombre);
    alumno.setNombre(nombre);

    apellidos= mayusculas(apellidos);
    alumno.setApellidos(apellidos);

    variableCorrecta=alumno.setTelefono(telefono);
    if(variableCorrecta==false){
        guardar=false;
    }

    direccion= mayusculas(direccion);
    alumno.setDireccion(direccion);

    alumno.setEmail(email);

    if((variableCorrecta= alumno.setFechaNacimiento(fechaNacimiento))==false){
        guardar=false;
    }

    if((variableCorrecta=alumno.setCurso(curso))==false){
        guardar=false;
    }

    if((variableCorrecta=alumno.setEquipo(equipo))==false){
        guardar=false;
    }

    if(lider==true){
        aux=agenda.buscarAlumno("","",equipo);
        encontrado= comprobarLider(aux, lider);
        if(encontrado==false){
            lider=true;
        }else{
            lider=false;
        }
    }
    alumno.setLider(lider);

    if(guardar==true){
        funcionCorrecta= agenda.modificarAlumno(alumno);
            if(funcionCorrecta==true){
                devuelve= true;
            }else{
                devuelve= false;
            }
    }
    aux.clear();
    return devuelve;
}

/**
    @fn int cuentaRegistros()
    @brief Cuenta el número de registros de un fichero
    @param No recibe ningún parámetro
    @return Devuelve un entero con el número de registros
*/
int cuentaRegistros(){
    int numeroRegistros=0;
    ifstream registros("alumnos.bin", ios::in | ios::binary);

    registros.seekg(0,ios::end);
    numeroRegistros = registros.tellg()/sizeof(RegistroAlumno);

    return numeroRegistros;
}

/**
    @fn void mostrarListado()
    @brief Muestra todos los alumnos de la lista de alumnos de Agenda
    @param No recibe ningún parámetro
    @return No devuelve nada
*/
void mostrarListado(){
    Agenda agenda;
    list<Alumno> aux = agenda.mostrarLista();
    aux.clear();
}

/**
    @fn bool ActualizarFicheroInicio(RegUsu reg)
    @brief Actualiza el fichero de usuarios con los nuevos usuarios insertados
    @param reg
    @return Devuelve un booleano, true si se actualiza el fichero y false en caso contrario
*/
bool ActualizarFicheroInicio(RegUsu reg){
    ofstream file("iniciosesion.bin", ios::out | ios::binary | ios::app);

    if(file.is_open()){
        file.write((char*)&reg, sizeof(RegUsu));
        file.close();
        return true;
    }
    else{
        return false;
    }
}
