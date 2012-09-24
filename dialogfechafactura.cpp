#include "dialogfechafactura.h"
#include "ui_dialogfechafactura.h"

DialogFechaFactura::DialogFechaFactura(QString usuario, QString local, QSqlQueryArticulos *mpArt, QString consultaArt, QSqlQueryCompras *mpCompras, QString consulta, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFechaFactura)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Fecha de Compra"));
    this->setWindowIcon(QIcon(":/imagenes/password.png"));
    this->setModal(true);
    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);



    mpArticulos = mpArt;
    consultaArticulos = consultaArt;
    mp = mpCompras;
    locale = local;
    consultaCompras = consulta;
    usuarioActivo = usuario;

    ui->deFecha->setDate(QDate::currentDate());
    ui->deFecha->setDisplayFormat("dddd, dd 'de' MMMM 'de' yyyy");

    actualizarStatus(locale);
    marcarCalendario();
}


void DialogFechaFactura::actualizarStatus(QString idioma)
{
    QLocale newlocale;

    if(idioma == "es")
        newlocale = QLocale::Spanish;
    else
        newlocale = QLocale::English;

    ui->deFecha->calendarWidget()->setLocale(newlocale);
    ui->deFecha->setLocale(newlocale);
}



void DialogFechaFactura::changeEvent(QEvent* event)
{
    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
        {
            actualizarStatus(locale);
            ui->retranslateUi(this);
        }
        else if(event->type() == QEvent::LocaleChange)
            actualizarStatus(locale);

    }

    QWidget::changeEvent(event);
}



void DialogFechaFactura::on_pbAceptar_clicked()
{

    QString nombreFich = "";
    QSqlQuery query, queryUsuarios,queryActualizar, comprobarExistencia;

    //nombreFich = QFileDialog::getOpenFileName(this,"Abrir Documento",QDir::currentPath(),".asc(*.asc)");
    nombreFich = QFileDialog::getOpenFileName(this,tr("Abrir Factura"),tr(""),tr("Fichero(*.asc)"));

    QFile file(nombreFich);


    if(nombreFich != "")
    {
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
                QMessageBox::critical(this,tr("Error"),tr("No se ha podido abrir el fichero"),tr("Aceptar"));
        else{

            //Para leer del fichero
            QTextStream stream(&file);
            QSqlQuery insertarArtprov;
            QSqlQuery insertarArticulo;
            QSqlQuery comprobarArticulo;
            QSqlQuery comprobarArtprov;
            QSqlQuery insertarCompra;
            QSqlQuery comprobarCompra;
            QSqlQuery actualizarCompra;
            QSqlQuery comprobarProveedor;
            QString proveedor;
            QString codEAN;
            QString cantidad;
            QString descripcion;
            QString precio;
            QString iva;

            QString linea;
            int tam = 0;

            // Lees todo y lo guardas en un QString
            //QString myString = stream.readAll();

            //Leemos la primera linea
            linea = stream.readLine();


            //Comprobamos si existe el proveedor
            proveedor = linea.mid(0,14);
            comprobarProveedor.exec("SELECT * FROM proveedores WHERE proveedores.cif = '"+proveedor+"' ");
            comprobarProveedor.first();

            if(!comprobarProveedor.isValid())
            {
                QMessageBox::warning(this,"Aviso","El proveedor no existe","Aceptar");

            }else{

                //Mientras no sea linea nula
                while(!linea.isNull())
                {
                    //Determinamos el tamanio de la linea
                    tam = linea.size();
                    //Recortamos
                    proveedor = linea.mid(0,14);
                    codEAN = linea.mid(14,13);
                    //Recortamos por el otro extremo la cadena
                    iva = linea.mid(tam-5,2);
                    precio = linea.mid(tam-15,4);
                    cantidad = linea.mid(tam-26,4);

                    //Resto para la descripcion
                    int nCar = (tam-26) - 27;
                    descripcion = linea.mid(27,nCar);

                    float precioArticulo = precio.toInt();
                    precioArticulo = precioArticulo/1000;

                    comprobarArticulo.exec("SELECT articulos.codigoean FROM articulos WHERE articulos.codigoean = '"+codEAN+"' ");
                    comprobarArtprov.exec("SELECT artprov.codigoean FROM artprov WHERE artprov.codigoean = '"+codEAN+"' and artprov.proveedor = '"+proveedor+"' ");
                    comprobarCompra.exec("SELECT articulo FROM compraproductos WHERE proveedor = '"+proveedor+"' AND fecha = '"+ui->deFecha->date().toString("yyyy/MM/dd")+"' AND articulo = '"+codEAN+"' ");

                    //Situamos las consultas
                    comprobarArticulo.first();
                    comprobarArtprov.first();
                    comprobarCompra.first();

                    if(!comprobarArticulo.isValid())
                        insertarArticulo.exec("INSERT INTO `articulos` (codigoean, cantidad, descripcion, iva) VALUES ('"+codEAN+"','"+cantidad+"','"+descripcion+"', '"+iva+"')");

                    if(!comprobarArtprov.isValid())
                        insertarArtprov.exec("INSERT INTO `artprov` (proveedor,codigoean,precio) VALUES('"+proveedor+"','"+codEAN+"','"+QString::number(precioArticulo)+"')");
                    else
                        insertarArtprov.exec("UPDATE  `artprov` SET  `precio` =  '"+QString::number(precioArticulo)+"' WHERE `proveedor` = '"+proveedor+"' AND `codigoean` =  '"+codEAN+"' ");


                    queryUsuarios.exec("SELECT usuarios.dni FROM usuarios WHERE usuarios.nombreusuario = '"+usuarioActivo+"' ");
                    queryUsuarios.first();


                    comprobarExistencia.exec("SELECT articulo,cantidad FROM compraproductos WHERE proveedor = '"+proveedor+"' AND fecha = '"+ui->deFecha->date().toString("yyyy/MM/dd")+"' AND articulo = '"+codEAN+"' ");
                    comprobarExistencia.first();



                    //Si no devuelve nada...
                    if(!comprobarCompra.isValid())
                    {
                        insertarCompra.exec("INSERT INTO `compraproductos` (proveedor,fecha,articulo,precio,cantidad,iva) VALUES('"+proveedor+"', '"+ui->deFecha->date().toString("yyyy/MM/dd")+"','"+codEAN+"', '"+QString::number(precioArticulo)+"', '"+cantidad+"', '"+iva+"')");
                        query.exec("INSERT INTO `actividad` (`fechamov`, `articulo`, `usuario`, `tipomovimiento`, `cantidad`) VALUES (NOW(), '"+codEAN+"', '"+queryUsuarios.value(0).toString()+"', 'Insertar', '"+cantidad+"')");
                        qDebug() << queryActualizar.exec("UPDATE `articulos` SET `cantidad` = `cantidad` + '"+cantidad+"', `iva` = '"+iva+"' WHERE `codigoean` = '"+codEAN+"' ");

                    }else{

                        actualizarCompra.exec("UPDATE `compraproductos` SET precio = '"+QString::number(precioArticulo)+"', cantidad = '"+cantidad+"', iva = '"+iva+"' WHERE proveedor = '"+proveedor+"' and articulo = '"+codEAN+"' and fecha = '"+ui->deFecha->date().toString("yyyy/MM/dd")+"' ");
                        query.exec("INSERT INTO `actividad` (`fechamov`, `articulo`, `usuario`, `tipomovimiento`, `cantidad`) VALUES (NOW(), '"+codEAN+"', '"+queryUsuarios.value(0).toString()+"', 'Insertar', '"+cantidad+"')");
                        qDebug() << queryActualizar.exec("UPDATE `articulos` SET `cantidad` = `cantidad` - '"+comprobarExistencia.value(1).toString()+"' + '"+cantidad+"', `iva` = '"+iva+"' WHERE `codigoean` = '"+codEAN+"' ");

                    }


                    //Procesamos
                    process_line(linea);
                    linea = stream.readLine();
                }

                QMessageBox::information(this,tr("Información"),tr("La factura ha sido cargada correctamente"),tr("Aceptar"));
                //Cerramos el fichero
                file.close();
            }
        }
    }


    //Refrescamos el model
    mpArticulos->refrescar(consultaArticulos);

    //Refrescamos el model
    mp->refrescar(consultaCompras);


    //Volvemos a marcar el calendario
    marcarCalendario();

    //Cerramos la pantalla
    this->close();
}

void DialogFechaFactura::marcarCalendario()
{
    QSqlQuery marcarCal;

    //Establecemos el fondo
    fondoCalendar.setBackground(Qt::cyan);

    //Limpiar el calendarWidget
    ui->deFecha->calendarWidget()->setDateTextFormat(QDate(),fondoCalendar);

    //Ejecutamos la consulta para saber los dias que marcar en el calendario
    marcarCal.exec("SELECT DISTINCT fecha FROM compraproductos");

    while(marcarCal.next())
        ui->deFecha->calendarWidget()->setDateTextFormat(marcarCal.value(0).toDate(),fondoCalendar);
}


DialogFechaFactura::~DialogFechaFactura()
{
    delete ui;
}
