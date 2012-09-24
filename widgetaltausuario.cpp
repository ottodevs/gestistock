#include "widgetaltausuario.h"
#include "ui_widgetaltausuario.h"

#include <QDate>

//Le pasamos la camara a todos los constructores que la vayan a necesitar
WidgetAltaUsuario::WidgetAltaUsuario(QMdiArea *mdiArea,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetAltaUsuario)
{
    ui->setupUi(this);

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));

    this->setWindowTitle(tr("Nuevo Usuario"));

    mdi = mdiArea;

    insertar = new QSqlQuery;
    cn1 = new QSqlQuery;

    fotoCargada = false;

    rutaImagen = "";

    //Metemos la imagen por defecto
    a.load(":/imagenes/noimagen.png");
    fondo = new QLabel;
    fondo->setPixmap(a);
    fondo->setScaledContents(true);
    ui->gridLayout_3->addWidget(fondo);

}


void WidgetAltaUsuario::on_pbSalir_clicked()
{
    mdi->closeActiveSubWindow();
}



WidgetAltaUsuario::~WidgetAltaUsuario()
{
    delete ui;
}



void WidgetAltaUsuario::on_pbActivarCamara_clicked()
{
        wb = new DialogWebCam(fondo,&fotoCargada);
        if(wb->disponible())
            wb->show();
}



void WidgetAltaUsuario::on_pbExaminar_clicked()
{
    //Abrimos el dialogo
    rutaImagen = QFileDialog::getOpenFileName(this,tr("Cargar Imagen"),tr(""),tr("Imagen(*.jpg *.bmp *.png *.jpge)"));

      if(rutaImagen != "")
      {
            //Limpiamos el label
            fondo->clear();
            //Cargamos en el pixmap
            a.load(rutaImagen);
            fondo->setPixmap(a);

            fotoCargada = true;
      }
}





void WidgetAltaUsuario::on_pbGuardar_clicked()
{
    QSqlQuery queryPass,query,queryReactivar;
    QString cif;


    //Encriptamos la clave
    queryPass.exec("select AES_ENCRYPT('"+ui->lePass->text()+"','MyPass')");
    queryPass.first();

    insertar->clear();
    insertar->exec("SELECT cifnif FROM empresa");
    insertar->first();
    cif = insertar->value(0).toString();


    //Limpiamos la query
    insertar->clear();

    //Si se han modificado los line edit
    if(ui->leNombre->isModified() && ui->leApellido1->isModified() && ui->leApellido2->isModified() && ui->leDNI->isModified() && ui->leUsuario->isModified() && ui->leCorreo->isModified() && ui->lePass->isModified() && ui->leRepitePass->isModified())
    {

        //Si el texto introducido no es completamente espacios en blanco...
        if(!ui->leNombre->text().simplified().isEmpty() && !ui->leApellido1->text().simplified().isEmpty() && !ui->leApellido2->text().simplified().isEmpty() && !ui->leDNI->text().simplified().isEmpty() && !ui->leUsuario->text().simplified().isEmpty() && !ui->leCorreo->text().simplified().isEmpty() && !ui->lePass->text().simplified().isEmpty() && !ui->leRepitePass->text().simplified().isEmpty())
        {

            if(ui->lePass->text() == ui->leRepitePass->text())
            {
                query.exec("SELECT nombreusuario, AES_DECRYPT(password,'MyPass') FROM usuarios WHERE usuarios.dni = '"+ui->leDNI->text()+"' ");
                query.first();

                //Si existe ya el usuario
                if(query.isValid())
                {
                    QMessageBox msgBox(this);

                    msgBox.setWindowTitle(tr("Información                   "));
                    msgBox.setText(tr("Reactivar usuario"));
                    msgBox.setInformativeText(tr("¿Desea volver a activar el usuario?"));
                    msgBox.setIcon(QMessageBox::Warning);
                    msgBox.addButton(tr("Si"),QMessageBox::AcceptRole);

                    //Guardamos el boton en una variable para despues hacerlo por defecto
                    QPushButton *pb = msgBox.addButton(tr("No"),QMessageBox::RejectRole);

                    //Por defecto el boton que saldra sombreado
                    msgBox.setDefaultButton(pb);

                    //Devuelve la respuesta que hayamos dado, si contesta que si, borramos
                    if(!msgBox.exec())
                    {
                        queryReactivar.exec("UPDATE `usuarios` SET `novisible` = '0' WHERE `dni` = '"+ui->leDNI->text()+"' ");
                        QMessageBox::information(this,tr("Información"),tr("El usuario ha sido activado de nuevo, su nombre de usuario es '") + query.value(0).toString() + tr("' y su contraseña '") + query.value(1).toString() + "'");
                    }


                }else{

                    if(fotoCargada)
                    {

                        QBuffer buffer(&ba);
                        buffer.open(QIODevice::WriteOnly);
                        a.save(&buffer,"JPG");

                        //Preparamos la consulta
                        insertar->prepare("INSERT INTO usuarios (nombreusuario,superusuario,refempresa,correo,dni,password,nombre,apellido1,apellido2,fechaalta,imagen) VALUES(:usuario, :superusuario, :refempresa, :correo, :dni, :pass, :nombre, :apellido1, :apellido2, :fecha, :imagen)");
                        insertar->bindValue(":usuario",ui->leUsuario->text());

                        if(ui->chSuperUsuario->isChecked() == false)
                            insertar->bindValue(":superusuario",0);
                        else
                            insertar->bindValue(":superusuario",1);

                        insertar->bindValue(":refempresa",cif);
                        insertar->bindValue(":correo",ui->leCorreo->text());
                        insertar->bindValue(":dni",ui->leDNI->text());
                        insertar->bindValue(":pass",queryPass.value(0));
                        insertar->bindValue(":nombre",ui->leNombre->text());
                        insertar->bindValue(":apellido1",ui->leApellido1->text());
                        insertar->bindValue(":apellido2",ui->leApellido2->text());
                        insertar->bindValue(":fecha",QDate::currentDate());
                        insertar->bindValue(":imagen",ba);

                        if(insertar->exec())
                        {
                            QMessageBox::information(this,tr("Información"),tr("El usuario ha sido creado"),tr("Aceptar"));

                            //Cerramos la ventana
                            mdi->closeActiveSubWindow();

                        }else
                            QMessageBox::critical(this,tr("Error"),tr("Revise los campos"),tr("Aceptar"));

                    }else{


                        //Preparamos la consulta
                        insertar->prepare("INSERT INTO usuarios (nombreusuario,superusuario,refempresa,correo,dni,password,nombre,apellido1,apellido2,fechaalta) VALUES(:usuario, :superusuario, :refempresa, :correo, :dni, :pass, :nombre, :apellido1, :apellido2, :fecha)");

                        insertar->bindValue(":usuario",ui->leUsuario->text());

                        if(ui->chSuperUsuario->isChecked() == false)
                            insertar->bindValue(":superusuario",0);
                        else
                            insertar->bindValue(":superusuario",1);



                        insertar->bindValue(":refempresa",cif);
                        insertar->bindValue(":correo",ui->leCorreo->text());
                        insertar->bindValue(":dni",ui->leDNI->text());
                        insertar->bindValue(":pass",queryPass.value(0));
                        insertar->bindValue(":nombre",ui->leNombre->text());
                        insertar->bindValue(":apellido1",ui->leApellido1->text());
                        insertar->bindValue(":apellido2",ui->leApellido2->text());
                        insertar->bindValue(":fecha",QDate::currentDate());


                        if(insertar->exec())
                        {
                            QMessageBox::information(this,tr("Información"),tr("El usuario ha sido creado"),tr("Aceptar"));
                            //Cerramos la ventana
                            mdi->closeActiveSubWindow();

                        }else
                            QMessageBox::critical(this,tr("Error"),tr("Revise los campos"),tr("Aceptar"));


                    }
                }

            }else
                QMessageBox::critical(this,tr("Error"),tr("Las contraseñas no coinciden"),tr("Aceptar"));

        }else
            QMessageBox::critical(this,tr("Error"),tr("Tiene campos en blanco"),tr("Aceptar"));

    }else
        QMessageBox::warning(this,tr("Aviso"),tr("Hay campos incompletos"),tr("Aceptar"));

}

void WidgetAltaUsuario::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}
