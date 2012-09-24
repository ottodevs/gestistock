#include "widgetmodificarempresa.h"
#include "ui_widgetmodificarempresa.h"

WidgetModificarEmpresa::WidgetModificarEmpresa(QMdiArea *ma, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetModificarEmpresa)
{
    ui->setupUi(this);

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));
    this->setWindowTitle(tr("Modificar Empresa"));

    imagenArticulo = new QPixmap();

    //Puntero al MdiArea
    mdi = ma;

    //Reserva de memoria
    consultaEmpresa = new QSqlQuery;
    consultaDireccion = new QSqlQuery;
    queryEmpresa = new QSqlQuery;


    queryEmpresa->exec("select * from empresa");

    //Nos situamos en la consulta
    queryEmpresa->first();

    //consultaDireccion->exec("SELECT localidad,provincia FROM direcciones WHERE cp = '"+queryEmpresa->value(2).toString()+"' AND dir = '"+queryEmpresa->value(3).toString()+"' ");
    //consultaDireccion->first();

    //Rellenamos los campos
    ui->leCIF->setText(queryEmpresa->value(0).toString());
    ui->leNombreEmpresa->setText(queryEmpresa->value(1).toString());
    ui->leCP->setText(queryEmpresa->value(2).toString());
    ui->leDireccionEmpresa->setText(queryEmpresa->value(3).toString());
    ui->leLocalidad->setText(queryEmpresa->value(4).toString());
    ui->leProvincia->setText(queryEmpresa->value(5).toString());
    ui->leTelefono->setText(queryEmpresa->value(6).toString());
    ui->leTelefono2->setText(queryEmpresa->value(7).toString());
    ui->leCorreoEmpresa->setText(queryEmpresa->value(8).toString());




    //Si tiene imagen la cagamos
    if(!queryEmpresa->value(9).isNull())
    {
        QByteArray ba1 = queryEmpresa->value(9).toByteArray();
        QPixmap pic;
        pic.loadFromData(ba1);
        QPixmap imagenAjustada = pic.scaled(ui->lbImagen->size());
        ui->lbImagen->setPixmap(imagenAjustada);

    }

    //Inicialmente la imagen no es actualizada
    imagenActualizada = false;

    //Bloqueamos el cif para no poder modificarlo
    ui->leCIF->setEnabled(false);


    ui->leCP->setValidator(new QIntValidator(0,99999,this));
    ui->leTelefono->setValidator(new QIntValidator(0,999999999,this));
    ui->leTelefono2->setValidator(new QIntValidator(0,999999999,this));
}

void WidgetModificarEmpresa::on_pbCambiarImagen_clicked()
{
    rutaImagen = QFileDialog::getOpenFileName(this,tr("Cargar Imagen"),tr(""),tr("Imagen(*.jpg *.bmp *.png *.jpge)"));

    if(rutaImagen != "")
    {
        imagenArticulo->load(rutaImagen);
        QPixmap imagenAjustada = imagenArticulo->scaled(ui->lbImagen->size());
        ui->lbImagen->clear();
        ui->lbImagen->setPixmap(imagenAjustada);

        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        imagenArticulo->save(&buffer,"JPG");

        //Limpiamos la consulta
        consultaEmpresa->clear();
        //Lanzamos consulta
        consultaEmpresa->prepare("UPDATE empresa SET nombre = :nombre, codpostal = :codpostal, direccion = :direccion, localidad = :localidad, provincia = :provincia, telefono1 = :telefono1, telefono2 = :telefono2, correo = :correo, imagen = :imagen WHERE cifnif = '"+ui->leCIF->text()+"'");
        consultaEmpresa->bindValue(":imagen",ba);

        imagenActualizada = true;

    }
}

void WidgetModificarEmpresa::on_pbGuardar_clicked()
{
    //Si el usuario modifica algo...de los lineEdit...
    if(ui->leCIF->isModified() || ui->leNombreEmpresa->isModified() || ui->leDireccionEmpresa->isModified() || ui->leLocalidad->isModified() || ui->leProvincia->isModified() || ui->leCP->isModified() || ui->leTelefono->isModified() || ui->leTelefono2->isModified() || ui->leCorreoEmpresa->isModified() || imagenActualizada)
    {
        //Lo insertamos como SuperUsuario
        QSqlDatabase db = QSqlDatabase::database();

        //Iniciamos la transaccion
        db.transaction();

        //Insertamos la direccion nueva, sino se puede mysql la rechazara
        //consultaDireccion->exec("INSERT INTO `direcciones` (`cp`, `dir`, `localidad`, `provincia`) VALUES ('"+ui->leCP->text()+"', '"+ui->leDireccionEmpresa->text()+"', '"+ui->leLocalidad->text()+"', '"+ui->leProvincia->text()+"')");

        if(imagenActualizada)
        {
            consultaEmpresa->bindValue(":nombre",ui->leNombreEmpresa->text());
            consultaEmpresa->bindValue(":codpostal",ui->leCP->text());
            consultaEmpresa->bindValue(":direccion",ui->leDireccionEmpresa->text());
            consultaEmpresa->bindValue(":localidad",ui->leLocalidad->text());
            consultaEmpresa->bindValue(":provincia",ui->leProvincia->text());
            consultaEmpresa->bindValue(":telefono1",ui->leTelefono->text());
            consultaEmpresa->bindValue(":telefono2",ui->leTelefono2->text());
            consultaEmpresa->bindValue(":correo",ui->leCorreoEmpresa->text());

        }else{

            //Limpiamos consulta
            consultaEmpresa->clear();
            //Actualizamos
            consultaEmpresa->prepare("UPDATE `empresa` SET nombre = :nombre, codpostal = :codpostal, direccion = :direccion, localidad = :localidad, provincia = :provincia, telefono1 = :telefono1, telefono2 = :telefono2, correo = :correo WHERE cifnif = '"+ui->leCIF->text()+"' ");
            consultaEmpresa->bindValue(":nombre",ui->leNombreEmpresa->text());
            consultaEmpresa->bindValue(":codpostal",ui->leCP->text());
            consultaEmpresa->bindValue(":direccion",ui->leDireccionEmpresa->text());
            consultaEmpresa->bindValue(":localidad",ui->leLocalidad->text());
            consultaEmpresa->bindValue(":provincia",ui->leProvincia->text());
            consultaEmpresa->bindValue(":telefono1",ui->leTelefono->text());
            consultaEmpresa->bindValue(":telefono2",ui->leTelefono2->text());
            consultaEmpresa->bindValue(":correo",ui->leCorreoEmpresa->text());
        }


        //Borramos la direccion anterior, si no esta relacionada con ningun otro item
        //consultaDireccion->clear();
        //consultaDireccion->prepare("DELETE FROM `direcciones` WHERE `cp` = '"+queryEmpresa->value(2).toString()+"' AND `dir` = '"+queryEmpresa->value(3).toString()+"'");

        if(consultaEmpresa->exec())
        {
            //Borramos la direccion anterior
            //consultaDireccion->exec();
            QMessageBox::information(this,tr("Información"),tr("La empresa ha sido actualizada"),tr("Aceptar"));
            db.commit();
            mdi->closeActiveSubWindow();

        }else{

            QMessageBox::critical(this,tr("Error"),tr("Ha habido un error, compruebe los campos"),tr("Aceptar"));
            db.rollback();
        }

    }else
        QMessageBox::information(this,tr("Información"),tr("No se ha modificado ningún campo"),tr("Aceptar"));

}

void WidgetModificarEmpresa::on_pbSalir_clicked()
{
    mdi->closeActiveSubWindow();
}


void WidgetModificarEmpresa::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}

WidgetModificarEmpresa::~WidgetModificarEmpresa()
{
    delete ui;
}
