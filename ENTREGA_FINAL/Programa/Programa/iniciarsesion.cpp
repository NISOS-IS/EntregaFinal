#include "iniciarsesion.h"
#include "ui_iniciarsesion.h"
#include "menu.h"
#include "profesor.h"
#include "profesoraux.h"

IniciarSesion::IniciarSesion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IniciarSesion)
{
    ui->setupUi(this);
}

IniciarSesion::~IniciarSesion()
{
    delete ui;
}

void IniciarSesion::on_pushButtonCancelar_clicked()
{
    hide();
}

void IniciarSesion::on_pushButtonAceptar_clicked()
{
    Profesor profesor;
    Profesor inicio;
    string usuario, contrasena, contrasenaAux;
    bool encontrado=false, habilitar=true;

    if(ui->lineEditUsuario->text().isEmpty()){
        QMessageBox::critical(this, "Error", "El usuario no está disponible");
        habilitar=false;
    }

    if(ui->lineEditContrasena->text().isEmpty()){
        QMessageBox::critical(this, "Error", "La contraseña debe tener al menos 4 caracteres");
        habilitar=false;
    }

    usuario= ui->lineEditUsuario->displayText().toStdString();
    contrasenaAux= ui->lineEditContrasena->text().toStdString();
    contrasena= contrasenaAux;
    inicio.setUsuario(usuario.c_str());
    inicio.setContrasena(contrasena.c_str());

	if(habilitar==true){
		encontrado = profesor.login(inicio);
		if(encontrado==true){
            bool rol= compruebaRol(inicio);
		    Menu *ventana = new Menu(rol);
		    ventana->show();
            /* agregado para que no se quede la ventana de datos de inicio de sesion abierta */
            delete this;
	   }else{
		    QMessageBox::critical(this, "Fallo al Iniciar Sesión", "El usuario o la contraseña son inválidos");
		    habilitar=false;
		}
	}
}
