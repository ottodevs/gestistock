#include "dialogsalidaarticulo.h"
#include "ui_dialogsalidaarticulo.h"

DialogSalidaArticulo::DialogSalidaArticulo(QString user, QString codEAN, QSqlQueryArticulos *modelArticulos, QSqlQuerySalidas *modelSalidas, QString consultaActivaArt, QString consultaActivaSal, QDate date, WidgetSalidasArticulos *wsa, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSalidaArticulo)
{
    ui->setupUi(this);

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));
    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    //Titulo de la ventana
    this->setWindowTitle(tr("Salida de Artículos"));
    //Ventana modal
    this->setModal(true);

    datos = new QSqlQuery;
    querySalidas = new QSqlQuery;

    ui->sbCantidad->setFocus();
    ui->sbCantidad->clear();

    usuarioActivo = user;
    codigoEAN = codEAN;
    mpArticulos = modelArticulos;
    mpSalidas = modelSalidas;
    consultaModelArt = consultaActivaArt;
    consultaModelSal = consultaActivaSal;
    fecha = date;
    pwsa = wsa;

    ui->deFecha->setDate(fecha);

    datos->exec("SELECT codigoean, tipoproducto, descripcion, cantidad, imagen FROM articulos WHERE codigoean = '"+codigoEAN+"' ");

    if(datos->first())
    {

        ui->leCodEAN->setText(datos->value(0).toString());
        ui->leTipo->setText(datos->value(1).toString());
        ui->leDescripcion->setText(datos->value(2).toString());
        ui->sbCantidad->setMaximum(datos->value(3).toInt());

        //Si tenemos una imagen almacenada, entonces la cargamos en el frame
        if(!datos->value(4).isNull())
        {

            QByteArray ba1 = datos->value(4).toByteArray();
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

    ui->leCodEAN->setEnabled(false);
    ui->leDescripcion->setEnabled(false);
    ui->leTipo->setEnabled(false);

    //Marcamos el calendario del dialogo
    sombrearCalendario();

}

void DialogSalidaArticulo::sombrearCalendario()
{
    //Establecemos el fondo
    fondoCalendar.setBackground(Qt::cyan);

    //Limpiar el calendarWidget
    ui->deFecha->calendarWidget()->setDateTextFormat(QDate(),fondoCalendar);

    //Ejecutamos la consulta para saber los dias que marcar en el calendario
    querySalidas->exec("SELECT DISTINCT fecha FROM salidasarticulos");

    while(querySalidas->next())
        ui->deFecha->calendarWidget()->setDateTextFormat(querySalidas->value(0).toDate(),fondoCalendar);
}

DialogSalidaArticulo::~DialogSalidaArticulo()
{
    delete ui;
}

void DialogSalidaArticulo::on_pbCancelar_clicked()
{
    this->close();
}

void DialogSalidaArticulo::on_pbGuardar_clicked()
{
    QSqlQuery actualizarAlmacen, insertarSalida;
    QSqlDatabase db = QSqlDatabase::database();

    //Iniciamos la transaccion
    db.transaction();

    actualizarAlmacen.prepare("UPDATE `articulos` SET `cantidad` = `cantidad` - '"+ui->sbCantidad->text()+"' WHERE `codigoean` = '"+codigoEAN+"' ");
    insertarSalida.prepare("INSERT INTO salidasarticulos (`fecha`, `articulo`,`cantidad`) VALUES ('"+ui->deFecha->date().toString("yyyy/MM/dd")+"', '"+codigoEAN+"', '"+ui->sbCantidad->text()+"')");

    if(actualizarAlmacen.exec() && insertarSalida.exec())
    {
        db.commit();

        QSqlQuery *queryUsuario, *query;

        queryUsuario = new QSqlQuery;
        query = new QSqlQuery;

        queryUsuario->exec("SELECT dni FROM usuarios WHERE nombreusuario = '"+usuarioActivo+"' ");
        queryUsuario->first();

        query->exec("INSERT INTO `actividad` (`id_actividad`,`fechamov`, `articulo`, `usuario`, `tipomovimiento`, `cantidad`) VALUES (NULL, NOW(), '"+ui->leCodEAN->text()+"', '"+queryUsuario->value(0).toString()+"', 'Eliminar', '"+ui->sbCantidad->text()+"')");

        mpArticulos->refrescar(consultaModelArt);
        mpSalidas->refrescar(consultaModelSal);
        pwsa->marcarCalendario();
        QMessageBox::information(this,tr("Información"),tr("Salida registrada correctamente"),tr("Aceptar"));
        this->close();

    }else{

        db.rollback();
        QMessageBox::critical(this,tr("Error"),tr("Ha habido un error, compruebe los campos"),tr("Aceptar"));
    }

}


void DialogSalidaArticulo::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}
