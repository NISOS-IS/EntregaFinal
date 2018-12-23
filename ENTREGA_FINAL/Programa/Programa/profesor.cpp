/**
    @file profesor.cpp
    @brief Archivo con los métodos de la clase Profesor implementados.
*/
#include <iostream>
#include <fstream>
#include "funcionesAux.h"
#include "profesor.h"

using namespace std;

/**
    @fn Profesor::Profesor():Persona()
    @brief Constructor de la clase Profesor

    Declara una variable de la clase Profesor vacío.

    @param No recibe ningún parámetro
    @return No devuelve nada

*/
Profesor::Profesor():Persona(){}


/**
    @fn bool Profesor::setContrasena(string contrasena)
    @brief Asigna la contraseña a un profesor si es correcta
    @param contrasena
    @return Devuelve un booleano, true si se asigna y false en caso contrario
*/
bool Profesor::setContrasena(string contrasena){
	bool correcto=false;
    if(contrasena.size()>=4){
        contrasena_ = contrasena;
        correcto= true;
    }
    else{
        correcto= false;
        cout<<"La contraseña debe tener 4 carácteres o más"<<endl;
    }
	return correcto;
}

/**
    @fn void Profesor::setUsuario(string usuario)
    @brief Asigna el usuario a un profesor
    @param usuario
    @return No devuelve nada
*/
void Profesor::setUsuario(string usuario){
    usuario_ = usuario;
}

/**
    @fn void Profesor::setRol(bool rol)
    @brief Asigna el rol a un profesor
    @param rol
    @return No devuelve nada
*/
void Profesor::setRol(bool rol){
    rol_ = rol;
}

/**
    @fn bool Profesor::buscarProfesor(string dni)
    @brief Busca a un profesor en el fichero binario donde están guardados los datos de cada uno de ellos
    @param dni
    @return Devuelve un booleano, true si se encuentra y false en caso contrario
*/
bool Profesor::buscaProfesor(string dni){
    bool correcto = false;
       ifstream file("profesores.bin", ios::in | ios::binary);
       Registro aux;
       bool encontrado = false;
       if(file.is_open()){
           while(!file.eof()){
               file.read(reinterpret_cast <char*>(&aux), sizeof(Registro));
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
    @fn bool Profesor::registrarProfesor(Profesor profesor)
    @brief Función que registra un profesor en el sistema guardando sus datos en el fichero binario
    @param profesor
    @return Devuelve un booleano, true si se guarda correctamente y false en caso contrario
*/
bool Profesor::registrarProfesor(Profesor profesor){
    ofstream file("profesores.bin", ios::out | ios::binary | ios::app);
    Registro reg;
	bool correcto=false;
    if(file.is_open()){
        strcpy(reg.dni,profesor.getDNI().c_str());
        strcpy(reg.nombre,profesor.getNombre().c_str());
        strcpy(reg.apellidos,profesor.getApellidos().c_str());
        reg.telefono=profesor.getTelefono();
        strcpy(reg.direccion,profesor.getDireccion().c_str());
        strcpy(reg.email,profesor.getEmail().c_str());
        strcpy(reg.fechaNacimiento,profesor.getFechaNacimiento().c_str());
        strcpy(reg.rol,convertirBool(profesor.getRol()).c_str());
        strcpy(reg.usuario,profesor.getUsuario().c_str());
        strcpy(reg.contrasena,profesor.getContrasena().c_str());
        file.write((char *) &reg, sizeof(Registro));
        file.close();
        correcto= true;
    }
    else{
        correcto= false;
    }
	return correcto;
}

/**
    @fn bool Profesor::login(Profesor reg)
    @brief Función que inicia la sesión de un profesor ya registrado
    @param reg
    @return Devuelve un booleano, true si los datos de inicio coinciden con los del fichero binario y false en caso contrario
*/
bool Profesor::login(Profesor reg){
    int j,cont=0;
    ifstream file("iniciosesion.bin", ios::in | ios::binary);
    bool correcto = false;
    RegUsu aux;
    string pass,user;
    
    if(file.is_open()){
        file.seekg(0,ios::end);
        j = file.tellg()/sizeof(RegUsu);
        file.seekg(0*sizeof(RegUsu));

        while((cont < j) && !correcto){
            file.read((char*) &aux, sizeof(RegUsu));

            user = aux.usuario;
            pass = aux.contrasena;

            if(user == reg.getUsuario()){
                if(pass == reg.getContrasena()){
                    cout<<"SESIÓN INICIADA"<<endl;
                    correcto = true;
                }
            }else{
                correcto=false;
            }
            cont++;
        }
        file.close();
    }
    return correcto;
}

/**
    @fn bool Profesor::cargarCopia()
    @brief Función que carga una copia de seguridad
    @param No recibe ningún parámetro
    @return Devuelve un booleano, true si se carga el fichero y false en caso contrario
*/
bool Profesor::cargarCopia(){
    int cont = 0, asig;
    ifstream in;
    ofstream out;
	bool correcto=false;
    RegistroAlumno alumno;

    in.open("copiaSeguridad.bin", ios::in | ios::binary);
    out.open("temporal.bin", ios::out | ios::binary);

    if(in.is_open() && out.is_open()){
        in.seekg(0, ios::end);
        asig = in.tellg() / sizeof(RegistroAlumno);
        in.seekg(0*sizeof(RegistroAlumno));

        in.read((char*)&alumno, sizeof(RegistroAlumno));
        do{
            out.write((char*)&alumno, sizeof(RegistroAlumno));
            in.read((char*)&alumno, sizeof(RegistroAlumno));
            cont++;
        }while(cont < asig);

        in.close();
        out.close();
        remove("alumnos.bin");
        rename("temporal.bin", "alumnos.bin");
        correcto= true;
    }
    else{
        cout<<"NO se pudo crear el fichero de copia"<<endl;
        correcto= false;
    }
	return correcto;
}

/**
    @fn bool Profesor::guardarCopia()
    @brief Función que guarda una copia de seguridad
    @param No recibe ningún parámetro
    @return Devuelve un booleano, true si guarda la copia de seguridad correctamente y false en caso contrario
*/
bool Profesor::guardarCopia(){
    int lon;
    ifstream fe;
    bool correcto = false;
    //Creamos otro archivo donde se copiara
    fe.open("alumnos.bin");
    ofstream fs("copiaSeguridad.bin");
    // Miramos cual es el tamaño del archivo
    if(fe.fail()){
        correcto = false;
    }else{
        fe.seekg (0, ios::end);
        lon = fe.tellg();
        fe.seekg (0, ios::beg);
        //Creamos una cadena de caracteres con el tamaño del archivo
        char* cadena = new char [lon];
        memset( cadena , 0 , lon );
        //Leemos el archivo y se guarda en la cadena
        fe.read(cadena,lon);
        if(fs.eof()){
            correcto = false;
        }
        else{
            fs.write(cadena,lon);
            correcto = true;
        }
    }

    fs.close();
    fe.close();

    return correcto;
}
