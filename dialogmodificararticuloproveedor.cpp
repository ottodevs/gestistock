#include "dialogmodificararticuloproveedor.h"
#include "ui_dialogmodificararticuloproveedor.h"

DialogModificarArticuloProveedor::DialogModificarArticuloProveedor(QString user, QString proveedor, QString primaryKey, QString consulta, QSqlQueryArticulosProveedor *mp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogModificarArticuloProveedor)
{
    ui->setupUi(this);

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));

    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);

    //Titulo de la ventana
    this->setWindowTitle(tr("Modificar Artículo"));

    //Ventana modal
    this->setModal(true);

    usuarioActivo = user;

    //Reserva de memoria
    consultaArticulo = new QSqlQuery;
    consultaAuxiliar = new QSqlQuery;
    imagenArticulo = new QPixmap;

    codEAN = primaryKey;
    consultaAct = consulta;
    model = mp;


    //Ejecutamos la consulta
    consultaArticulo->exec("SELECT articulos.codigoean, artprov.precio, proveedores.nombreproveedor, articulos.comentario, articulos.iva, articulos.descripcion, articulos.imagen FROM artprov, proveedores, articulos WHERE artprov.codigoean = '"+codEAN+"' and proveedores.cif = artprov.proveedor and articulos.codigoean = artprov.codigoean and proveedores.cif = '"+proveedor+"' ");

    if(consultaArticulo->first())
    {
        //Rellenamos los campos
        ui->leCodigoEAN->setText(consultaArticulo->value(0).toString());
        ui->lePrecio->setText(consultaArticulo->value(1).toString());
        ui->leProveedor->setText(consultaArticulo->value(2).toString());
        ui->teComentario->setText(consultaArticulo->value(3).toString());
        ui->leIVA->setText(consultaArticulo->value(4).toString());
        ui->leDescripcion->setText(consultaArticulo->value(5).toString());


        //Si tenemos una imagen almacenada, entonces la cargamos en el frame
        if(!consultaArticulo->value(6).isNull())
        {
                QByteArray ba1 = consultaArticulo->value(6).toByteArray();
                QPixmap pic;
                pic.loadFromData(ba1);
                QPixmap imagenAjustada = pic.scaled(ui->lbImagen->size());
                ui->lbImagen->setPixmap(imagenAjustada);

        }else{

            //Si no, cargamos la imagen por defecto
            QString im = ":/imagenes/noimagen.png";
            QPixmap imagenArticulo;
            imagenArticulo.load(im);
            QPixmap imagenAjustada = imagenArticulo.scaled(ui->lbImagen->size());
            ui->lbImagen->setPixmap(imagenAjustada);
        }

    }

    ui->leCodigoEAN->setEnabled(false);
    ui->leProveedor->setEnabled(false);
    ui->leDescripcion->setEnabled(false);
    ui->leIVA->setEnabled(false);
    ui->teComentario->setEnabled(false);


    ui->leIVA->setValidator(new QIntValidator(0,99,this));
    ui->lePrecio->setValidator(new QDoubleValidator(0,99999,3,this));
}



void DialogModificarArticuloProveedor::on_pbGuardar_clicked()
{
    //Si se modifica la imagen, y algun otro campo o no...
    if(ui->lePrecio->isModified())
    {
        if(!ui->lePrecio->text().isEmpty())
        {

            consultaAuxiliar->exec("SELECT cif FROM proveedores WHERE nombreproveedor = '"+ui->leProveedor->text()+"' ");
            consultaAuxiliar->first();

            //Limpiamos la consulta
            consultaArticulo->clear();
            consultaArticulo->prepare("UPDATE artprov SET precio = '"+ui->lePrecio->text()+"' WHERE codigoean = '"+ui->leCodigoEAN->text()+"' and proveedor = '"+consultaAuxiliar->value(0).toString()+"' ");

            if(consultaArticulo->exec()){

                //Refrescamos el modelo
                model->refrescar(consultaAct);
                QMessageBox::information(this,tr("Información"),tr("Artículo modificado correctamente"),tr("Aceptar"));
                this->close();

            }else
                QMessageBox::critical(this,tr("Error"),tr("No se ha podido modificar el artículo"),tr("Aceptar"));
        }else
            QMessageBox::critical(this,tr("Error"),tr("Hay campos incompletos"),tr("Aceptar"));

    }else
        QMessageBox::information(this,tr("Información"),tr("No ha modificado ningún campo"),tr("Aceptar"));

}


void DialogModificarArticuloProveedor::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}

void DialogModificarArticuloProveedor::on_pbCancelar_clicked()
{
    this->close();
}

void DialogModificarArticuloProveedor::on_teComentario_textChanged()
{
    if(ui->teComentario->toPlainText().length() > 250)
        ui->teComentario->textCursor().deletePreviousChar();
}

void DialogModificarArticuloProveedor::on_pbEliminar_clicked()
{
    QSqlQuery query,queryCif;
    QMessageBox msgBox(this);

    msgBox.setWindowTitle(tr("Eliminar"));
    msgBox.setText(tr("Eliminar artículo                             "));
    msgBox.setInformativeText(tr("¿Está seguro de que desea eliminar el artículo del proveedor?"));
    msgBox.setIcon(QMessageBox::Question);
    msgBox.addButton(tr("Si"),QMessageBox::AcceptRole);

    //Guardamos el boton en una variable para despues hacerlo por defecto
    QPushButton *pb = msgBox.addButton(tr("No"),QMessageBox::RejectRole);

    //Por defecto el boton que saldra sombreado
    msgBox.setDefaultButton(pb);

    //Si la respuesta es si...
    if(!msgBox.exec())
    {
        queryCif.exec("SELECT proveedores.cif FROM proveedores WHERE proveedores.nombreproveedor = '"+ui->leProveedor->text()+"' ");
        queryCif.first();

        query.prepare("DELETE FROM artprov WHERE artprov.codigoean =  '"+ui->leCodigoEAN->text()+"' and artprov.proveedor = '"+queryCif.value(0).toString()+"' ");

            if(query.exec())
            {
                model->refrescar(consultaAct);
                QMessageBox::information(this,tr("Información"),tr("El artículo ha sido borrado"),tr("Aceptar"));
                this->close();

            }else
                QMessageBox::critical(this,tr("Error"),tr("No se ha podido borrar el usuario, compruebe su actividad"),tr("Aceptar"));
    }
}


DialogModificarArticuloProveedor::~DialogModificarArticuloProveedor()
{
    delete imagenArticulo;
    delete ui;
}
