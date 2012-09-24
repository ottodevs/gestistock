#include "dialogmodificararticulo.h"
#include "ui_dialogmodificararticulo.h"


DialogModificarArticulo::DialogModificarArticulo(QString user, QString codEan, QString consulta, QSqlQueryArticulos *mp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogModificarArticulo)
{
    ui->setupUi(this);

    //Titulo de la ventana
    this->setWindowTitle(tr("Modificar Artículo"));
    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logoSolo.png"));
    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    this->setModal(true);

    //Guardamos la direccion del model para poder actualizar el tableview
    model = mp;

    consultaAct = consulta;

    usuarioActivo = user;
    fotoCargada = false;

    imagenArticulo = new QPixmap;
    actImagen = new QSqlQuery;

    //Ahora vamos a buscar el articulo con la clave primaria codEan, para sacarlo para poder modificarlo
    consult = new QSqlQuery;

    consult->exec("SELECT nombretipo FROM tipoproducto");

    //Rellenamos comboBox
    while(consult->next())
        ui->cbTipoProducto->addItem(consult->value(0).toString());

    //Limpiamos
    consult->clear();

    //Buscamos el articulo, con todas sus caracteri­sticas
    consult->exec("SELECT codigoean, descripcion, iva, tipoproducto, comentario,stockminimo,stockoptimo,imagen FROM articulos WHERE codigoean = '"+codEan+"' ");

    if(consult->first())
    {
            ui->leCodEAN->setText(consult->value(0).toString());
            ui->leDescripcion->setText(consult->value(1).toString());
            ui->leIVA->setText(consult->value(2).toString());
            //Establecemos el combo con el texto de la consulta
            indiceCombo = ui->cbTipoProducto->findText(consult->value(3).toString());
            ui->cbTipoProducto->setCurrentIndex(indiceCombo);
            ui->teComentario->setText(consult->value(4).toString());
            ui->sbMinimo->setValue(consult->value(5).toFloat());
            ui->sbOptimo->setValue(consult->value(6).toFloat());


            //Si tenemos una imagen almacenada, entonces la cargamos en el frame
            if(!consult->value(7).isNull())
            {
                    QByteArray ba1 = consult->value(7).toByteArray();
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


    //Desactivamos los campos
    ui->leCodEAN->setEnabled(false);



    ui->leIVA->setValidator(new QIntValidator(0,99,this));
}




void DialogModificarArticulo::on_pbCancelar_clicked()
{
    //Cerramos la ventana
    this->close();
}


void DialogModificarArticulo::on_pbAceptar_clicked()
{

    //Si se modifica la imagen, y algun otro campo o no...
    if(ui->leDescripcion->isModified() ||  ui->leIVA->isModified() || ui->sbMinimo->value() != consult->value(5).toInt() || ui->sbOptimo->value() != consult->value(6).toInt() || ui->cbTipoProducto->currentIndex() != indiceCombo || ui->teComentario->document()->isModified() || fotoCargada)
    {
        //El campo de iva no puede estar en blanco
        if(!ui->leIVA->text().simplified().isEmpty() && !ui->leDescripcion->text().simplified().isEmpty())
        {

            //ui->teComentario->toPlainText().simplified().isEmpty()

            //Limpiamos la consulta
            consult->clear();

            //Si la foto ha sido cargada...
            if(fotoCargada)
            {
                //Para recoger la imagen del Qlabel
                QByteArray ba;
                QBuffer buffer(&ba);
                buffer.open(QIODevice::ReadWrite);
                ui->lbImagen->pixmap()->save(&buffer,"JPG");


                consult->prepare("UPDATE articulos SET descripcion = :descripcion,iva = :iva, tipoproducto = :tipoproducto, comentario = :comentario, stockminimo = :stockminimo, stockoptimo = :stockoptimo, imagen = :imagen WHERE codigoean = '"+ui->leCodEAN->text()+"'");

                consult->bindValue(":descripcion",ui->leDescripcion->text());
                consult->bindValue(":iva",ui->leIVA->text());
                consult->bindValue(":tipoproducto",ui->cbTipoProducto->currentText());
                consult->bindValue(":comentario",ui->teComentario->toPlainText());
                consult->bindValue(":stockminimo",ui->sbMinimo->value());
                consult->bindValue(":stockoptimo",ui->sbOptimo->value());
                consult->bindValue(":imagen",ba);

            }else{

                consult->prepare("UPDATE articulos SET descripcion = :descripcion,iva = :iva, tipoproducto = :tipoproducto, comentario = :comentario,stockminimo = :stockminimo, stockoptimo = :stockoptimo WHERE codigoean = '"+ui->leCodEAN->text()+"'");

                consult->bindValue(":descripcion",ui->leDescripcion->text());
                consult->bindValue(":iva",ui->leIVA->text());
                consult->bindValue(":tipoproducto",ui->cbTipoProducto->currentText());
                consult->bindValue(":comentario",ui->teComentario->toPlainText());
                consult->bindValue(":stockminimo",ui->sbMinimo->value());
                consult->bindValue(":stockoptimo",ui->sbOptimo->value());
            }

            if(consult->exec()){

                QMessageBox::information(this,tr("Información"),tr("Artículo modificado correctamente"),tr("Aceptar"));
                //Refrescamos el modelo
                model->refrescar(consultaAct);
                this->close();

            }else
                QMessageBox::critical(this,tr("Error"),tr("Ha habido un error en la modificación"),tr("Aceptar"));

        }else
            QMessageBox::critical(this,tr("Error"),tr("Hay campos incompletos"),tr("Aceptar"));

    }else
        QMessageBox::information(this,tr("Información"),tr("No ha modificado ningún campo"),tr("Aceptar"));

}


void DialogModificarArticulo::on_pbCambiarImagen_clicked()
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


void DialogModificarArticulo::on_pbCamera_clicked()
{
        wb = new DialogWebCam(ui->lbImagen,&fotoCargada);

        if(wb->disponible())
            wb->show();
}

void DialogModificarArticulo::changeEvent(QEvent* event)
{
    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}

void DialogModificarArticulo::on_teComentario_textChanged()
{
    if(ui->teComentario->toPlainText().length() > 250)
        ui->teComentario->textCursor().deletePreviousChar();
}

void DialogModificarArticulo::on_pbEliminar_clicked()
{
    QSqlQuery query, queryCantidad;
    QMessageBox msgBox(this);

    msgBox.setWindowTitle(tr("Eliminar"));
    msgBox.setText(tr("Eliminar artículo                             "));
    msgBox.setInformativeText(tr("¿Está seguro de que desea eliminar el artículo?"));
    msgBox.setIcon(QMessageBox::Question);
    msgBox.addButton(tr("Si"),QMessageBox::AcceptRole);

    //Guardamos el boton en una variable para despues hacerlo por defecto
    QPushButton *pb = msgBox.addButton(tr("No"),QMessageBox::RejectRole);

    //Por defecto el boton que saldra sombreado
    msgBox.setDefaultButton(pb);

    queryCantidad.exec("SELECT cantidad FROM articulos WHERE codigoean = '"+ui->leCodEAN->text()+"' ");
    queryCantidad.first();

    //Si la respuesta es si...
    if(!msgBox.exec())
    {
        query.prepare("DELETE FROM articulos WHERE articulos.codigoean =  '"+ui->leCodEAN->text()+"' ");

        if(queryCantidad.value(0).toInt() == 0)
        {
            if(query.exec())
            {
                model->refrescar(consultaAct);
                QMessageBox::information(this,tr("Información"),tr("El artículo ha sido eliminado"),tr("Aceptar"));
                this->close();
            }else
                QMessageBox::critical(this,tr("Error"),tr("No se ha podido eliminar el artículo, compruebe su actividad"),tr("Aceptar"));

        }else
            QMessageBox::critical(this,tr("Error"),tr("No se ha podido eliminar el artículo, compruebe su actividad"),tr("Aceptar"));
    }

}


DialogModificarArticulo::~DialogModificarArticulo()
{
    delete ui;
}
