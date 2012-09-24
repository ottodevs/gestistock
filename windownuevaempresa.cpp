#include "windownuevaempresa.h"
#include "ui_windownuevaempresa.h"


WindowNuevaEmpresa::WindowNuevaEmpresa(WindowCargarDatos *wcd,QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowNuevaEmpresa)
{
    ui->setupUi(this);

    //Titulo
    this->setWindowTitle(tr("Registro Inicial"));
    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logoSolo.png"));
    //Ventana modal
    this->setWindowModality(Qt::WindowModal);

    //Bloqueamos el boton de maximizar
    this->setWindowFlags((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);

    pwcd = wcd;


    insertarUsuario = new QSqlQuery;
    insertarEmpresa = new QSqlQuery;

    //Configuracion de los campos
    //ui->leCP->setValidator(new QDoubleValidator(0,99999,3,this));
    //ui->leCP->setMaxLength(5);

    ui->leCP->setValidator(new QIntValidator(0,99999,this));
    ui->leTelefono1->setValidator(new QIntValidator(0,999999999,this));
    ui->leTelefono2->setValidator(new QIntValidator(0,999999999,this));
}


void WindowNuevaEmpresa::on_pbSalir_clicked()
{
    //Cerramos la ventana
    this->close();
}

void WindowNuevaEmpresa::on_pbLimpiar_clicked()
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



void WindowNuevaEmpresa::on_pbCompletar_clicked()
{
    //QSqlQuery insertarDireccion;
    QSqlQuery queryPass;
    bool chivato = false;


    if(ui->leNombre->text().simplified().isEmpty())
    {

        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leNombre->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;

    }else
        ui->leNombre->setStyleSheet("QLineEdit { background-color: white }");

    if(ui->leApellido1->text().simplified().isEmpty())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leApellido1->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;

    }else
        ui->leApellido1->setStyleSheet("QLineEdit { background-color: white }");

    if(ui->leApellido2->text().simplified().isEmpty())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leApellido2->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;

    }else
        ui->leApellido2->setStyleSheet("QLineEdit { background-color: white }");

    if(ui->leUsuario->text().simplified().isEmpty())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leUsuario->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;

    }else
        ui->leUsuario->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->leDNI->text().simplified().isEmpty())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leDNI->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;

    }else
        ui->leDNI->setStyleSheet("QLineEdit { background-color: white }");

    if(ui->leNombreEmpresa->text().simplified().isEmpty())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leNombreEmpresa->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leNombreEmpresa->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->lePass->text().simplified().isEmpty() || ui->leRepitePass->text() != ui->lePass->text())
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


    if(ui->leCorreo->text().simplified().isEmpty())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leCorreo->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leCorreo->setStyleSheet("QLineEdit { background-color: white }");

    if(ui->leTelefono1->text().simplified().isEmpty())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leTelefono1->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leTelefono1->setStyleSheet("QLineEdit { background-color: white }");

    if(ui->leTelefono2->text().simplified().isEmpty())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leTelefono2->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leTelefono2->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->leNombreEmpresa->text().simplified().isEmpty())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leNombreEmpresa->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leNombreEmpresa->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->leCIF->text().simplified().isEmpty())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leCIF->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leCIF->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->leDireccionEmpresa->text().simplified().isEmpty())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leDireccionEmpresa->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leDireccionEmpresa->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->leLocalidad->text().simplified().isEmpty())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leLocalidad->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leLocalidad->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->leProvincia->text().simplified().isEmpty())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leProvincia->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leProvincia->setStyleSheet("QLineEdit { background-color: white }");


    if(ui->leCP->text().simplified().isEmpty())
    {
        //Cuando haya un campo sin rellenar, lo pintamos de amarillo
        ui->leCP->setStyleSheet("QLineEdit { background-color: yellow }");
        chivato = true;
    }else
        ui->leCP->setStyleSheet("QLineEdit { background-color: white }");


    //Si hay campos sin rellenar...
    if(chivato)
        QMessageBox::critical(this,tr("Error"),tr("Tiene campos sin rellenar"),tr("Aceptar"));
    else
    {

        //Encriptamos la clave
        queryPass.exec("select AES_ENCRYPT('"+ui->lePass->text()+"','MyPass')");
        queryPass.first();


        QSqlDatabase db = QSqlDatabase::database();

        //Iniciamos la transaccion
        db.transaction();

        //insertarDireccion.prepare("INSERT INTO `direcciones` (`cp`, `dir`, `localidad`, `provincia`) VALUES ('"+ui->leCP->text()+"', '"+ui->leDireccionEmpresa->text()+"', '"+ui->leLocalidad->text()+"', '"+ui->leProvincia->text()+"')");
        insertarEmpresa->prepare("INSERT INTO `empresa` (`cifnif`, `nombre`, `codpostal`, `direccion`, `localidad`, `provincia`, `telefono1`, `telefono2`, `correo`, `imagen`) VALUES ('"+ui->leCIF->text()+"', '"+ui->leNombreEmpresa->text()+"', '"+ui->leCP->text()+"', '"+ui->leDireccionEmpresa->text()+"', '"+ui->leLocalidad->text()+"', '"+ui->leProvincia->text()+"', '"+ui->leTelefono1->text()+"', '"+ui->leTelefono2->text()+"', '"+ui->leCorreoEmpresa->text()+"', NULL)");
        insertarUsuario->prepare("INSERT INTO usuarios (nombreusuario,superusuario,refempresa,correo,dni,password,nombre,apellido1,apellido2,fechaalta) VALUES(:usuario, :superusuario, :refempresa, :correo, :dni, :pass, :nombre, :apellido1, :apellido2, :fecha)");

        insertarUsuario->bindValue(":usuario",ui->leUsuario->text());
        insertarUsuario->bindValue(":superusuario",1);
        insertarUsuario->bindValue(":refempresa",ui->leCIF->text());
        insertarUsuario->bindValue(":correo",ui->leCorreo->text());
        insertarUsuario->bindValue(":dni",ui->leDNI->text());
        insertarUsuario->bindValue(":pass",queryPass.value(0));
        insertarUsuario->bindValue(":nombre",ui->leNombre->text());
        insertarUsuario->bindValue(":apellido1",ui->leApellido1->text());
        insertarUsuario->bindValue(":apellido2",ui->leApellido2->text());
        insertarUsuario->bindValue(":fecha",QDate::currentDate());


        if(insertarEmpresa->exec() && insertarUsuario->exec())
        {
            db.commit();

            //Bloqueamos la accion nueva empresa
            pwcd->comprobarAccion();

            //Mostramos el mensaje
            QMessageBox::information(this,tr("Información"),tr("Registro completado"),tr("Aceptar"));

            //Cerramos la ventana
            this->close();

        }else{

            db.rollback();
            QMessageBox::critical(this,tr("Error"),tr("Revise los campos"),tr("Aceptar"));

        }
    }

}


WindowNuevaEmpresa::~WindowNuevaEmpresa()
{
    delete ui;
}


void WindowNuevaEmpresa::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QMainWindow::changeEvent(event);
}
