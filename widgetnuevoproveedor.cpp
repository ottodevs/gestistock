#include "widgetnuevoproveedor.h"
#include "ui_widgetnuevoproveedor.h"

WidgetNuevoProveedor::WidgetNuevoProveedor(MdiArea *mdi, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetNuevoProveedor)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Nuevo Proveedor"));

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));


    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);

    mdiArea = mdi;

    imagenArticulo = new QPixmap;

    //Inicialmente al crear el articulo no tendrá foto personalizada, tendra la por defecto
    fotoCargada = false;

    //Imagen por defecto
    QString im = ":/imagenes/noimagen.png";
    imagenArticulo->load(im);
    QPixmap imagenAjustada = imagenArticulo->scaled(ui->lbImagen->size());
    ui->lbImagen->setPixmap(imagenAjustada);
    //Fin imagen por defecto

    ui->leCP->setValidator(new QIntValidator(0,99999,this));
    ui->leTelefono->setValidator(new QIntValidator(0,999999999,this));
    ui->leTelefono2->setValidator(new QIntValidator(0,999999999,this));
}



void WidgetNuevoProveedor::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}


WidgetNuevoProveedor::~WidgetNuevoProveedor()
{
    delete ui;
}


void WidgetNuevoProveedor::on_pbGuardar_clicked()
{
    QSqlQuery insertarDireccion,insertarProveedor,comprobarDireccion;


    //comprobarDireccion.exec("SELECT direcciones.cp FROM direcciones WHERE direcciones.cp = '"+ui->leCP->text()+"' AND direcciones.dir = '"+ui->leDireccion->text()+"' ");
    //comprobarDireccion.first();

    QSqlDatabase db = QSqlDatabase::database();

    //Iniciamos la transaccion
    db.transaction();


    //insertarDireccion.prepare("INSERT INTO `direcciones` (`cp`, `dir`, `localidad`, `provincia`) VALUES ('"+ui->leCP->text()+"', '"+ui->leDireccion->text()+"', '"+ui->leLocalidad->text()+"', '"+ui->leProvincia->text()+"')");

    if(fotoCargada)
    {
        //Para recoger la imagen del Qlabel
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::ReadWrite);
        ui->lbImagen->pixmap()->save(&buffer,"JPG");

        insertarProveedor.prepare("INSERT INTO `proveedores` (cif,nombreproveedor,codpostal,direccion,localidad, provincia,telefono1,telefono2,correo,imagen) VALUES(:cif,:nombreproveedor,:codpostal,:direccion,:localidad,:provincia,:telefono1,:telefono2,:correo,:imagen)");

        insertarProveedor.bindValue(":cif",ui->leCIF->text());
        insertarProveedor.bindValue(":nombreproveedor",ui->leNombre->text());
        insertarProveedor.bindValue(":codpostal",ui->leCP->text());
        insertarProveedor.bindValue(":direccion",ui->leDireccion->text());
        insertarProveedor.bindValue(":localidad",ui->leLocalidad->text());
        insertarProveedor.bindValue(":provincia",ui->leProvincia->text());
        insertarProveedor.bindValue(":telefono1",ui->leTelefono->text());
        insertarProveedor.bindValue(":telefono2",ui->leTelefono2->text());
        insertarProveedor.bindValue(":correo",ui->leCorreo->text());
        insertarProveedor.bindValue(":imagen",ba);


    }else{

        insertarProveedor.prepare("INSERT INTO `proveedores` (cif,nombreproveedor,codpostal,direccion,localidad, provincia,telefono1,telefono2,correo) VALUES(:cif,:nombreproveedor,:codpostal,:direccion,:localidad,:provincia,:telefono1,:telefono2,:correo)");

        insertarProveedor.bindValue(":cif",ui->leCIF->text());
        insertarProveedor.bindValue(":nombreproveedor",ui->leNombre->text());
        insertarProveedor.bindValue(":codpostal",ui->leCP->text());
        insertarProveedor.bindValue(":direccion",ui->leDireccion->text());
        insertarProveedor.bindValue(":localidad",ui->leLocalidad->text());
        insertarProveedor.bindValue(":provincia",ui->leProvincia->text());
        insertarProveedor.bindValue(":telefono1",ui->leTelefono->text());
        insertarProveedor.bindValue(":telefono2",ui->leTelefono2->text());
        insertarProveedor.bindValue(":correo",ui->leCorreo->text());

    }


        if(insertarProveedor.exec())
        {
            db.commit();
            //Mostramos el mensaje
            QMessageBox::information(this,tr("Información"),tr("Registro completo"),tr("Aceptar"));

            mdiArea->closeActiveSubWindow();

        }else{

            db.rollback();
            QMessageBox::critical(this,tr("Error"),tr("Revise los campos"),tr("Aceptar"));
        }


}

void WidgetNuevoProveedor::on_pbExaminar_clicked()
{
    rutaImagen = QFileDialog::getOpenFileName(this,tr("Cargar Imagen"),tr(""),tr("Imagen(*.jpg *.bmp *.png *.jpge)"));

    if(rutaImagen != "")
    {
        imagenArticulo->load(rutaImagen);
        QPixmap imagenAjustada = imagenArticulo->scaled(ui->lbImagen->size());
        ui->lbImagen->clear();
        ui->lbImagen->setPixmap(imagenAjustada);

        fotoCargada = true;
    }
}

void WidgetNuevoProveedor::on_pbCancelar_clicked()
{
    mdiArea->closeActiveSubWindow();
}
