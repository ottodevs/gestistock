#include "dialogmodificarusuario.h"
#include "ui_dialogmodificarusuario.h"

DialogModificarUsuario::DialogModificarUsuario(QString user, QString clave, QString consulta, QSqlQueryUsuarios *mp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogModificarUsuario)
{
    ui->setupUi(this);

    //Titulo
    this->setWindowTitle(tr("Modificar Usuario"));
    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logoSolo.png"));
    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);

    //Hacemos la ventana modal
    this->setModal(true);

    usuarioActivo = user;

    //Inicialmente la imagen no ha sido actualizada
    imagenActualizada = false;

    //Reserva de memoria
    cn = new QSqlQuery;
    actualizar = new QSqlQuery;
    imagenArticulo = new QPixmap;

    //Guardamos un puntero al model
    model = mp;

    //Guardamos la consulta del table view
    consultaUsuarios = consulta;
    nombreUsuario = clave;


    qDebug() << nombreUsuario << user;

    //Bloqueamos line edit del usuario
    ui->leUsuario->setEnabled(false);

    cn->exec("SELECT superusuario,nombreusuario,correo,dni,password,nombre,apellido1,apellido2,imagen FROM usuarios WHERE usuarios.nombreUsuario = '"+nombreUsuario+"' ");
    cn->first();

    ui->leUsuario->setText(cn->value(1).toString());
    ui->leCorreo->setText(cn->value(2).toString());
    ui->leDNI->setText(cn->value(3).toString());
    ui->lePass->setText(cn->value(4).toString());
    ui->leNombre->setText(cn->value(5).toString());
    ui->leApellido1->setText(cn->value(6).toString());
    ui->leApellido2->setText(cn->value(7).toString());

    if(!cn->value(8).isNull())
    {
            QByteArray ba1 = cn->value(8).toByteArray();
            QPixmap pic;
            pic.loadFromData(ba1);
            QPixmap imagenAjustada = pic.scaled(ui->lbImagen->size());
            ui->lbImagen->setPixmap(imagenAjustada);

    }

    if(cn->value(0).toBool())
        ui->chAdministrador->setChecked(true);


    ui->lePass->setEnabled(false);
    ui->leDNI->setEnabled(false);


    //No permitimos que un mismo usuario se asigne privilegios
    if(usuarioActivo == ui->leUsuario->text())
        ui->chAdministrador->setEnabled(false);
}

DialogModificarUsuario::DialogModificarUsuario(QString usuario, QWidget *parent) :
QDialog(parent),
ui(new Ui::DialogModificarUsuario)
{
    ui->setupUi(this);

    //Titulo
    this->setWindowTitle(tr("Modificar Usuario"));
    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logoSolo.png"));
    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);


    //Hacemos la ventana modal
    this->setModal(true);

    //Inicialmente la imagen no ha sido actualizada
    imagenActualizada = false;

    model = NULL;

    //Reserva de memoria
    cn = new QSqlQuery;
    actualizar = new QSqlQuery;
    imagenArticulo = new QPixmap;

    nombreUsuario = usuario;
    usuarioActivo = usuario;

    //Bloqueamos line edit del usuario
    ui->leUsuario->setEnabled(false);

    cn->exec("SELECT superusuario,nombreusuario,correo,dni,password,nombre,apellido1,apellido2,imagen FROM usuarios WHERE usuarios.nombreUsuario = '"+nombreUsuario+"' ");
    cn->first();

    ui->leUsuario->setText(cn->value(1).toString());
    ui->leCorreo->setText(cn->value(2).toString());
    ui->leDNI->setText(cn->value(3).toString());
    ui->lePass->setText(cn->value(4).toString());
    ui->leNombre->setText(cn->value(5).toString());
    ui->leApellido1->setText(cn->value(6).toString());
    ui->leApellido2->setText(cn->value(7).toString());

    if(!cn->value(8).isNull())
    {
        QByteArray ba1 = cn->value(8).toByteArray();
        QPixmap pic;
        pic.loadFromData(ba1);
        QPixmap imagenAjustada = pic.scaled(ui->lbImagen->size());
        ui->lbImagen->setPixmap(imagenAjustada);

    }

    if(cn->value(0).toBool())
        ui->chAdministrador->setChecked(true);


    ui->lePass->setEnabled(false);
    ui->leDNI->setEnabled(false);
}



void DialogModificarUsuario::on_pbSalir_clicked()
{
    this->close();
}

void DialogModificarUsuario::on_pbCambiarImagen_clicked()
{
    rutaImagen = QFileDialog::getOpenFileName(this,tr("Cargar Imagen"),tr(""),tr("Imagen(*.jpg *.bmp *.png *.jpge)"));

    if(rutaImagen != "")
    {
        imagenArticulo->load(rutaImagen);
        QPixmap imagenAjustada = imagenArticulo->scaled(ui->lbImagen->size());
        ui->lbImagen->clear();
        ui->lbImagen->setPixmap(imagenAjustada);

        /*
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        imagenArticulo->save(&buffer,"JPG");


        actualizar->prepare("UPDATE usuarios SET imagen = :imagen, nombre = :nombre, apellido1 = :apellido1, apellido2 = :apellido2, correo = :correo, dni = :dni, superusuario = :superusuario WHERE nombreUsuario = '"+usuarioActivo+"' ");
        actualizar->bindValue(":imagen",ba);
        */

        imagenActualizada = true;
    }

}

void DialogModificarUsuario::on_pbGuardar_clicked()
{

    //Si el usuario modifica algo...de los lineEdit...
    if(ui->leNombre->isModified() || ui->leApellido1->isModified() || ui->leApellido2->isModified() || ui->leDNI->isModified() || ui->leCorreo->isModified() || ui->chAdministrador->isChecked() != cn->value(0).toBool() || imagenActualizada)
    {
        if(!ui->leNombre->text().simplified().isEmpty() && !ui->leApellido1->text().simplified().isEmpty() && !ui->leApellido2->text().simplified().isEmpty() && !ui->leDNI->text().simplified().isEmpty() && !ui->leCorreo->text().simplified().isEmpty())
        {
            if(imagenActualizada)
            {
                //Para recoger la imagen del Qlabel
                QByteArray ba;
                QBuffer buffer(&ba);
                buffer.open(QIODevice::ReadWrite);
                ui->lbImagen->pixmap()->save(&buffer,"JPG");

                actualizar->prepare("UPDATE usuarios SET imagen = :imagen, nombre = :nombre, apellido1 = :apellido1, apellido2 = :apellido2, correo = :correo, superusuario = :superusuario WHERE nombreusuario = '"+nombreUsuario+"' ");

                actualizar->bindValue(":imagen",ba);
                actualizar->bindValue(":nombre",ui->leNombre->text());
                actualizar->bindValue(":apellido1",ui->leApellido1->text());
                actualizar->bindValue(":apellido2",ui->leApellido2->text());
                actualizar->bindValue(":correo",ui->leCorreo->text());



            }else{

                actualizar->prepare("UPDATE usuarios SET nombre = :nombre, apellido1 = :apellido1, apellido2 = :apellido2, correo = :correo, superusuario = :superusuario WHERE nombreUsuario = '"+nombreUsuario+"' ");

                actualizar->bindValue(":nombre",ui->leNombre->text());
                actualizar->bindValue(":apellido1",ui->leApellido1->text());
                actualizar->bindValue(":apellido2",ui->leApellido2->text());
                actualizar->bindValue(":correo",ui->leCorreo->text());

            }


       }else
            QMessageBox::critical(this,tr("Error"),tr("Hay campos incompletos"),tr("Aceptar"));


        //Preparamos la consulta y la ejecutamos
        if(ui->chAdministrador->isChecked() == true)
            actualizar->bindValue(":superusuario",1);
        else
            actualizar->bindValue(":superusuario",0);

        //Ejecutamos la actualizacion
       if(actualizar->exec()){

            QMessageBox::information(this,tr("Información"),tr("El usuario ha sido modificado"),tr("Aceptar"));
            this->close();

       }else
            QMessageBox::critical(this,tr("Error"),tr("No se ha podido modificar el usuario"),tr("Aceptar"));


       qDebug() << actualizar->lastError();

       //Refrescamos
       if(model != NULL)
            model->refrescar(consultaUsuarios);

    }else
        QMessageBox::warning(this,tr("Aviso"),tr("No se ha modificado ningún campo"),tr("Aceptar"));



}

void DialogModificarUsuario::on_pbCamara_clicked()
{
        wb = new DialogWebCam(ui->lbImagen,&imagenActualizada);
        if(wb->disponible())
            wb->show();
}

void DialogModificarUsuario::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}


void DialogModificarUsuario::on_pbEliminar_clicked()
{
    QSqlQuery query;
    QMessageBox msgBox(this);

    msgBox.setWindowTitle(tr("Eliminar"));
    msgBox.setText(tr("Eliminar usuario                             "));
    msgBox.setInformativeText(tr("¿Está seguro de que desea eliminar el usuario del sistema?"));
    msgBox.setIcon(QMessageBox::Question);
    msgBox.addButton(tr("Si"),QMessageBox::AcceptRole);

    //Guardamos el boton en una variable para despues hacerlo por defecto
    QPushButton *pb = msgBox.addButton(tr("No"),QMessageBox::RejectRole);

    //Por defecto el boton que saldra sombreado
    msgBox.setDefaultButton(pb);

    //Si la respuesta es si...
    if(!msgBox.exec())
    {
        //query.prepare("DELETE FROM usuarios WHERE usuarios.dni =  '"+ui->leDNI->text()+"' ");
        query.prepare("UPDATE `usuarios` SET `novisible` = '0' WHERE `dni` = '"+ui->leDNI->text()+"' ");

        if(usuarioActivo != ui->leUsuario->text())
        {
            if(query.exec())
            {
                model->refrescar(consultaUsuarios);
                QMessageBox::information(this,tr("Información"),tr("El usuario ha sido eliminado"),tr("Aceptar"));
                this->close();

            }else
                QMessageBox::critical(this,tr("Error"),tr("No se ha podido eliminar el usuario, compruebe su actividad"),tr("Aceptar"));

        }else
            QMessageBox::critical(this,tr("Error"),tr("No se puede eliminar el usuario en uso"),tr("Aceptar"));
    }


}


DialogModificarUsuario::~DialogModificarUsuario()
{
    delete imagenArticulo;
    delete actualizar;
    delete cn;
    delete ui;
}
