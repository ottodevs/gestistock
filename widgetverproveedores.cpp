#include "widgetverproveedores.h"
#include "ui_widgetverproveedores.h"



WidgetVerProveedores::WidgetVerProveedores(QMdiArea *ma, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetVerProveedores)
{
    ui->setupUi(this);

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));
    this->setWindowTitle(tr("Proveedores"));

    //Guardamos el puntero al QMdiArea
    mdi = ma;

    //Rura de la imagen
    rutaImagen = "";

    //La imagen la ponemos como no actualizada al principio
    fotoCargada = false;

    imagenArticulo = new QPixmap;

    consult = new QSqlQuery;
    cn = new QSqlQuery;
    cn1 = new QSqlQuery;
    actualizar = new QSqlQuery;

    //Ejecutamos la cna
    cn->exec("SELECT nombreproveedor FROM proveedores ORDER BY nombreproveedor asc");

    QStringList nombres;

    //Rellenamos el combobox
    while(cn->next())
        nombres.append(cn->value(0).toString());


    ui->cbProveedor->addItems(nombres);

    ui->leCIF->setEnabled(false);
    ui->leNombre->setEnabled(false);


    ui->leCP->setValidator(new QIntValidator(0,99999,this));
    ui->leTelefono->setValidator(new QIntValidator(0,999999999,this));
    ui->leTelefono2->setValidator(new QIntValidator(0,999999999,this));
}


void WidgetVerProveedores::on_cbProveedor_currentIndexChanged(const QString &arg1)
{

    if(ui->cbProveedor->currentText() != "")
    {
        //Rellenamos los campos de la ventana
        cn->exec("SELECT cif, nombreproveedor, codpostal, direccion, localidad, provincia, telefono1, telefono2, correo, imagen FROM proveedores WHERE nombreproveedor = '"+arg1+"' ");

        //Nos movemos en la cna
        cn->first();


        //Rellenamos los campos
        ui->leCIF->setText(cn->value(0).toString());
        ui->leNombre->setText(cn->value(1).toString());
        ui->leCP->setText(cn->value(2).toString());
        ui->leDireccion->setText(cn->value(3).toString());
        ui->leLocalidad->setText(cn->value(4).toString());
        ui->leProvincia->setText(cn->value(5).toString());
        ui->leTelefono->setText(cn->value(6).toString());
        ui->leTelefono2->setText(cn->value(7).toString());
        ui->leCorreo->setText(cn->value(8).toString());



            //Recogemos la imagen
            if(cn->value(9).toString() != NULL)
            {
                QByteArray ba1 = cn->value(9).toByteArray();
                QPixmap pic;
                pic.loadFromData(ba1);
                QPixmap imagenAjustada = pic.scaled(ui->lbImagen->size());
                ui->lbImagen->setPixmap(imagenAjustada);

            }else{

                QString im = ":/imagenes/noimagen.png";

                QPixmap imagenArticulo;
                imagenArticulo.load(im);
                QPixmap imagenAjustada = imagenArticulo.scaled(ui->lbImagen->size());
                ui->lbImagen->setPixmap(imagenAjustada);

            }
    }


}



void WidgetVerProveedores::on_pbCambiarImagen_clicked()
{
    rutaImagen = QFileDialog::getOpenFileName(this,tr("Cargar Imagen"),tr(""),tr("Imagen(*.jpg *.bmp *.png *.jpge)"));

    if(rutaImagen != "")
    {
        ui->lbImagen->clear();
        imagenArticulo->load(rutaImagen);
        QPixmap imagenAjustada = imagenArticulo->scaled(ui->lbImagen->size());
        ui->lbImagen->setPixmap(imagenAjustada);

        fotoCargada = true;
    }

}


WidgetVerProveedores::~WidgetVerProveedores()
{
    delete ui;
}

void WidgetVerProveedores::on_pbSalir_clicked()
{
    //Cerramos la ventana del mdiArea
    mdi->closeActiveSubWindow();
}


void WidgetVerProveedores::on_pbGuardarCambios_clicked()
{


    //Si se modifica la imagen, y algun otro campo o no...
    if(ui->leCIF->isModified() || ui->leCorreo->isModified() || ui->leCP->isModified() || ui->leDireccion->isModified() || ui->leLocalidad->isModified() || ui->leNombre->isModified() || ui->leProvincia->isModified() || ui->leTelefono->isModified() || ui->leTelefono2->isModified() || fotoCargada)
    {
        //El campo de iva no puede estar en blanco
        if(!ui->leCIF->text().simplified().isEmpty() && !ui->leCorreo->text().simplified().isEmpty() && !ui->leCP->text().simplified().isEmpty() && !ui->leDireccion->text().simplified().isEmpty() && !ui->leLocalidad->text().simplified().isEmpty() && !ui->leNombre->text().simplified().isEmpty() && !ui->leProvincia->text().simplified().isEmpty())
        {
            //Limpiamos la cna
            cn1->clear();

            //Si la foto ha sido cargada...
            if(fotoCargada)
            {
                //Para recoger la imagen del Qlabel
                QByteArray ba;
                QBuffer buffer(&ba);
                buffer.open(QIODevice::ReadWrite);
                ui->lbImagen->pixmap()->save(&buffer,"JPG");

                //Lo insertamos como SuperUsuario
                QSqlDatabase db = QSqlDatabase::database();

                //Iniciamos la transaccion
                db.transaction();

                //Insertamos la direccion nueva
                //cn1->exec("INSERT INTO `direcciones` (`cp`, `dir`, `localidad`, `provincia`) VALUES ('"+ui->leCP->text()+"', '"+ui->leDireccion->text()+"', '"+ui->leLocalidad->text()+"', '"+ui->leProvincia->text()+"')");

                //Actualizamos a la direccion nueva
                consult->prepare("UPDATE proveedores SET codpostal = :codpostal, direccion = :direccion, localidad = :localidad, provincia = :provincia, telefono1 = :telefono1, telefono2 = :telefono2, correo = :correo, imagen = :imagen WHERE cif = '"+ui->leCIF->text()+"'");

                consult->bindValue(":codpostal",ui->leCP->text());
                consult->bindValue(":direccion",ui->leDireccion->text());
                consult->bindValue(":localidad",ui->leLocalidad->text());
                consult->bindValue(":provincia",ui->leProvincia->text());
                consult->bindValue(":telefono1",ui->leTelefono->text());
                consult->bindValue(":telefono2",ui->leTelefono2->text());
                consult->bindValue(":correo",ui->leCorreo->text());
                consult->bindValue(":imagen",ba);

                //Borramos la direccion anterior
                //cn1->clear();
                //cn1->prepare("DELETE FROM `direcciones` WHERE `cp` = '"+cn->value(8).toString()+"' AND `dir` = '"+cn->value(2).toString()+"'");

                //Si va bien la insercion confirmamos la transaccion
                if(consult->exec())
                {
                    //Borramos la direccion anterior
                    //cn1->exec();
                    QMessageBox::information(this,tr("Información"),tr("Proveedor modificado satisfactoriamente"),tr("Aceptar"));
                    db.commit();

                }else
                    db.rollback();

                mdi->closeActiveSubWindow();

            }else{

                //Lo insertamos como SuperUsuario
                QSqlDatabase db = QSqlDatabase::database();

                //Iniciamos la transaccion
                db.transaction();

                //Insertamos la direccion nueva
                //cn1->exec("INSERT INTO `direcciones` (`cp`, `dir`, `localidad`, `provincia`) VALUES ('"+ui->leCP->text()+"', '"+ui->leDireccion->text()+"', '"+ui->leLocalidad->text()+"', '"+ui->leProvincia->text()+"')");

                //Actualizamos a la direccion nueva
                consult->prepare("UPDATE proveedores SET codpostal = :codpostal, direccion = :direccion, localidad = :localidad, provincia = :provincia, telefono1 = :telefono1, telefono2 = :telefono2, correo = :correo WHERE cif = '"+ui->leCIF->text()+"'");

                consult->bindValue(":codpostal",ui->leCP->text());
                consult->bindValue(":direccion",ui->leDireccion->text());
                consult->bindValue(":localidad",ui->leLocalidad->text());
                consult->bindValue(":provincia",ui->leProvincia->text());
                consult->bindValue(":telefono1",ui->leTelefono->text());
                consult->bindValue(":telefono2",ui->leTelefono2->text());
                consult->bindValue(":correo",ui->leCorreo->text());

                //Borramos la direccion anterior
                //cn1->clear();
                //cn1->exec("DELETE FROM `direcciones` WHERE `cp` = '"+cn->value(8).toString()+"' AND `dir` = '"+cn->value(2).toString()+"'");

                //Si va bien la insercion confirmamos la transaccion
                if(consult->exec())
                {
                    db.commit();
                    QMessageBox::information(this,tr("Información"),tr("Proveedor modificado satisfactoriamente"),tr("Aceptar"));
                    //Borramos la direccion anterior
                    //cn1->exec();
                }else{
                    db.rollback();
                    QMessageBox::critical(this,tr("Error"),tr("No se ha podido modificar el proveedor, revise los datos"),tr("Aceptar"));
                }
            }

            mdi->closeActiveSubWindow();

        }else
            QMessageBox::critical(this,tr("Error"),tr("Hay campos incompletos"),tr("Aceptar"));


    }else
        QMessageBox::warning(this,tr("Aviso"),tr("No ha modificado ningún campo"),tr("Aceptar"));

}


void WidgetVerProveedores::on_pbEliminar_clicked()
{
    QMessageBox msgBox(this);


    msgBox.setWindowTitle(tr("Eliminar"));
    msgBox.setText(tr("Eliminar Proveedor                                               "));
    msgBox.setInformativeText(tr("¿Está seguro de que desea eliminar el proveedor seleccionado?"));
    msgBox.setIcon(QMessageBox::Question);
    msgBox.addButton(tr("Si"),QMessageBox::AcceptRole);

    //Guardamos el boton en una variable para despues hacerlo por defecto
    QPushButton *pb = msgBox.addButton(tr("No"),QMessageBox::RejectRole);

    //Por defecto el boton que saldra sombreado
    msgBox.setDefaultButton(pb);

    //Devuelve la respuesta que hayamos dado, si contesta que no, ignoramos el evento de cierre
    if(!msgBox.exec())
    {

        actualizar->prepare("DELETE FROM proveedores WHERE nombreproveedor = '"+ui->cbProveedor->currentText()+"' ");
        //Si se borra....
        if(actualizar->exec())
        {
            //Borramos el item del combobox
            ui->cbProveedor->removeItem(ui->cbProveedor->currentIndex());
            QMessageBox::information(this,tr("Proveedor Eliminado"),tr("El proveedor se ha eliminado"),tr("Aceptar"));

            //Si no hay mas proveedores, cierro la ventana
            if(ui->cbProveedor->currentText() == "")
                mdi->closeActiveSubWindow();


        }else
            QMessageBox::critical(this,tr("Error"),tr("No se ha podido eliminar el proveedor, compruebe la actividad"),tr("Aceptar"));

    }


}


void WidgetVerProveedores::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}
