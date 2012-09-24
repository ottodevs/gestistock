#include "dialognuevoarticuloalmacen.h"
#include "ui_dialognuevoarticuloalmacen.h"

DialogNuevoArticuloAlmacen::DialogNuevoArticuloAlmacen(QString usuarioActivo, QWidget *parent, QSqlQueryArticulos *mp, QString consultaAct, QLCDNumber *lcd, QString codEAN) :
    QDialog(parent),
    ui(new Ui::DialogNuevoArticuloAlmacen)
{
    ui->setupUi(this);

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));
    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    //Titulo de la ventana
    this->setWindowTitle("Nuevo Articulo");
    //Hacemos el dialogo modal
    this->setModal(true);

    imagenArticulo = new QPixmap;
    insertarArticulo = new QSqlQuery;

    codigoEAN = codEAN;
    mpArticulos = mp;
    consultaActual = consultaAct;
    userActivo = usuarioActivo;
    plcd = lcd;

    //Inicialmente al crear el articulo no tendrá foto personalizada, tendra la por defecto
    fotoCargada = false;


    //Si ha recibido el CodEAN...
    if(codigoEAN != "")
    {
        ui->leCodEAN->setText(codigoEAN);
        ui->leCodEAN->setEnabled(false);
    }


    //Imagen por defecto
    QString im = ":/imagenes/noimagen.png";
    imagenArticulo->load(im);
    QPixmap imagenAjustada = imagenArticulo->scaled(ui->lbImagen->size());
    ui->lbImagen->setPixmap(imagenAjustada);
    //Fin imagen por defecto


    //Rellenamos comboBox
    this->iniciaComboTipos();


    ui->leIVA->setValidator(new QIntValidator(0,99,this));
    ui->leIVA->setText("0");
}

void DialogNuevoArticuloAlmacen::iniciaComboTipos()
{
    QStringList tipos;
    QSqlQuery consultaTipos;

    consultaTipos.exec("select nombretipo from tipoproducto");

    while(consultaTipos.next())
        tipos.append(consultaTipos.value(0).toString());


    ui->cbTipoProducto->addItems(tipos);
}


void DialogNuevoArticuloAlmacen::on_pbExaminar_clicked()
{
   rutaImagen = QFileDialog::getOpenFileName(this,tr("Cargar Imagen"),"",tr("Imagen(*.jpg *.bmp *.png *.jpge)"));

   if(rutaImagen != "")
   {
       imagenArticulo->load(rutaImagen);
       QPixmap imagenAjustada = imagenArticulo->scaled(ui->lbImagen->size());
       ui->lbImagen->clear();
       ui->lbImagen->setPixmap(imagenAjustada);

       fotoCargada = true;
   }
}


void DialogNuevoArticuloAlmacen::on_pbCamara_clicked()
{
    wb = new DialogWebCam(ui->lbImagen,&fotoCargada);
    if(wb->disponible())
        wb->show();
}


void DialogNuevoArticuloAlmacen::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}

void DialogNuevoArticuloAlmacen::on_pbCancelar_clicked()
{
    this->close();
}

void DialogNuevoArticuloAlmacen::on_pbGuardar_clicked()
{
    //Si la foto ha sido cargada...
    if(fotoCargada)
    {
        //Para recoger la imagen del Qlabel
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::ReadWrite);
        ui->lbImagen->pixmap()->save(&buffer,"JPG");

        insertarArticulo->prepare("INSERT INTO articulos (codigoean,cantidad,descripcion,iva,tipoproducto,comentario,stockminimo,stockoptimo,imagen) VALUES(:codigoean, :cantidad, :descripcion, :iva, :tipoproducto,:comentario,:stockminimo,:stockoptimo,:imagen)");

        insertarArticulo->bindValue(":codigoean",ui->leCodEAN->text());
        insertarArticulo->bindValue(":cantidad",0);
        insertarArticulo->bindValue(":descripcion",ui->leDescripcion->text());
        insertarArticulo->bindValue(":iva",ui->leIVA->text());
        insertarArticulo->bindValue(":tipoproducto",ui->cbTipoProducto->currentText());
        insertarArticulo->bindValue(":comentario",ui->teComentario->toPlainText());
        insertarArticulo->bindValue(":stockminimo",ui->sbMinimo->value());
        insertarArticulo->bindValue(":stockoptimo",ui->sbOptimo->value());
        insertarArticulo->bindValue(":imagen",ba);

    }else{

        insertarArticulo->prepare("INSERT INTO articulos (codigoean,cantidad,descripcion,iva,tipoproducto,comentario,stockminimo,stockoptimo) VALUES(:codigoean, :cantidad, :descripcion, :iva, :tipoproducto, :comentario, :stockminimo, :stockoptimo)");

        insertarArticulo->bindValue(":codigoean",ui->leCodEAN->text());
        insertarArticulo->bindValue(":cantidad",0);
        insertarArticulo->bindValue(":descripcion",ui->leDescripcion->text());
        insertarArticulo->bindValue(":iva",ui->leIVA->text());
        insertarArticulo->bindValue(":tipoproducto",ui->cbTipoProducto->currentText());
        insertarArticulo->bindValue(":comentario",ui->teComentario->toPlainText());
        insertarArticulo->bindValue(":stockminimo",ui->sbMinimo->value());
        insertarArticulo->bindValue(":stockoptimo",ui->sbOptimo->value());
    }


    if(insertarArticulo->exec())
    {
        mpArticulos->refrescar(consultaActual);
        plcd->display(mpArticulos->rowCount());
        QMessageBox::information(this,tr("Información"),tr("Artículo insertado correctamente"),tr("Aceptar"));
        this->close();

    }else
        QMessageBox::critical(this,tr("Error"),tr("Revise los campos"),tr("Aceptar"));

}

DialogNuevoArticuloAlmacen::~DialogNuevoArticuloAlmacen()
{
    delete ui;
}


void DialogNuevoArticuloAlmacen::on_teComentario_textChanged()
{
    if(ui->teComentario->toPlainText().length() > 250)
        ui->teComentario->textCursor().deletePreviousChar();
}
