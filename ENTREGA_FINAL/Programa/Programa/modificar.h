#ifndef MODIFICAR_H
#define MODIFICAR_H

#include <QDialog>

namespace Ui {
class Modificar;
}

class Modificar : public QDialog
{
    Q_OBJECT

public:
    explicit Modificar(const QString &dni,QWidget *parent = 0);
    ~Modificar();

private slots:
    void on_pushButtonCancelar_clicked();

    void on_pushButtonAceptar_clicked();

private:
    Ui::Modificar *ui;
    QString dni_;
};

#endif // MODIFICAR_H
