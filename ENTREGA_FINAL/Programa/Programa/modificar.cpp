#include "modificar.h"
#include "ui_modificar.h"
#include <string>
#include <iostream>
#include "funcionesAux.h"
#include "agenda.h"

Modificar::Modificar(const QString &dni, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Modificar),
    dni_(dni)
{
    ui->setupUi(this);

    ui->lineEditTelefono->setValidator( new QIntValidator);
    ui->lineEditCurso->setValidator( new QIntValidator);
    ui->lineEditEquipo->setValidator( new QIntValidator);

    Agenda agenda;
               list<Alumno>aux;
               aux= agenda.buscarAlumno(dni.toStdString(), "", 0);
               for (list<Alumno>::iterator it = aux.begin();it != aux.end(); it++){
                   ui->lineEditDNI->setText(it->getDNI().c_str());
                   ui->lineEditDNI->setEnabled(false);
                   ui->lineEditNombre->setText(it->getNombre().c_str());
                   ui->lineEditApellidos->setText(it->getApellidos().c_str());
                   QString telefono = QString::number(it->getTelefono());
                   ui->lineEditTelefono->setText(telefono);
                   ui->lineEditDireccion->setText(it->getDireccion().c_str());
                   ui->lineEditEmail->setText(it->getEmail().c_str());
                   ui->lineEditEmail->setEnabled(false);
                   QString fecha_nacimiento = it->getFechaNacimiento().c_str();
                   QDate fecha;
                   fecha.fromString(fecha_nacimiento,"dd/MM/YYYY");
                   ui->dateEditFecha->text();
                   QString curso = QString::number(it->getCurso());
                   ui->lineEditCurso->setText(curso);
                   QString equipo = QString::number(it->getEquipo());
                   ui->lineEditEquipo->setText(equipo);
                   QString lider = QString::fromStdString(convertirBoolLider(it->getLider()));
                   int esLider = ui->comboBoxLider->findText(lider);
                   if ( esLider != -1 ) { // -1 for not found
                      ui->comboBoxLider->setCurrentIndex(esLider);
                   }
               }
}

Modificar::~Modificar()
{
    delete ui;
}

void Modificar::on_pushButtonCancelar_clicked()
{
    hide();
}

void Modificar::on_pushButtonAceptar_clicked()
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

                       funcionCorrecta= modificarDatos(dni, nombre, apellidos, telefono, direccion, email, fechaNacimiento, curso, equipo, lider);
                   if(funcionCorrecta==true){
                       QMessageBox::information(this, "Correcto", "Alumno Guardado");
                       close();
                   }else{
                        QMessageBox::critical(this, "Error", "Alumno No Guardado");
                   }
               }
}
