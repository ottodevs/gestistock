#include "dialogcambiarcontrasenia.h"
#include "ui_dialogcambiarcontrasenia.h"

DialogCambiarContrasenia::DialogCambiarContrasenia(QString userActivo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCambiarContrasenia)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Cambiar Contraseña"));

    this->setWindowIcon(QIcon(":/imagenes/password.png"));

    this->setModal(true);

    //this->UsuarioActivo = new QString;
    this->UsuarioActivo = userActivo;

    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);

}


void DialogCambiarContrasenia::on_pbCambiar_clicked()
{
    QSqlQuery cnslt;

    cnslt.exec("SELECT nombreusuario, AES_DECRYPT(password,'MyPass') FROM usuarios WHERE nombreusuario = '"+UsuarioActivo+"' ");

    //Nos situamos en la consulta
    cnslt.first();

        //Coincide la antigua contraseña
        if(cnslt.value(1).toString() == ui->leAntigua->text())
        {
            //Coinciden los campos nueva y repetir nueva
            if(ui->leNueva->text() == ui->leRepetir->text())
            {
                if(cnslt.exec("UPDATE usuarios SET password = AES_ENCRYPT('"+ui->leRepetir->text()+"','MyPass')  WHERE nombreusuario = '"+UsuarioActivo+"' ")){
                    QMessageBox::information(this,tr("Información"),tr("Contraseña actualizada"),tr("Aceptar"));
                    this->close();
                }
            }else
                QMessageBox::critical(this,tr("Error"),tr("Las contraseñas no coinciden"),tr("Aceptar"));
        }else
            QMessageBox::critical(this,tr("Error"),tr("La contraseña anterior no es correcta"),tr("Aceptar"));

}

void DialogCambiarContrasenia::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}


DialogCambiarContrasenia::~DialogCambiarContrasenia()
{
    delete ui;
}

