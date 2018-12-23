/**
    @file agenda.cpp
    @brief Archivo con los métodos de la clase Agenda implementados.
*/
#include <iostream>
#include <fstream>
#include <string>
#include "agenda.h"
#include "funcionesAux.h"
#include <QMessageBox>

/**
    @fn Agenda::Agenda()
    @brief Constructor de la clase Agenda

    Declara una variable de la clase Agenda vacío.

    @param No recibe ningún parámetro
    @return No devuelve nada

*/
Agenda::Agenda(){}

/**
    @fn list<Alumno> Agenda::buscarAlumno(string dni, string apel, int equipo)
    @brief Función que busca a un alumno en la Agenda
    @param dni
    @param apel
    @param equipo
    @return Devuelve una lista de Alumnos encontrados
*/
list<Alumno> Agenda::buscarAlumno(string dni, string apel, int equipo){
    int j,cont=0;
        ifstream file("alumnos.bin", ios::in | ios::binary);
        Alumno aux;
        RegistroAlumno alumnoAux;
        bool encontrado = false;
        string dni1, nombre, apellido, direccion, email, fechaNacimiento;
        if(file.is_open()){
            file.seekg(0,ios::end);
            j = file.tellg()/sizeof(RegistroAlumno);
            file.seekg(0*sizeof(RegistroAlumno));

            file.read(reinterpret_cast <char *> (&alumnoAux), sizeof(RegistroAlumno));
            while(cont < j){
                //si apel es una cadena vacia y equipo 0, realiza la busqueda por dni
                if(apel=="" && equipo==0){
                    if(alumnoAux.dni == dni){
                        encontrado = true;
                    }
                //si dni es cadena vacia y equipo 0, realiza la busqueda por apellido
                }else if(dni=="" && equipo==0){
                    //compruebe si apellido contiene apel
                    apellido = alumnoAux.apellidos;
                    if(apellido.find(apel) != string::npos){
                        encontrado=true;
                    }
                //si dni y apel son cadena vacia, realiza la busqueda por equipo
                }else if(dni=="" && apel==""){
                    if(alumnoAux.equipo==equipo){
                        encontrado=true;
                    }
                }
                if(encontrado){
                        dni1=alumnoAux.dni;
                        aux.setDNI(dni1);
                        nombre=alumnoAux.nombre;
                        aux.setNombre(nombre);
                        apellido=alumnoAux.apellidos;
                        aux.setApellidos(apellido);
                        aux.setTelefono(alumnoAux.telefono);
                        direccion= alumnoAux.direccion;
                        aux.setDireccion(direccion);
                        email= alumnoAux.email;
                        aux.setEmail(email);
                        fechaNacimiento= alumnoAux.fechaNacimiento;
                        aux.setFechaNacimiento(fechaNacimiento);
                        aux.setCurso(alumnoAux.curso);
                        aux.setEquipo(alumnoAux.equipo);
                        aux.setLider(convertirStringLider(alumnoAux.lider));
                        listaAlumnos_.push_back(aux);
                        encontrado=false;
                }else{
                }
                file.read(reinterpret_cast <char *> (&alumnoAux), sizeof(RegistroAlumno));
                cont++;

            }
        }

        return listaAlumnos_;
}


/**
    @fn bool Agenda::insertarAlumno(Alumno alumno)
    @brief Función que inserta un nuevo alumno en la agenda

    Esta función inserta el nuevo alumno si cumple las siguientes condiciones:
        - No hay almacenados 150 alumnos en la Agenda.
        - El alumno aún no está guardado.
        - Los campos a rellenar están correctamente cumplimentados.

    @param alumno
    @return Devuelve un booleano, si guarda al alumno devuelve true y en caso contrario false
*/
bool Agenda::insertarAlumno(Alumno alumno){
    bool correcto = false;
    int numeroRegistros=0;
    ofstream file("alumnos.bin", ios::out | ios::binary | ios::app);
    RegistroAlumno reg;

    numeroRegistros = cuentaRegistros();

    if(numeroRegistros<150){
        if(file.is_open()){
            strcpy(reg.dni,alumno.getDNI().c_str());
            strcpy(reg.nombre,alumno.getNombre().c_str());
            strcpy(reg.apellidos,alumno.getApellidos().c_str());
            reg.telefono=alumno.getTelefono();
            strcpy(reg.direccion, alumno.getDireccion().c_str());
            strcpy(reg.email, alumno.getEmail().c_str());
            strcpy(reg.fechaNacimiento,alumno.getFechaNacimiento().c_str());
            reg.curso=alumno.getCurso();
            reg.equipo=alumno.getEquipo();
            strcpy(reg.lider,convertirBoolLider(alumno.getLider()).c_str());
            file.write((char *) &reg, sizeof(RegistroAlumno));
            file.close();
            correcto = true;
        }
    }else{
        correcto=false;
    }
    return correcto;
}

/**
    @fn bool Agenda::modificarAlumno(Alumno alumno)
    @brief Función que modifica los datos de un alumno

    Esta función modifica los datos si todos ellos están cumplimentados correctamente.

    @param alumno
    @return Devuelve un booleano, si guarda al alumno devuelve true y en caso contrario false
*/
bool Agenda::modificarAlumno(Alumno alumno){
    //QWidget *parent= new QWidget;
    listaAlumnos_.clear();
    int j=0, cont=0;
    ifstream in;
    ofstream out;
    string dni1,dni2;
                    dni1 = alumno.getDNI();
    /* modificacion Oscar: añadi una variable RegistroAlumno registro */
    RegistroAlumno reg,registro;
    bool correcto = false;

        in.open("alumnos.bin", ios::in | ios::binary);
        out.open("temporal.bin", ios::out | ios::binary);

        if(in.is_open() && out.is_open()){
            strcpy(reg.dni,alumno.getDNI().c_str());
            strcpy(reg.nombre,alumno.getNombre().c_str());
            strcpy(reg.apellidos,alumno.getApellidos().c_str());
            reg.telefono=alumno.getTelefono();
            strcpy(reg.direccion, alumno.getDireccion().c_str());
            strcpy(reg.email, alumno.getEmail().c_str());
            strcpy(reg.fechaNacimiento,alumno.getFechaNacimiento().c_str());
            reg.curso=alumno.getCurso();
            reg.equipo=alumno.getEquipo();
            strcpy(reg.lider,convertirBoolLider(alumno.getLider()).c_str());
            /**************************************************/
            /* Apertura lectura y escritura de ficheros para la
            modificacion de registros */
            in.seekg(0,ios::end);
            j = in.tellg()/sizeof(RegistroAlumno);
            in.seekg(0*sizeof(RegistroAlumno));
            /*modificacion oscar: cambio reg por registro */
            in.read((char*)&registro,sizeof(RegistroAlumno));
			//out.write((char*)&reg,sizeof(RegistroAlumno));
            while(cont<j){
                /**********************/
                /*modificacion oscar*/

                dni2 = registro.dni;
                if(dni1 == dni2){
                    //QMessageBox::information(parent, "Title", "He entrado");
                    cout<<"Entra"<<endl;
                    out.write((char*)&reg,sizeof(RegistroAlumno));
                }else{
                    //QMessageBox::information(parent, "Title", "No He entrado");
                    cout<<"No Entra"<<endl;
                    out.write((char*)&registro,sizeof(RegistroAlumno));
                }
                /* fin modificacion oscar*/
                /**********************/
                //out.write((char*)&reg,sizeof(RegistroAlumno));
                in.read((char*)&registro,sizeof(RegistroAlumno));
                /**********************/
                cont++;
            }

                in.close();
                out.close();
                remove("alumnos.bin");
                rename("temporal.bin","alumnos.bin");
                correcto= true;

        }else{
            correcto= false;
        }

        return correcto;
}

/**
    @fn bool Agenda::borrarAlumno(string dni)
    @brief Función que borra los datos de un alumno
    @param dni
    @return Devuelve un booleano, si borra al alumno devuelve true y en caso contrario false
*/
bool Agenda::borrarAlumno(string dni){
    int j,cont=0;
    list<Alumno> al;
    //limpia las list creadas para no repetir la informacion a mostrar
    al.clear();
    listaAlumnos_.clear();
    RegistroAlumno alumno;
    ifstream in;
    ofstream out;
    al = mostrarAlumno(dni,"",0);
    QWidget *parent= new QWidget;


    if(al.empty()){
        cout<<"Lista vacia";
        //remove("alumnos.bin");
        return false;
    }else{
        /* Preguntara al profesor si quiere eliminar el registro del alumno*/
        /*if(encontrado){
        }*///else
            //cout<<"\nNo se pudo encontrar los datos del alumno."<<endl;

        /*En caso afirmativo procedera a actualizar la agenda */
            in.open("alumnos.bin", ios::in | ios::binary);
            out.open("temporal.bin", ios::out | ios::binary);

            if(in.is_open() && out.is_open()){

                /*Lectura y escritura de la agenda para su actualizacion */
                in.seekg(0,ios::end);
                j = in.tellg()/sizeof(RegistroAlumno);
                in.seekg(0*sizeof(RegistroAlumno));

                in.read((char *)&alumno,sizeof(RegistroAlumno));
                while(cont < j){
                    string aux1(alumno.dni);
                    if(aux1 != dni){
                        out.write((char *)&alumno,sizeof(RegistroAlumno));
                    }
                    in.read((char *)&alumno,sizeof(RegistroAlumno));
                    cont++;
                }
                in.close();
                out.close();
                remove("alumnos.bin");
                rename("temporal.bin","alumnos.bin");
            }else{
                QMessageBox::critical(parent, "This", "No se pudo abrir el fichero");
                return false;
            }

        return true;
    }
}

/**
    @fn list<Alumno> Agenda::mostrarLista()
    @brief Función que muestra todos los datos de los alumnos en una lista
    @param No recibe ningún parámetro
    @return Devuelve una lista de alumnos
*/
list<Alumno> Agenda::mostrarLista(){
    int j, cont=0;
    ifstream in("alumnos.bin", ios::in | ios::binary);
    RegistroAlumno al;
    list<Alumno> alumno;
    alumno.clear();
    Alumno aux;

    if(in.is_open()){
        in.seekg(0, ios::end);
        j = in.tellg() / sizeof(RegistroAlumno);
        in.seekg(0*sizeof(RegistroAlumno));

        //Lee todo el registro y los introduce en un objeto de clase Alumno, y el objeto estará en un list<Alumno>
        in.read((char*)&al, sizeof(RegistroAlumno));
        while(cont < j){
            aux.setDNI(al.dni);
            aux.setNombre(al.nombre);
            aux.setApellidos(al.apellidos);
            aux.setTelefono(al.telefono);
            aux.setDireccion(al.direccion);
            aux.setEmail(al.email);
            aux.setFechaNacimiento(al.fechaNacimiento);
            aux.setCurso(al.curso);
            aux.setEquipo(al.equipo);
            aux.setLider(convertirStringLider(al.lider));
            alumno.push_back(aux);
            in.read((char*)&al, sizeof(RegistroAlumno));
            cont++;
        }
        in.close();
    }
    return alumno;
}

/**
    @fn list<Alumno> Agenda::mostrarAlumno(string dni, string apellidos, int equipo)
    @brief Función que muestra todos los datos de un alumno/s buscado/s
    @param dni
    @param apellidos
    @param equipo
    @return Devuelve una lista de alumnos
*/
list<Alumno> Agenda::mostrarAlumno(string dni, string apellidos, int equipo){
    list<Alumno> aux = buscarAlumno(dni, apellidos, equipo);
    return aux;
}
