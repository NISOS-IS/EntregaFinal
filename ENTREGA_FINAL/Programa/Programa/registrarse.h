#ifndef REGISTRARSE_H
#define REGISTRARSE_H

#include <QDialog>

namespace Ui {
class Registrarse;
}

class Registrarse : public QDialog
{
    Q_OBJECT

public:
    explicit Registrarse(QWidget *parent = 0);
    ~Registrarse();

private slots:
    void on_pushButtonCancelar_clicked();

    void on_pushButtonAceptar_clicked();

private:
    Ui::Registrarse *ui;
};

#endif // REGISTRARSE_H
