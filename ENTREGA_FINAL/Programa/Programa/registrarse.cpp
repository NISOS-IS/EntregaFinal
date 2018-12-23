#include "registrarse.h"
#include "ui_registrarse.h"
#include "profesor.h"
#include "funcionesAux.h"
#include <QMessageBox>

Registrarse::Registrarse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registrarse)
{
    ui->setupUi(this);
    ui->lineEditTelefono->setValidator( new QIntValidator);
}

Registrarse::~Registrarse()
{
    delete ui;
}

void Registrarse::on_pushButtonCancelar_clicked()
{
    hide();
}

void Registrarse::on_pushButtonAceptar_clicked()
{
    Profesor profesor, aux;
    RegUsu registro;
    string dni, nombre, apellidos, direccion, email, fechaNacimiento, getRol, usuario, contrasena, contrasenaAux;
    int telefono;
    char auxDNI[9];
    bool habilitar=true, rol, funcionCorrecta=false, guardadoCorrecto=false, guardar=true, emailRegistrado=true, usuarioRegistrado=true;

    QString fecha;

    if(ui->lineEditDNI->text().isEmpty()){
       QMessageBox::critical(this, "Error", "El campo DNI es obligatorio");
       habilitar=false;
    }
    if(ui->lineEditNombre->text().isEmpty()){
       QMessageBox::critical(this, "Error", "El campo Nombre es obligatorio");
       habilitar=false;
    }
    if(ui->lineEditApellidos->text().isEmpty()){
       QMessageBox::critical(this, "Error", "El campo Apellidos es obligatorio");
       habilitar=false;
    }
    if(ui->lineEditTelefono->text().isEmpty()){
       QMessageBox::critical(this, "Error", "El campo Telefono es obligatorio");
       habilitar=false;
    }
    if(ui->lineEditDireccion->text().isEmpty()){
       QMessageBox::critical(this, "Error", "El campo Direccion es obligatorio");
       habilitar=false;
    }
    if(ui->lineEditEmail->text().isEmpty()){
       QMessageBox::critical(this, "Error", "El campo Email es obligatorio");
       habilitar=false;
    }

    if(ui->lineEditUsuario->text().isEmpty()){
        QMessageBox::critical(this, "Error", "El usuario no está disponible");
        habilitar=false;
    }

    if(ui->lineEditContrasena->text().isEmpty()){
        QMessageBox::critical(this, "Error", "La contraseña debe tener al menos 4 caracteres");
        habilitar=false;
    }

    if(habilitar==true){
       dni= ui->lineEditDNI->displayText().toStdString();
       nombre= ui->lineEditNombre->displayText().toStdString();
       apellidos= ui->lineEditApellidos->displayText().toStdString();
       telefono= ui->lineEditTelefono->displayText().toInt();
       direccion= ui->lineEditDireccion->displayText().toStdString();
       email= ui->lineEditEmail->displayText().toStdString();
       fecha = ui->dateEditFecha->date().toString("dd/MM/yyyy");
       fechaNacimiento= fecha.toStdString();
       getRol= ui->comboBoxRol->currentText().toStdString();
       if(getRol=="Coordinador"){
           rol=true;
       }else{
            rol=false;
       }
       usuario= ui->lineEditUsuario->displayText().toStdString();
       //contrasena= ui->lineEditContrasena->displayText().toStdString();
       contrasenaAux= ui->lineEditContrasena->text().toStdString();
       contrasena= contrasenaAux;
       aux.setDNI(dni);
       strcpy(auxDNI, dni.c_str());
       auxDNI[8]= toupper(auxDNI[8]);
       dni= auxDNI;
       if((aux.setDNI(dni))==false){
            guardar=false;
       }

       aux.setNombre(nombre);
       aux.setApellidos(apellidos);
       if(aux.setTelefono(telefono)==false){
           guardar=false;
       }
       aux.setDireccion(direccion);

        emailRegistrado= compruebaEmailProfesor(email);
        if(emailRegistrado==false){
            if((aux.setEmail(email))==false){
                guardar=false;
            }
        }else{
            guardar=false;
            QMessageBox::critical(this, "Title", "Ese email ya esta registrado. Introduzca uno distinto");
        }

       if((aux.setFechaNacimiento(fechaNacimiento))==false){
            guardar=false;
       }

       aux.setRol(rol);

       usuarioRegistrado= compruebaUsuario(usuario);
       if(usuarioRegistrado==false){
            aux.setUsuario(usuario);
       }else{
           guardar=false;
           QMessageBox::critical(this, "Title", "Ese Usuario ya esta registrado. Introduzca uno distinto");
       }

       if((aux.setContrasena(contrasena))==false){
           QMessageBox::critical(this, "Title", "La contrasena debe tener mas de 4 caracteres");
           guardar=false;
       }

       if(guardar==true){
           strcpy(registro.usuario, usuario.c_str());
           strcpy(registro.contrasena, contrasena.c_str());
           strcpy(registro.rol, getRol.c_str());
           if(aux.buscaProfesor(dni)==false){
               funcionCorrecta= profesor.registrarProfesor(aux);
               guardadoCorrecto= ActualizarFicheroInicio(registro);

               if(funcionCorrecta==true && guardadoCorrecto==true){
                   QMessageBox::information(this, "Correcto", "Profesor Guardado");
                   //hide();
                   delete this;
               }else{
                    QMessageBox::critical(this, "Error", "Profesor No Guardado");
               }
           }else{
               QMessageBox::critical(this, "Title", "DNI existente. Introduzca uno distinto");
           }
       }
    }
}
