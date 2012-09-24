#include "dialogcompras.h"
#include "ui_dialogcompras.h"

DialogCompras::DialogCompras(QString user, QString proveedor, QDate date, QSqlQueryArticulos *modelArticulos, QSqlQueryCompras *modelCompras, QString consultaArticulos, QString consultaCompras, WidgetIntroducirCompra *wic, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCompras)
{
    ui->setupUi(this);

    //Titulo de la ventana
    this->setWindowTitle(tr("Introducir Compra"));

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));
    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);

    this->setModal(true);

    usuarioActivo = user;

    ui->sbCantidad->setFocus();
    ui->sbCantidad->clear();


    provider = proveedor;
    mpCompras = modelCompras;
    mpAlmacen = modelArticulos;
    consultaModelCompras = consultaCompras;
    consultaModelAlmacen = consultaArticulos;
    fecha = date;
    pwic = wic;

    imagenArticulo = new QPixmap;
    actImagen = new QSqlQuery;

    //Ahora vamos a buscar el articulo con la clave primaria codEan, para sacarlo para poder modificarlo
    consult = new QSqlQuery;
    consult2 = new QSqlQuery;

    //Cargamos la imagen por defecto
    QString im = ":/imagenes/noimagen.png";
    imagenArticulo->load(im);
    QPixmap imagenAjustada = imagenArticulo->scaled(ui->lbImagen->size());
    ui->lbImagen->setPixmap(imagenAjustada);

}


DialogCompras::DialogCompras(QString user, QString codEan, QString proveedor, QDate date, QSqlQueryArticulos *modelArticulos, QSqlQueryCompras *modelCompras, QString consultaArticulos, QString consultaCompras, WidgetIntroducirCompra *wic, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCompras)
{
    ui->setupUi(this);

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));
    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    //Titulo de la ventana
    this->setWindowTitle(tr("Introducir Compra"));

    this->setModal(true);

    usuarioActivo = user;

    pwic = wic;

    ui->sbCantidad->setFocus();
    ui->sbCantidad->clear();

    provider = proveedor;
    codigoEAN = codEan;
    mpCompras = modelCompras;
    mpAlmacen = modelArticulos;
    consultaModelCompras = consultaCompras;
    consultaModelAlmacen = consultaArticulos;

    fecha = date;

    imagenArticulo = new QPixmap;
    actImagen = new QSqlQuery;

    //Ahora vamos a buscar el articulo con la clave primaria codEan, para sacarlo para poder modificarlo
    consult = new QSqlQuery;
    consult2 = new QSqlQuery;

    //Buscamos el articulo, con todas sus caracteri­sticas
    consult->exec("SELECT codigoean,descripcion,iva,imagen FROM articulos WHERE codigoean = '"+codEan+"' ");


    if(consult->first())
    {
            ui->leCodEAN->setText(consult->value(0).toString());
            //ui->lePrecio->setText(consult->value(1).toString());
            ui->leDescripcion->setText(consult->value(1).toString());
            ui->leIVA->setText(consult->value(2).toString());


            //Si tenemos una imagen almacenada, entonces la cargamos en el frame
            if(!consult->value(3).isNull())
            {

                    QByteArray ba1 = consult->value(3).toByteArray();
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

    consult->clear();
    consult->exec("SELECT precio FROM artprov WHERE proveedor = '"+provider+"' and codigoean = '"+codigoEAN+"' ");

    consult->first();

    ui->lePrecio->setText(consult->value(0).toString());

    //Desactivamos los campos
    ui->leDescripcion->setEnabled(false);
    ui->leCodEAN->setEnabled(false);

}

void DialogCompras::on_pbCancelar_clicked()
{
    this->close();
}

void DialogCompras::on_pbGuardar_clicked()
{
    QSqlQuery query,comprobarExistencia,comprobarArticuloProveedor, insertarArtProv;

    //Limpiamos la consulta
    consult->clear();

    //Lo insertamos como SuperUsuario
    QSqlDatabase db = QSqlDatabase::database();

    //Iniciamos transaccion
    db.transaction();

    comprobarExistencia.exec("SELECT articulo,cantidad FROM compraproductos WHERE proveedor = '"+provider+"' AND fecha = '"+fecha.toString("yyyy/MM/dd")+"' AND articulo = '"+ui->leCodEAN->text()+"' ");
    comprobarExistencia.first();

    comprobarArticuloProveedor.exec("SELECT * FROM artprov WHERE proveedor = '"+provider+"' and codigoean = '"+codigoEAN+"' ");
    comprobarArticuloProveedor.first();


    //Si no existe en el proveedor lo creamos
    if(!comprobarArticuloProveedor.isValid())
        insertarArtProv.exec("INSERT INTO `artprov` (`proveedor`, `codigoean`, `precio`) VALUES ('"+provider+"', '"+ui->leCodEAN->text()+"', '"+ui->lePrecio->text()+"')");


    //Si existe el artículo en la compra, lo modificamos...
    if(comprobarExistencia.isValid())
    {
        query.prepare("UPDATE `compraproductos` SET precio = '"+ui->lePrecio->text()+"', cantidad = '"+ui->sbCantidad->text()+"', iva = '"+ui->leIVA->text()+"' WHERE proveedor = '"+provider+"' and articulo = '"+codigoEAN+"' and fecha = '"+fecha.toString("yyyy/MM/dd")+"' ");

        consult->prepare("UPDATE `artprov` SET `precio` = '"+ui->lePrecio->text()+"' WHERE `proveedor` = '"+provider+"' AND `codigoean` = '"+ui->leCodEAN->text()+"' ");
        consult2->prepare("UPDATE `articulos` SET `cantidad` = `cantidad` - '"+comprobarExistencia.value(1).toString()+"' + '"+ui->sbCantidad->text()+"', `iva` = '"+ui->leIVA->text()+"' WHERE `codigoean` = '"+ui->leCodEAN->text()+"' ");

    }else{

        query.prepare("INSERT INTO `compraproductos`(`proveedor`, `fecha`, `articulo`, `precio`, `cantidad`, `iva`) VALUES ('"+provider+"', '"+fecha.toString("yyyy/MM/dd")+"', '"+ui->leCodEAN->text()+"', '"+ui->lePrecio->text()+"', '"+ui->sbCantidad->text()+"', '"+ui->leIVA->text()+"')");

        consult->prepare("UPDATE `artprov` SET `precio` = '"+ui->lePrecio->text()+"' WHERE `proveedor` = '"+provider+"' AND `codigoean` = '"+ui->leCodEAN->text()+"' ");
        consult2->prepare("UPDATE `articulos` SET `cantidad` = `cantidad` + '"+ui->sbCantidad->text()+"', `iva` = '"+ui->leIVA->text()+"' WHERE `codigoean` = '"+ui->leCodEAN->text()+"' ");
    }

    qDebug() << "Proveedor: " << provider << " CodigoEAN: " << codigoEAN << " Fecha: " << fecha.toString("yyyy/MM/dd");


    //Si las consultas estan corrrectas, confirmamos transaccion
    if(query.exec() && consult->exec() && consult2->exec())
    {
        db.commit();

        QSqlQuery *queryUsuario,*query;

        query = new QSqlQuery;
        queryUsuario = new QSqlQuery;

        queryUsuario->exec("SELECT dni FROM usuarios WHERE nombreusuario = '"+usuarioActivo+"' ");
        queryUsuario->first();

        query->exec("INSERT INTO `actividad` (`fechamov`, `articulo`, `usuario`, `tipomovimiento`, `cantidad`) VALUES (NOW(), '"+ui->leCodEAN->text()+"', '"+queryUsuario->value(0).toString()+"', 'Insertar', '"+ui->sbCantidad->text()+"')");

        QMessageBox::information(this,tr("Información"),tr("Compra añadida correctamente"),tr("Aceptar"));

        mpCompras->refrescar(consultaModelCompras);
        mpAlmacen->refrescar(consultaModelAlmacen);

        pwic->marcarCalendario();
        this->close();

    }else{

        db.rollback();
        QMessageBox::critical(this,tr("Error"),tr("Compruebe los datos de la compra"),tr("Aceptar"));
    }
}

void DialogCompras::on_leCodEAN_editingFinished()
{
    QSqlQuery query;

    query.exec("SELECT articulos.descripcion, artprov.precio, articulos.iva, articulos.imagen FROM articulos, artprov WHERE articulos.codigoean = '"+ui->leCodEAN->text()+"' AND artprov.codigoean = articulos.codigoean AND artprov.proveedor = '"+provider+"' ");
    query.first();

    if(query.isValid())
    {
        ui->leDescripcion->setText(query.value(0).toString());
        ui->lePrecio->setText(query.value(1).toString());
        ui->leIVA->setText(query.value(2).toString());

            //Si tenemos una imagen almacenada, entonces la cargamos en el frame
            if(!query.value(3).isNull())
            {

                    QByteArray ba1 = query.value(3).toByteArray();
                    QPixmap pic;
                    pic.loadFromData(ba1);
                    QPixmap imagenAjustada = pic.scaled(ui->lbImagen->size());
                    ui->lbImagen->setPixmap(imagenAjustada);

            }else{

                //Sino, cargamos la imagen por defecto
                QString im = ":/imagenes/noimagen.png";
                QPixmap imagenArticulo;
                imagenArticulo.load(im);
                QPixmap imagenAjustada = imagenArticulo.scaled(ui->lbImagen->size());
                ui->lbImagen->setPixmap(imagenAjustada);

           }
    }

    codigoEAN = ui->leCodEAN->text();
}


void DialogCompras::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}



DialogCompras::~DialogCompras()
{
    delete ui;
}
