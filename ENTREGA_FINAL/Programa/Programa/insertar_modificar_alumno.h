#ifndef INSERTAR_MODIFICAR_ALUMNO_H
#define INSERTAR_MODIFICAR_ALUMNO_H

#include <QDialog>

namespace Ui {
class Insertar_Modificar_Alumno;
}

class Insertar_Modificar_Alumno : public QDialog
{
    Q_OBJECT

public:
    explicit Insertar_Modificar_Alumno(QWidget *parent = 0);
    ~Insertar_Modificar_Alumno();

private slots:
    void on_pushButtonAceptar_clicked();

    void on_pushButtonCancelar_clicked();

private:
    Ui::Insertar_Modificar_Alumno *ui;
};

#endif // INSERTAR_MODIFICAR_ALUMNO_H
