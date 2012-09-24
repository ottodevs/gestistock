#include "dialoganyadirarticuloproveedor.h"
#include "ui_dialoganyadirarticuloproveedor.h"

DialogAnyadirArticuloProveedor::DialogAnyadirArticuloProveedor(QString primaryKey, QSqlQueryArticulosProveedor *mp, QString consulta, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAnyadirArticuloProveedor)
{
    ui->setupUi(this);

    //Titulo de la ventana
    this->setWindowTitle(tr("Añadir artículo"));
    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));
    //Boton de ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    //Hacemos la ventana modal
    this->setModal(true);

    mpArticulosProveedor = new QSqlQueryArticulosProveedor;
    imagenArticulo = new QPixmap;
    actImagen = new QSqlQuery;
    consult = new QSqlQuery;

    mpArticulosProveedor = mp;
    consultaModel = consulta;
    codigoEAN = primaryKey;

    //Buscamos el articulo, con todas sus caracteri­sticas
    consult->exec("SELECT codigoean,descripcion,imagen FROM articulos WHERE codigoean = '"+codigoEAN+"' ");
    consult->first();

    if(consult->isValid())
    {
            ui->leCodEAN->setText(consult->value(0).toString());
            ui->leDescripcion->setText(consult->value(1).toString());

            //Si tenemos una imagen almacenada, entonces la cargamos en el frame
            if(!consult->value(2).isNull())
            {
                    QByteArray ba1 = consult->value(2).toByteArray();
                    QPixmap pic;
                    pic.loadFromData(ba1);
                    QPixmap imagenAjustada = pic.scaled(ui->lbImagen->size());
                    ui->lbImagen->setPixmap(imagenAjustada);

            }else{

                //Sino, cargamos la imagen por defecto
                QString im = ":/imagenes/noimagen.png";
                imagenArticulo->load(im);
                QPixmap imagenAjustada = imagenArticulo->scaled(ui->lbImagen->size());
                ui->lbImagen->setPixmap(imagenAjustada);

           }
    }

    //Inicializamos el combo
    inicializarCombo();

    ui->lePrecio->setValidator(new QDoubleValidator(0,99999,3,this));
    ui->lePrecio->setText("0.00");


    ui->cbProveedorArticulo->setCurrentIndex(0);
    ui->leCodEAN->setEnabled(false);
    ui->leDescripcion->setEnabled(false);

}

void DialogAnyadirArticuloProveedor::inicializarCombo()
{
    QSqlQuery combo;
    QStringList prov;

    combo.exec("SELECT nombreproveedor FROM proveedores WHERE cif NOT IN(SELECT proveedor FROM artprov WHERE codigoean = '"+codigoEAN+"') ");

    //Rellenamos comboBox
    while(combo.next())
        prov.append(combo.value(0).toString());

    ui->cbProveedorArticulo->addItems(prov);
}

DialogAnyadirArticuloProveedor::~DialogAnyadirArticuloProveedor()
{
    delete ui;
}

void DialogAnyadirArticuloProveedor::on_pbCancelar_clicked()
{
    this->close();
}

void DialogAnyadirArticuloProveedor::on_pbGuardar_clicked()
{
    QSqlQuery primaryKeyProveedor;
    QSqlQuery articuloProveedor;
    QString proveedorArticulo;

    primaryKeyProveedor.exec("SELECT cif FROM proveedores WHERE proveedores.nombreproveedor = '"+ui->cbProveedorArticulo->currentText()+"' ");
    primaryKeyProveedor.first();

    proveedorArticulo = primaryKeyProveedor.value(0).toString();

    if(!ui->lePrecio->text().simplified().isEmpty() || ui->cbProveedorArticulo->currentText() == "")
    {
        articuloProveedor.prepare("INSERT INTO artprov (`proveedor`, `codigoean`, `precio`) VALUES ('"+proveedorArticulo+"', '"+codigoEAN+"', '"+ui->lePrecio->text()+"') ");

        if(articuloProveedor.exec())
        {
            mpArticulosProveedor->refrescar(consultaModel);
            QMessageBox::information(this,tr("Información"),tr("Artículo añadido correctamente"),tr("Aceptar"));
            this->close();

        }else
            QMessageBox::critical(this,tr("Error"),tr("Revise los campos"),tr("Aceptar"));

    }else
        QMessageBox::critical(this,tr("Error"),tr("Revise los campos"),tr("Aceptar"));


}

void DialogAnyadirArticuloProveedor::on_cbProveedorArticulo_currentIndexChanged(const QString &arg1)
{/*
    QSqlQuery comprobarExistenciaArticulo;

    comprobarExistenciaArticulo.exec("SELECT artprov.precio, proveedores.cif FROM artprov, proveedores WHERE proveedores.cif = artprov.proveedor AND proveedores.nombreproveedor = '"+arg1+"' AND artprov.codigoean = '"+ui->leCodEAN->text()+"' ");
    comprobarExistenciaArticulo.first();

    if(comprobarExistenciaArticulo.isValid())
    {
        existeArticuloProveedor = true;
        //Limpiamos el lineEdit precio
        ui->lePrecio->clear();
        //Rellenamos el precio
        ui->lePrecio->setText(comprobarExistenciaArticulo.value(0).toString());

    }else{

        ui->lePrecio->clear();
        existeArticuloProveedor = false;
    }
*/
}

void DialogAnyadirArticuloProveedor::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}
