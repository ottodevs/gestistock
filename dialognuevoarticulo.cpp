#include "dialognuevoarticulo.h"
#include "ui_dialognuevoarticulo.h"


DialogNuevoArticulo::DialogNuevoArticulo(QString usuarioActivo, QDate date, QWidget *parent, QSqlQueryCompras *mp, QString consultaAct, QString codEAN) :
    QDialog(parent),
    ui(new Ui::DialogNuevoArticulo)
{
    ui->setupUi(this);


    //Titulo de la ventana
    this->setWindowTitle("Nuevo Artículo");
    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));
    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    //Hacemos el dialogo modal
    this->setModal(true);

    imagenArticulo = new QPixmap;
    insertar = new QSqlQuery;
    consulta = new QSqlQuery;

    codigoEAN = codEAN;
    mpCompras = mp;
    consultaActiva = consultaAct;
    userActivo = usuarioActivo;
    fecha = date;

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


    //Rellenamos comboBoxs
    this->iniciaComboProveedores();
    this->iniciaComboTipos();


    ui->leIVA->setValidator(new QIntValidator(0,99,this));
    ui->lePrecio->setText("0");

    ui->lePrecio->setValidator(new QDoubleValidator(0,99999,3,this));
    ui->lePrecio->setText("0");
}



void DialogNuevoArticulo::iniciaComboProveedores()
{
    QSqlQuery *cnsltTiendas;
    int cont = 1;
    RelProv::iterator ite = rprov.begin();

    cnsltTiendas = new QSqlQuery;

    cnsltTiendas->exec("SELECT cif,nombreproveedor FROM proveedores");

    //Insertamos un item vacio para que aparezca en blanco al principio...
    ui->cbTienda->addItem("");

    while(cnsltTiendas->next())
    {   //Metemos los datos en un map
        rprov.insert(ite,make_pair(cnsltTiendas->value(1).toString(),cnsltTiendas->value(0).toString()));

        ui->cbTienda->addItem(cnsltTiendas->value(0).toString());
        //Para colocarle el nombre al item...
        ui->cbTienda->setItemText(cont,cnsltTiendas->value(1).toString());
        cont++;
    }

    /* Comprobar el map
    for(ite = rprov.begin(); ite != rprov.end(); ite++)
    {
        qDebug() << (*ite).first << " " << (*ite).second;
    }*/

}

void DialogNuevoArticulo::iniciaComboTipos()
{
    QStringList tipos;
    QSqlQuery consultaTipos;

    consultaTipos.exec("select nombretipo from tipoproducto");

    while(consultaTipos.next())
        tipos.append(consultaTipos.value(0).toString());


    ui->cbTipoProducto->addItems(tipos);
    //Fin relleno del comboBox
}



void DialogNuevoArticulo::on_pbGuardar_clicked()
{
    QSqlQuery *insertarArtProv;
    QSqlQuery *insertarCompra;
    QSqlQuery *query, *queryUsuario;

    insertarArtProv = new QSqlQuery; 
    insertarCompra = new QSqlQuery;
    query = new QSqlQuery;
    queryUsuario = new QSqlQuery;

    //Si se han modificado los line edit... y el combo box...
    if(!ui->leCodEAN->text().simplified().isEmpty() && !ui->leIVA->text().simplified().isEmpty() && !ui->leDescripcion->text().simplified().isEmpty() && !ui->lePrecio->text().simplified().isEmpty() && ui->cbTienda->currentText() != "" && ui->cbTipoProducto->currentText() != "")
    {
            //Iterador al principio del map
            RelProv::iterator it = rprov.begin();
            bool encontrado = false;
            QString codTienda;

            //A partir del nombre de la tienda devolvemos su codigo
            while(it != rprov.end() && encontrado == false)
            {
                if(ui->cbTienda->currentText() == (*it).first)
                {
                    encontrado = true;
                    codTienda = (*it).second;

                }

                it++;
            }


            //Si tenemos un cif de tienda...
            if(codTienda != "")
            {
                //Guardamos la base de datos actual
                QSqlDatabase db = QSqlDatabase::database();

                //Iniciamos la transaccion
                db.transaction();


                //Si la foto ha sido cargada...
                if(fotoCargada)
                {
                    //Para recoger la imagen del Qlabel
                    QByteArray ba;
                    QBuffer buffer(&ba);
                    buffer.open(QIODevice::ReadWrite);
                    ui->lbImagen->pixmap()->save(&buffer,"JPG");

                    insertar->prepare("INSERT INTO articulos (codigoean,cantidad,descripcion,iva,tipoproducto,comentario,stockminimo,stockoptimo,imagen) VALUES(:codigoean, :cantidad, :descripcion, :iva, :tipoproducto,:comentario,:stockminimo,:stockoptimo,:imagen)");

                    insertar->bindValue(":codigoean",ui->leCodEAN->text());
                    insertar->bindValue(":cantidad",ui->sbCantidad->value());
                    insertar->bindValue(":descripcion",ui->leDescripcion->text());
                    insertar->bindValue(":iva",ui->leIVA->text());
                    insertar->bindValue(":tipoproducto",ui->cbTipoProducto->currentText());
                    insertar->bindValue(":comentario",ui->teComentario->toPlainText());
                    insertar->bindValue(":stockminimo",ui->sbMinimo->value());
                    insertar->bindValue(":stockoptimo",ui->sbOptimo->value());
                    insertar->bindValue(":imagen",ba);

                }else{

                    insertar->prepare("INSERT INTO articulos (codigoean,cantidad,descripcion,iva,tipoproducto,comentario,stockminimo,stockoptimo) VALUES(:codigoean, :cantidad, :descripcion, :iva, :tipoproducto, :comentario, :stockminimo, :stockoptimo)");

                    insertar->bindValue(":codigoean",ui->leCodEAN->text());
                    insertar->bindValue(":cantidad",ui->sbCantidad->value());
                    insertar->bindValue(":descripcion",ui->leDescripcion->text());
                    insertar->bindValue(":iva",ui->leIVA->text());
                    insertar->bindValue(":tipoproducto",ui->cbTipoProducto->currentText());
                    insertar->bindValue(":comentario",ui->teComentario->toPlainText());
                    insertar->bindValue(":stockminimo",ui->sbMinimo->value());
                    insertar->bindValue(":stockoptimo",ui->sbOptimo->value());
                }

                insertarArtProv->prepare("INSERT INTO artprov (`proveedor`, `codigoean`, `precio`) VALUES ('"+codTienda+"', '"+ui->leCodEAN->text()+"','"+ui->lePrecio->text()+"')");
                insertarCompra->prepare("INSERT INTO compraproductos (`proveedor`, `fecha`, `articulo`, `precio`, `cantidad`, `iva`) VALUES('"+codTienda+"', '"+fecha.toString("yyyy/MM/dd")+"', '"+ui->leCodEAN->text()+"', '"+ui->lePrecio->text()+"', '"+ui->sbCantidad->text()+"', '"+ui->leIVA->text()+"' )");


                //Si no hay ningun problema, confirmamos la transaccion, de lo contrario la anulamos
                if(insertar->exec() && insertarArtProv->exec() && insertarCompra->exec())
                {
                    db.commit();
                    QMessageBox::information(this,tr("Información"),tr("Artículo insertado correctamente"),tr("Aceptar"));

                    queryUsuario->exec("SELECT dni FROM usuarios WHERE nombreusuario = '"+userActivo+"' ");
                    queryUsuario->first();

                    query->exec("INSERT INTO `actividad` (`id_actividad`,`fechamov`, `articulo`, `usuario`, `tipomovimiento`, `cantidad`) VALUES (NULL, NOW(), '"+ui->leCodEAN->text()+"', '"+queryUsuario->value(0).toString()+"', 'Insertar', '"+ui->sbCantidad->text()+"')");

                    mpCompras->refrescar(consultaActiva);

                    //Cerramos la ventana
                    this->close();

                }else{

                    db.rollback();
                    QMessageBox::critical(this,tr("Error"),tr("Ha habido un error en la inserción"),tr("Aceptar"));

                }

            }

    }else
        QMessageBox::critical(this,tr("Error"),tr("Hay campos incompletos"),tr("Aceptar"));

}




//Buscamos la imagen
void DialogNuevoArticulo::on_pbExaminar_clicked()
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


void DialogNuevoArticulo::on_pbCancelar_clicked()
{
        //Cerramos la ventana
        this->close();
}


void DialogNuevoArticulo::reject()
{
    this->close();
}


void DialogNuevoArticulo::on_pbCamara_clicked()
{
        wb = new DialogWebCam(ui->lbImagen,&fotoCargada);
        if(wb->disponible())
            wb->show();
}


//Si cerramos la ventana...
void DialogNuevoArticulo::closeEvent(QCloseEvent *ev)
{
    //Si el usuario ha cerrado la ventana...
    if(ev->isAccepted())
    {
        this->close();
    }

}

void DialogNuevoArticulo::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}

DialogNuevoArticulo::~DialogNuevoArticulo()
{
    delete ui;
}


void DialogNuevoArticulo::on_teComentario_textChanged()
{
    if(ui->teComentario->toPlainText().length() > 250)
        ui->teComentario->textCursor().deletePreviousChar();
}
