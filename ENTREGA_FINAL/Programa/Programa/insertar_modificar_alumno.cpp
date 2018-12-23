#include "insertar_modificar_alumno.h"
#include "ui_insertar_modificar_alumno.h"
#include <string>
#include <iostream>
#include "funcionesAux.h"
#include "agenda.h"

Insertar_Modificar_Alumno::Insertar_Modificar_Alumno(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Insertar_Modificar_Alumno)
{
    ui->setupUi(this);
    ui->lineEditTelefono->setValidator( new QIntValidator);
    ui->lineEditCurso->setValidator( new QIntValidator);
    ui->lineEditEquipo->setValidator( new QIntValidator);
}

Insertar_Modificar_Alumno::~Insertar_Modificar_Alumno()
{
    delete ui;
}

void Insertar_Modificar_Alumno::on_pushButtonAceptar_clicked()
{
    Alumno alumno;
       Agenda agenda;
       string dni, nombre, apellidos, direccion, email, fechaNacimiento, getLider;
       int telefono, curso, equipo;
       bool habilitar=true, lider, funcionCorrecta=false;

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
       if(ui->lineEditCurso->text().isEmpty()){
           QMessageBox::critical(this, "Error", "El campo Curso es obligatorio");
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
           curso= ui->lineEditCurso->displayText().toInt();
           equipo= ui->lineEditEquipo->displayText().toInt();
           getLider= ui->comboBoxLider->currentText().toStdString();
           if(getLider=="Lider"){
               lider=true;
           }else{
                lider=false;
           }

           funcionCorrecta= escribirDatos(dni, nombre, apellidos, telefono, direccion, email, fechaNacimiento, curso, equipo, lider);

           if(funcionCorrecta==true){
               QMessageBox::information(this, "Correcto", "Alumno Guardado");
               close();
           }else{
                QMessageBox::critical(this, "Error", "Alumno No Guardado");
           }
       }
}

void Insertar_Modificar_Alumno::on_pushButtonCancelar_clicked()
{
    hide();
}
