#include "menu.h"
#include "ui_menu.h"
#include "insertar_modificar_alumno.h"
#include "profesor.h"
#include "modificar.h"
#include <QMessageBox>
#include <QInputDialog>
#include <ctype.h>
#include <list>
#include "agenda.h"
#include "funcionesAux.h"
#include "alumno.h"

int elegir=0;

Menu::Menu(const bool &rol, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu),
    rol_(rol)
{
    ui->setupUi(this);
    if(rol==true){
        ui->pushButtonGuardarCopia->setEnabled(false);
        ui->pushButtonCargarCopia->setEnabled(false);
    }
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButtonInsertarAlumno_clicked()
{
    Insertar_Modificar_Alumno *ventana= new Insertar_Modificar_Alumno;
    ventana->show();
}

void Menu::on_pushButtonMostrarAlumno_clicked()
{
              ui->tableWidgetListado->setEditTriggers(QAbstractItemView::NoEditTriggers);
            while(ui->tableWidgetListado->rowCount()>0){
                ui->tableWidgetListado->removeRow(0);
            }
            ui->tableWidgetListado->setColumnCount(10);
    Agenda agenda;
        list<Alumno> aux;
        QStringList opciones;
        opciones <<"DNI";
        opciones <<"Apellido";
        opciones <<"Equipo";
        QString opcion = QInputDialog::getItem(this, "Elemento", "¿Por qué campo desea buscar?", opciones);

        if(opcion=="DNI"){
            QString dni= QInputDialog::getText(this, "Entrada", "Introduce el dni");
            string DNI= dni.toStdString();
            char auxDNI[9];
            strcpy(auxDNI, DNI.c_str());
            auxDNI[8]=toupper(auxDNI[8]);
            DNI=auxDNI;
            aux= agenda.mostrarAlumno(DNI, "", 0);
        }
        else if(opcion=="Apellido"){
            QString apellidos = QInputDialog::getText(this, "Entrada", "Introduce el apellido");
            string apellido = apellidos.toStdString();
            apellido = mayusculas(apellido);
            aux= agenda.mostrarAlumno("", apellido, 0);
        }
        else if(opcion=="Equipo"){
            QString equipo = QInputDialog::getText(this, "Entrada", "Introduce el número del equipo");
            int eq = equipo.toInt();
            aux= agenda.mostrarAlumno("", "", eq);
        }
        else{
            QMessageBox::critical(this, "Error", "Opción no válida");
        }
        if(aux.empty()){
            QMessageBox::information(this, "¡Atención!", "La Agenda está vacía");
        }
        else{
            /*ui->tableWidgetListado->setEditTriggers(QAbstractItemView::NoEditTriggers);
            while(ui->tableWidgetListado->rowCount()>0){
                ui->tableWidgetListado->removeRow(0);
            }
            ui->tableWidgetListado->setColumnCount(10);*/
            QStringList cabeceras;
            cabeceras <<"DNI" <<"Nombre"<<"Apellidos"<<"Telefono"<<"Direccion"<<"E-mail"<<"FechaNacimiento"<<"Curso"<<"Equipo"<<"Lider";
            ui->tableWidgetListado->setHorizontalHeaderLabels(cabeceras);
            for (list<Alumno>::iterator it = aux.begin(); it != aux.end();it++){
                ui->tableWidgetListado->insertRow(ui->tableWidgetListado->rowCount());

                QString dni = QString::fromStdString(it->getDNI());
                ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 0, new QTableWidgetItem(dni));

                QString nombre = QString::fromStdString(it->getNombre());
                ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 1, new QTableWidgetItem(nombre));

                QString apellidos = QString::fromStdString(it->getApellidos());
                ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 2, new QTableWidgetItem(apellidos));

                QString telefono = QString::number(it->getTelefono());
                ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 3, new QTableWidgetItem(telefono));

                QString direccion = QString::fromStdString(it->getDireccion());
                ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 4, new QTableWidgetItem(direccion));

                QString email = QString::fromStdString(it->getEmail());
                ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 5, new QTableWidgetItem(email));

                QString fechaNacimiento = QString::fromStdString(it->getFechaNacimiento());
                ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 6, new QTableWidgetItem(fechaNacimiento));

                QString curso = QString::number(it->getCurso());
                ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 7, new QTableWidgetItem(curso));

                QString equipo = QString::number(it->getEquipo());
                ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 8, new QTableWidgetItem(equipo));

                QString lider = QString::fromStdString(convertirBoolLider(it->getLider()));
                ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 9, new QTableWidgetItem(lider));
            }
            
        }
        aux.clear();
}

void Menu::on_pushButtonBorrarAlumno_clicked()
{
    elegir=1;
    rellenarTabla();
}

void Menu::on_pushButtonModificarAlumno_clicked()
{
      elegir=2;
      rellenarTabla();
}

void Menu::on_pushButtonListadoAlumnos_clicked()
{
    Agenda agenda;
        list<Alumno>aux = agenda.mostrarLista();
        if(aux.empty()){
           QMessageBox::information(this, "¡Atención!", "La Agenda esta vacia");
        }else {
            ui->tableWidgetListado->setEditTriggers(QAbstractItemView::NoEditTriggers);
            while (ui->tableWidgetListado->rowCount() > 0)
            {
               ui->tableWidgetListado->removeRow(0);
            }
           ui->tableWidgetListado->setColumnCount(10);
           QStringList cabeceras;
           cabeceras <<"DNI" <<"Nombre"<<"Apellidos"<<"Telefono"<<"Direccion"<<"E-mail"<<"FechaNacimiento"<<"Curso"<<"Equipo"<<"Lider";
           ui->tableWidgetListado->setHorizontalHeaderLabels(cabeceras);
           for (list<Alumno>::iterator it = aux.begin();it != aux.end(); it++){
                    ui->tableWidgetListado->insertRow(ui->tableWidgetListado->rowCount());

                    QString dni = QString::fromStdString(it->getDNI());
                    ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 0, new QTableWidgetItem(dni));

                    QString nombre = QString::fromStdString(it->getNombre());
                    ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 1, new QTableWidgetItem(nombre));

                    QString apellidos = QString::fromStdString(it->getApellidos());
                    ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 2, new QTableWidgetItem(apellidos));

                    QString telefono = QString::number(it->getTelefono());
                    ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 3, new QTableWidgetItem(telefono));

                    QString direccion = QString::fromStdString(it->getDireccion());
                    ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 4, new QTableWidgetItem(direccion));

                    QString email = QString::fromStdString(it->getEmail());
                    ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 5, new QTableWidgetItem(email));

                    QString fechaNacimiento = QString::fromStdString(it->getFechaNacimiento());
                    ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 6, new QTableWidgetItem(fechaNacimiento));

                    QString curso = QString::number(it->getCurso());
                    ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 7, new QTableWidgetItem(curso));

                    QString equipo = QString::number(it->getEquipo());
                    ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 8, new QTableWidgetItem(equipo));

                    QString lider = QString::fromStdString(convertirBoolLider(it->getLider()));
                    ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 9, new QTableWidgetItem(lider));

                }
//                aux.clear();
        }
        aux.clear();
}

void Menu::on_pushButtonGuardarCopia_clicked()
{
    bool correcto=false;
    Profesor profesor;
    correcto= profesor.guardarCopia();
    if(correcto==true){
        QMessageBox::information(this, "Correcto", "Copia de Seguridad Guardada");
    }else{
        QMessageBox::critical(this, "Error", "Error al Guardar la Copia de Seguridad");
    }
}

void Menu::on_pushButtonCargarCopia_clicked()
{
    bool correcto=false;
    Profesor profesor;
    correcto= profesor.cargarCopia();
    if(correcto==true){
        QMessageBox::information(this, "Correcto", "Copia de Seguridad Cargada");
    }else{
        QMessageBox::critical(this, "Error", "Error al Cargar la Copia de Seguridad");
    }
}

void Menu::on_pushButtonSalir_clicked()
{
   hide();
}

void Menu::rellenarTabla(){
  /*ui->tableWidgetListado->setEditTriggers(QAbstractItemView::NoEditTriggers);
          while (ui->tableWidgetListado->rowCount() > 0)
          {
              ui->tableWidgetListado->removeRow(0);
          }
         ui->tableWidgetListado->setColumnCount(3);*/
    Agenda agenda;
      list<Alumno>aux;

      QStringList opciones;
      QString dni, apellidos;
      string DNI, apellido;

      opciones <<"DNI";
      opciones <<"Apellido";
      QString opcion= QInputDialog::getItem(this, "Elemento", "¿Por qué campo desea buscar?", opciones);

      if(opcion=="DNI"){
          dni= QInputDialog::getText(this, "Entrada", "Introduce el dni");
          DNI= dni.toStdString();
          char auxDNI[9];
          strcpy(auxDNI, DNI.c_str());
          auxDNI[8]= toupper(auxDNI[8]);
          DNI= auxDNI;
          DNI= mayusculas(DNI);
          aux= agenda.mostrarAlumno(DNI, "", 0);
      }else if(opcion=="Apellido"){
         apellidos= QInputDialog::getText(this, "Entrada", "Introduce el apellidos");
         apellido= apellidos.toStdString();
         apellido= mayusculas(apellido);
         aux= agenda.mostrarAlumno("", apellido, 0);
      }else{
          QMessageBox::critical(this, "Error", "Opcion no válida");
      }

      if(aux.empty()){
         QMessageBox::information(this, "¡Atención!", "La Agenda esta vacia");
      }else {
         ui->tableWidgetListado->setEditTriggers(QAbstractItemView::NoEditTriggers);
          while (ui->tableWidgetListado->rowCount() > 0)
          {
              ui->tableWidgetListado->removeRow(0);
          }
         ui->tableWidgetListado->setColumnCount(3);
         QStringList cabeceras;
         cabeceras <<"DNI" <<"Nombre"<<"Apellidos";
         ui->tableWidgetListado->setHorizontalHeaderLabels(cabeceras);
         for (list<Alumno>::iterator it = aux.begin();it != aux.end(); it++){
            ui->tableWidgetListado->insertRow(ui->tableWidgetListado->rowCount());
            QString dni = QString::fromStdString(it->getDNI());
            ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 0, new QTableWidgetItem(dni));
            QString nombre = QString::fromStdString(it->getNombre());
            ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 1, new QTableWidgetItem(nombre));
            QString apellidos = QString::fromStdString(it->getApellidos());
            ui->tableWidgetListado->setItem(ui->tableWidgetListado->rowCount()-1, 2, new QTableWidgetItem(apellidos));
          }
              //aux.clear();
      }
      aux.clear();
}

void Menu::on_tableWidgetListado_cellActivated(int row, int column)
{
    QString dni;
    column=0;
    dni = ui->tableWidgetListado->item(row, column)->text();
    if(elegir==1){
        Agenda agenda;
        bool correcto=false;
        string DNI= dni.toStdString();
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Test", "¿Desea Borrar este alumno",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            correcto= agenda.borrarAlumno(DNI);
        }else if (reply == QMessageBox::No) {
            //hide();
        }
        if(correcto==true){
            QMessageBox::information(this, "Correcto", "Alumno Borrado");
            ui->tableWidgetListado->removeRow(row);
        }else{
            QMessageBox::critical(this, "Error", "Error al borrar Alumno");
        }
    }else if (elegir==2) {
        Modificar *ventana= new Modificar(dni);
        ventana->show();
    }

}
