#include "WidgetNuevaEmpresa.h"
#include "ui_WidgetNuevaEmpresa.h"

int num = 0;

WidgetNuevaEmpresa::WidgetNuevaEmpresa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetNuevaEmpresa)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModal);

    this->setWindowTitle(tr("Nueva empresa"));

    //Bloqueamos el boton de maximizar
    this->setWindowFlags((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);


}


void WidgetNuevaEmpresa::on_pbSalir_clicked()
{
    //Cerramos la ventana
    this->close();
}

void WidgetNuevaEmpresa::on_pbLimpiar_clicked()
{
    //Limpiamos Campos
    ui->leNombre->clear();
    ui->leApellido1->clear();
    ui->leApellido2->clear();
    ui->leDNI->clear();
    ui->leNombreEmpresa->clear();
    ui->leUsuario->clear();
    ui->leCorreo->clear();
    ui->leCIF->clear();

}



void WidgetNuevaEmpresa::on_pbCompletar_clicked()
{
    bool chivato = false;


    if(ui->leNombre->text() == "" || ui->leNombre->text().count(" ") == ui->leNombre->text().size())
    {
        chivato = true;
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leNombre->setStyleSheet("QLineEdit { background-color: yellow }");
    }else
        ui->leNombre->setStyleSheet("QLineEdit { background-color: white }");

    if(ui->leApellido1->text() == "" || ui->leApellido1->text().count(" ") == ui->leApellido1->text().size())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leApellido1->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leApellido1->setStyleSheet("QLineEdit { background-color: white }");

    if(ui->leApellido2->text() == "" || ui->leApellido2->text().count(" ") == ui->leApellido2->text().size())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leApellido2->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leApellido2->setStyleSheet("QLineEdit { background-color: white }");

    if(ui->leUsuario->text() == "" || ui->leUsuario->text().count(" ") == ui->leUsuario->text().size())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leUsuario->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leUsuario->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->leDNI->text() == "" || ui->leDNI->text().count(" ") == ui->leDNI->text().size())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leDNI->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leDNI->setStyleSheet("QLineEdit { background-color: white }");

    if(ui->leNombreEmpresa->text() == "" || ui->leNombreEmpresa->text().count(" ") == ui->leNombreEmpresa->text().size())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leNombreEmpresa->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leNombreEmpresa->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->lePass->text() == "" || ui->leRepitePass->text() != ui->lePass->text() || ui->lePass->text().count(" ") == ui->lePass->text().size() )
    {
        chivato = true;

        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->lePass->setStyleSheet("QLineEdit { background-color: yellow }");
        ui->leRepitePass->setStyleSheet("QLineEdit { background-color: yellow }");

                if(ui->leRepitePass->text() != ui->lePass->text())
                                QMessageBox::critical(this,tr("Error"),tr("Las contraseñas no coinciden"),tr("Aceptar"));
    }else{
        ui->lePass->setStyleSheet("QLineEdit { background-color: white }");
        ui->leRepitePass->setStyleSheet("QLineEdit { background-color: white }");
    }


    if(ui->leNombreEmpresa->text() == "" || ui->leNombreEmpresa->text().count(" ") == ui->leNombreEmpresa->text().size())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leNombreEmpresa->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leNombreEmpresa->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->leCIF->text() == "" || ui->leCIF->text().count(" ") == ui->leCIF->text().size())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leCIF->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leCIF->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->leDireccionEmpresa->text() == "" || ui->leDireccionEmpresa->text().count(" ") == ui->leDireccionEmpresa->text().size())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leDireccionEmpresa->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leDireccionEmpresa->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->leLocalidad->text() == "" || ui->leLocalidad->text().count(" ") == ui->leLocalidad->text().size())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leLocalidad->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leLocalidad->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->leProvincia->text() == "" || ui->leProvincia->text().count(" ") == ui->leProvincia->text().size())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leProvincia->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leProvincia->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->leCP->text() == "" || ui->leCP->text().count(" ") == ui->leCP->text().size())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leCP->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leCP->setStyleSheet("QLineEdit { background-color: white }");


    //Si hay campos sin rellenar...
    if(chivato)
    {
        QMessageBox::critical(this,"Error","Tienes Campos sin rellenar","Aceptar");

    }else{

        int marca = 0;

        //Comprobamos que no exista el usuario
        QSqlQuery consult;

        consult.prepare( "SELECT usuarios.Usuario FROM usuarios WHERE usuarios.Usuario = '"+ui->leUsuario->text()+"'" );

                //Activa la consulta
                consult.exec();

                if(consult.first())
                {
                    //Si coinciden los usuarios
                    if(consult.value(0).toString()== ui->leUsuario->text())
                        marca = 1;
                }


        if(marca)
        {
            QMessageBox::critical(this,tr("Error"),tr("El usuario ya existe"),tr("Aceptar"));

        }else{

            QSqlQuery insertarDatos,insertarDatos1;

            //Lo insertamos como SuperUsuario
            if(insertarDatos.prepare("INSERT INTO `usuarios` VALUES ('"+ui->leUsuario->text()+"',true,'"+ui->leCorreo->text()+"','"+ui->leDNI->text()+"',AES_ENCRYPT('"+ui->lePass->text()+"','MyPass'),'"+ui->leNombre->text()+"','"+ui->leApellido1->text()+"','"+ui->leApellido2->text()+"',CURDATE(),NULL)") && insertarDatos1.prepare("INSERT INTO `empresa` VALUES ('"+ui->leCIF->text()+"','"+ui->leNombreEmpresa->text()+"', '"+ui->leDireccionEmpresa->text()+"', '"+ui->leLocalidad->text()+"', '"+ui->leProvincia->text()+"', '"+ui->leCP->text()+"', '"+ui->leTelefono1->text()+"', '"+ui->leTelefono2->text()+"', '"+ui->leCorreoEmpresa->text()+"')"))
            {
                if(insertarDatos.exec() && insertarDatos1.exec())
                {
                    //Mostramos el mensaje
                    QMessageBox::information(this,tr("Registro Completado"),tr("Su usuario ha sido registrado satisfactoriamente"),tr("Aceptar"));

                    //Bloqueamos el boton de registro
                    wcd->comprobarAccion();

                    //Activamos la ventana principal (PADRE)
                    this->parentWidget()->setEnabled(true);

                    //Cerramos la ventana
                    this->close();
                }else
                    QMessageBox::critical(this,tr("Error"),tr("Ha habido un error, no se ha guardado la información"),tr("Aceptar"));

            }else
                QMessageBox::critical(this,tr("Error"),tr("Ha habido un error, no se ha guardado la información"),tr("Aceptar"));

        }
    }


}


WidgetNuevaEmpresa::~WidgetNuevaEmpresa()
{
    delete ui;
}

void WidgetNuevaEmpresa::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}




