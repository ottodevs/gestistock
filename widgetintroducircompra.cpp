#include "widgetintroducircompra.h"
#include "ui_widgetintroducircompra.h"

WidgetIntroducirCompra::WidgetIntroducirCompra(QString *local, QString user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetIntroducirCompra)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Introducir Compra"));

    this->setWindowModality(Qt::WindowModal);

    this->setFocus();
    this->setFocusPolicy(Qt::StrongFocus);

    //Enganchamos el puntero a locale de la pantalla padre
    locale = local;

    usuarioActivo = user;

    consultArticulos = new QSqlQuery;
    consult = new QSqlQuery;
    consultAux = new QSqlQuery;
    mp = new QSqlQueryCompras;
    mpAlmacen = new QSqlQueryArticulos;

    inicializarTabCompras();
    inicializarTabAlmacen();

}

void WidgetIntroducirCompra::inicializarTabCompras()
{
    rellenarCombos();

    ui->deFecha->setDate(QDate::currentDate());
    ui->deFecha->setDisplayFormat("dddd, dd 'de' MMMM 'de' yyyy");

    this->actualizarStatus((*locale));


    //Sacamos la clava primaria del proveedor
    consult->exec("SELECT cif FROM proveedores WHERE nombreproveedor = '"+ui->cbProveedor->currentText()+"' ");
    consult->first();

    //Consulta activa actualmente
    consultaActiva = "select articulos.codigoean, articulos.descripcion, compraproductos.cantidad, compraproductos.precio from articulos,compraproductos WHERE articulos.codigoean = compraproductos.articulo AND compraproductos.proveedor = '"+consult->value(0).toString()+"' AND compraproductos.fecha = '"+ui->deFecha->date().toString("yyyy/MM/dd")+"'";
    //Consulta a modificar
    consulta = consultaActiva;

    mp->refrescar(consulta);

    ui->tableView->setModel(mp);

    header = ui->tableView->horizontalHeader();

    header->setSortIndicatorShown(false);

    //Conectamos el header al slot
    connect(header,SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), this, SLOT(refresh()));

    //item delegate
    ui->tableView->setItemDelegateForColumn(0, new Delegate(this));
    ui->tableView->setItemDelegateForColumn(1, new Delegate(this));
    ui->tableView->setItemDelegateForColumn(2, new Delegate(this));
    ui->tableView->setItemDelegateForColumn(3, new Delegate(this));
    ui->tableView->setItemDelegateForColumn(4, new Delegate(this));


    //Tamaño del QTableView
    ui->tableView->setFixedSize(740,320);

    //Colocamos los nombres en el table
    mp->setHeaderData(0,Qt::Horizontal,tr("CódigoEAN\n"));
    mp->setHeaderData(1,Qt::Horizontal,tr("Descripción\n"));
    mp->setHeaderData(2,Qt::Horizontal,tr("Cantidad\n"));
    mp->setHeaderData(3,Qt::Horizontal,tr("Precio\n"));

    //Damos a cada columna la anchura deseada
    ui->tableView->setColumnWidth(0,150);
    ui->tableView->setColumnWidth(1,450);
    ui->tableView->setColumnWidth(2,70);
    ui->tableView->setColumnWidth(3,50);

    //Para cuando se cliquea sobre un item se marque la fila completa
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

}

void WidgetIntroducirCompra::inicializarTabAlmacen()
{
    headerArt = ui->tvArticulosAlmacen->horizontalHeader();

    rellenarComboTipos();

    //Consulta activa actualmente
    consultaActivaArt = "select articulos.codigoean, articulos.descripcion, articulos.cantidad, articulos.iva from articulos, artprov WHERE articulos.codigoean = artprov.codigoean and artprov.proveedor = '"+cifProveedor+"' ";
    //Consulta a modificar
    consultaArt = consultaActivaArt;

    mpAlmacen->refrescar(consultaArt);

    ui->tvArticulosAlmacen->setModel(mpAlmacen);

    headerArt->setSortIndicatorShown(false);

    //Conectamos el header al slot
    connect(headerArt,SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), this, SLOT(refreshOrdenarArticulosAlmacen()));

    //item delegate
    ui->tvArticulosAlmacen->setItemDelegateForColumn(0, new DelegateArticulos(this));
    ui->tvArticulosAlmacen->setItemDelegateForColumn(1, new DelegateArticulos(this));
    ui->tvArticulosAlmacen->setItemDelegateForColumn(2, new DelegateArticulos(this));
    ui->tvArticulosAlmacen->setItemDelegateForColumn(3, new DelegateArticulos(this));
    ui->tvArticulosAlmacen->setItemDelegateForColumn(4, new DelegateArticulos(this));


    //Tamaño del QTableView
    ui->tvArticulosAlmacen->setFixedSize(740,320);

    //Colocamos los nombres en el table
    mpAlmacen->setHeaderData(0,Qt::Horizontal,tr("CódigoEAN\n"));
    mpAlmacen->setHeaderData(1,Qt::Horizontal,tr("Descripción\n"));
    mpAlmacen->setHeaderData(2,Qt::Horizontal,tr("Cantidad\n"));
    mpAlmacen->setHeaderData(3,Qt::Horizontal,tr("IVA\n"));

    //Damos a cada columna la anchura deseada
    ui->tvArticulosAlmacen->setColumnWidth(0,150);
    ui->tvArticulosAlmacen->setColumnWidth(1,450);
    ui->tvArticulosAlmacen->setColumnWidth(2,70);
    ui->tvArticulosAlmacen->setColumnWidth(3,50);

    //Para cuando se cliquea sobre un item se marque la fila completa
    ui->tvArticulosAlmacen->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvArticulosAlmacen->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->rbCodigoEANAlmacen->setChecked(true);
}

//Compras
void WidgetIntroducirCompra::on_tableView_clicked(const QModelIndex &index)
{
    //Con esto encontramos la clave primaria
    QString codigoEAN;
    QSqlQuery query;

    codigoEAN = index.sibling(index.row(),0).data().toString();

    query.exec("SELECT cif FROM proveedores WHERE nombreproveedor = '"+ui->cbProveedor->currentText()+"' ");
    query.first();


    dc = new DialogCompras(usuarioActivo,codigoEAN,query.value(0).toString(),ui->deFecha->date(),mpAlmacen,mp,consultaArt,consulta,this,this);
    dc->show();
}



void WidgetIntroducirCompra::on_deFecha_dateChanged(const QDate &date)
{
    QSqlQuery query;

    //Sacamos la clava primaria del proveedor
    query.exec("SELECT cif FROM proveedores WHERE nombreproveedor = '"+ui->cbProveedor->currentText()+"' ");
    query.first();

    //Consulta activa actualmente
    consultaActiva = "select articulos.codigoean, articulos.descripcion, compraproductos.cantidad, compraproductos.precio from articulos,compraproductos WHERE articulos.codigoean = compraproductos.articulo AND compraproductos.proveedor = '"+query.value(0).toString()+"' AND compraproductos.fecha = '"+date.toString("yyyy/MM/dd")+"'";
    //Consulta a modificar
    consulta = consultaActiva;

    mp->refrescar(consulta);

}

void WidgetIntroducirCompra::marcarCalendario()
{
    //Establecemos el fondo
    fondoCalendar.setBackground(Qt::cyan);

    //Limpiar el calendarWidget
    ui->deFecha->calendarWidget()->setDateTextFormat(QDate(),fondoCalendar);

    //Sacamos la clava primaria del proveedor
    consult->exec("SELECT cif FROM proveedores WHERE nombreproveedor = '"+ui->cbProveedor->currentText()+"'");
    consult->first();

    //Ejecutamos la consulta para saber los dias que marcar en el calendario
    consultAux->exec("SELECT DISTINCT fecha FROM compraproductos WHERE compraproductos.proveedor = '"+consult->value(0).toString()+"'");

    while(consultAux->next())
        ui->deFecha->calendarWidget()->setDateTextFormat(consultAux->value(0).toDate(),fondoCalendar);
}


void WidgetIntroducirCompra::on_cbProveedor_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    marcarCalendario();

    //Sacamos la clava primaria del proveedor
    consult->exec("SELECT cif FROM proveedores WHERE nombreproveedor = '"+arg1+"'");
    consult->first();

    //Sacamos la clava primaria del proveedor
    query.exec("SELECT cif FROM proveedores WHERE nombreproveedor = '"+arg1+"' ");
    query.first();

    cifProveedor = query.value(0).toString();

    //Consulta activa actualmente
    consultaActiva = "select articulos.codigoean, articulos.descripcion, compraproductos.cantidad, compraproductos.precio from articulos,compraproductos WHERE articulos.codigoean = compraproductos.articulo AND compraproductos.proveedor = '"+cifProveedor+"' AND compraproductos.fecha = '"+ui->deFecha->date().toString("yyyy/MM/dd")+"'";
    //Consulta a modificar
    consulta = consultaActiva;

    //Consulta activa actualmente
    consultaActivaArt = "select articulos.codigoean, articulos.descripcion, articulos.cantidad, articulos.iva from articulos, artprov WHERE articulos.codigoean = artprov.codigoean and artprov.proveedor = '"+cifProveedor+"'";
    //Consulta a modificar
    consultaArt = consultaActivaArt;

    mp->refrescar(consulta);
    mpAlmacen->refrescar(consultaArt);

    this->setFocus();
}


void WidgetIntroducirCompra::actualizarStatus(QString idioma)
{
    QLocale newlocale;

    if(idioma == "es")
        newlocale = QLocale::Spanish;
    else
        newlocale = QLocale::English;

    ui->deFecha->calendarWidget()->setLocale(newlocale);
    ui->deFecha->setLocale(newlocale);
}


void WidgetIntroducirCompra::changeEvent(QEvent* event)
{
    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
        {
            actualizarStatus((*locale));
            ui->retranslateUi(this);
        }
        else if(event->type() == QEvent::LocaleChange)
            actualizarStatus((*locale));

    }

    QWidget::changeEvent(event);
}



void WidgetIntroducirCompra::rellenarCombos()
{
    QStringList proveedores;
    QSqlQuery query;

    query.exec("SELECT nombreproveedor FROM proveedores");

    while(query.next())
        proveedores.append(query.value(0).toString());

    ui->cbProveedor->addItems(proveedores);
}


void WidgetIntroducirCompra::refresh()
{
    //"consulta" es la que modificaremos añadiendole el resto del string
    consulta = consultaActiva;

    //No dejamos ordenarlo por CodigoEAN
    if(header->sortIndicatorSection() == 0)
    {   
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consulta.append(" ORDER BY articulos.codigoean asc");
            mp->refrescar(consulta);

        }
        else
        {
            consulta.append(" ORDER BY articulos.codigoean desc");
            mp->refrescar(consulta);

        }
    }


    //Devuelve la seccion del header que hemos clickeado
    if(header->sortIndicatorSection() == 1)
    {
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consulta.append(" ORDER BY articulos.descripcion asc");
            mp->refrescar(consulta);

        }
        else
        {
            consulta.append(" ORDER BY articulos.descripcion desc");
            mp->refrescar(consulta);

        }
    }


    //Devuelve la seccion del header que hemos clickeado
    if(header->sortIndicatorSection() == 2)
    {
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consulta.append(" ORDER BY compraproductos.cantidad asc");
            mp->refrescar(consulta);

        }
        else
        {
            consulta.append(" ORDER BY compraproductos.cantidad desc");
            mp->refrescar(consulta);

        }
    }


    //Devuelve la seccion del header que hemos clickeado
    if(header->sortIndicatorSection() == 3)
    {
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consulta.append(" ORDER BY compraproductos.precio asc");
            mp->refrescar(consulta);

        }
        else
        {
            consulta.append(" ORDER BY compraproductos.precio desc");
            mp->refrescar(consulta);

        }
    }


    this->setFocus();
}


void WidgetIntroducirCompra::keyReleaseEvent(QKeyEvent *ke)
{
        QString EAN = "";

        if(ke->key() != 16777220)
        {
            //Vamos almacenando lo que se teclee...si no es un retorno de carro
            cad += ke->text();

            //Los rotamos
            if(cad.count() > 13)
                cad = cad.mid(1,13);

        }else{

            //if(cad.count() > 13)
                //cad = cad.mid((cad.count() - 13),(cad.count()- 1));

            //La parada es cuando se teclee retorno de carro y tenga 13 caracteres!
            if(ke->key() == 16777220 && cad.count() == 13)
            {
                EAN = cad;
                cad = "";

                QString invertEAN = "";

                //Invertimos la cadena
                for(int i = EAN.count() - 2; i >= 0; i--)
                {
                    //Invertimos caracter a caracter... OJO el ultimo que es el de control lo dejamos fuera!
                    invertEAN += EAN.at(i);
                }

                qDebug() << "Codigo invertido sin control: " << invertEAN;

                //Guardamos el digito de control
                QString DC = EAN.at(12);
                int DigitoControl = DC.toInt();

                qDebug() << "Digito de Control " << DigitoControl;

                // Cálculo del dígito de control EAN
                int Sum = 0;
                int SumaImpar = 0;
                int SumaPar = 0;


                //Realizamos los calculos
                for (int i = 0; i < invertEAN.count(); i++)
                {
                    //Si es impar...(Sumamos uno porque las cadenas empiezan en 0!)
                    if((i+1) % 2 != 0 )
                    {
                        QString cimpar;
                        cimpar = invertEAN.at(i);
                        SumaImpar += cimpar.toInt();

                    }else{
                        QString cpar;
                        cpar = invertEAN.at(i);
                        SumaPar += cpar.toInt();
                    }

                }

                //Calculamos la suma...
                Sum = (SumaImpar * 3) + SumaPar;


                int Res = (10 -(Sum % 10)) % 10;


                //Si es un codigo válido...
                if(Res == DigitoControl)
                {

                    qDebug() << "Codigo Válido" << EAN;

                    //Ignoramos la tecla
                    //ke->setAccepted(false);


                    //Comprobamos si el articulo lo tenemos ya en la base de datos
                    consultArticulos->exec("SELECT * FROM articulos WHERE codigoean = '"+EAN+"' ");

                    //Si no hay ningun arti­culo con ese CodigoEAN...
                    if(consultArticulos->size() < 1)
                    {
                        dna = new DialogNuevoArticulo(usuarioActivo,ui->deFecha->date(),this,mp,consulta,EAN);
                        dna->show();


                    //Si lo tenemos en la base de datos...
                    }else if(consultArticulos->size() > 0)
                    {
                        consult->clear();
                        consult->exec("SELECT cif FROM proveedores WHERE nombreproveedor = '"+ui->cbProveedor->currentText()+"' ");
                        consult->first();

                        dc = new DialogCompras(usuarioActivo,EAN,consult->value(0).toString(),ui->deFecha->date(),mpAlmacen,mp,consultaArt,consulta,this);
                        dc->show();

                    }else
                    {
                        qDebug() << "Error en consulta";

                    }

                }
                else
                {

                    qDebug() << "Esto no es un codigo";

                }


                qDebug() << "Digito resultado: " << Res;
                qDebug() << "Digito solución: " << DigitoControl;
            }


        }

}



void WidgetIntroducirCompra::on_pbCrearArticulo_clicked()
{
    dna = new DialogNuevoArticulo(usuarioActivo,ui->deFecha->date(),this,mp,consulta);
    dna->show();
}


/*
void WidgetIntroducirCompra::on_pbNuevaCompra_clicked()
{
    QString proveedor, QDate date, QSqlQueryCompras *modelCompras, QSqlQueryArticulos *modelArticulos, QString consultaArticulos, QString consultaCompras, WidgetIntroducirCompra *wic, QWidget *parent
    dc = new DialogCompras(consult->value(0).toString(),ui->deFecha->date(),mpAlmacen,mp,consultaArt,consulta,this,this);
    dc->show();
}
*/

void WidgetIntroducirCompra::on_pbFactura_clicked()
{


    dff = new DialogFechaFactura(usuarioActivo,(*locale),mpAlmacen,consultaArt,mp,consulta,this);
    dff->show();    //Declaramos un QString que almacenara el nombre que devuelva la funcion openFile()   

}




/************************************ALMACEN************************************/

void WidgetIntroducirCompra::rellenarComboTipos()
{
    QSqlQuery cn;
    QStringList tipos;

    cn.prepare("select nombretipo from tipoproducto");
    cn.exec();

    while(cn.next())
        tipos.append(cn.value(0).toString());

    ui->cbTipoProductoAlmacen->addItems(tipos);
}



void WidgetIntroducirCompra::on_pbBuscarAlmacen_clicked()
{
    if(ui->rbCodigoEANAlmacen->isChecked() == true)
    {
        consultaArt = "select articulos.codigoean, articulos.descripcion, articulos.cantidad, articulos.iva from articulos, artprov WHERE articulos.codigoean = artprov.codigoean and artprov.proveedor = '"+cifProveedor+"' and artprov.codigoean like '%"+ui->leBuscarAlmacen->text()+"%'";
        mpAlmacen->refrescar(consultaArt);
        consultaActivaArt = consultaArt;
        //Desactivamos para mostrar la consulta y que no aparezca el indicador
        headerArt->setSortIndicatorShown(false);
    }

    if(ui->rbDescripcionAlmacen->isChecked() == true)
    {
        consultaArt = "select articulos.codigoean, articulos.descripcion, articulos.cantidad, articulos.iva from articulos, artprov WHERE articulos.codigoean = artprov.codigoean and artprov.proveedor = '"+cifProveedor+"' and articulos.descripcion like '%"+ui->leBuscarAlmacen->text()+"%'";
        mpAlmacen->refrescar(consultaArt);
        consultaActivaArt = consultaArt;
        headerArt->setSortIndicatorShown(false);
    }

    if(ui->rbTipoProductoAlmacen->isChecked() == true)
    {
        consultaArt = "select articulos.codigoean, articulos.descripcion, articulos.cantidad, articulos.iva from articulos, artprov WHERE articulos.codigoean = artprov.codigoean and artprov.proveedor = '"+cifProveedor+"' and articulos.tipoproducto = '"+ui->cbTipoProductoAlmacen->currentText()+"'";
        mpAlmacen->refrescar(consultaArt);
        consultaActivaArt = consultaArt;
        headerArt->setSortIndicatorShown(false);
    }
}

void WidgetIntroducirCompra::on_tvArticulosAlmacen_clicked(const QModelIndex &index)
{
    //Con esto encontramos la clave primaria
    QString codigoEAN;
    QSqlQuery query;

    codigoEAN = index.sibling(index.row(),0).data().toString();

    query.exec("SELECT cif FROM proveedores WHERE nombreproveedor = '"+ui->cbProveedor->currentText()+"' ");
    query.first();

    dc = new DialogCompras(usuarioActivo,codigoEAN,query.value(0).toString(),ui->deFecha->date(),mpAlmacen,mp,consultaArt,consulta,this,this);
    dc->show();
}

void WidgetIntroducirCompra::refreshOrdenarArticulosAlmacen()
{
    consultaArt = consultaActivaArt;

    //No dejamos ordenarlo por CodigoEAN
    if(headerArt->sortIndicatorSection() == 0)
    {
        headerArt->setSortIndicatorShown(false);

        //Vemos que indicador está puesto
        if(headerArt->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaArt.append(" ORDER BY articulo asc");
            mpAlmacen->refrescar(consultaArt);
        }
        else
        {
            consultaArt.append(" ORDER BY articulo desc");
            mpAlmacen->refrescar(consultaArt);
        }
    }


    //Devuelve la seccion del header que hemos clickeado
    if(headerArt->sortIndicatorSection() == 1)
    {
        headerArt->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(headerArt->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaArt.append(" ORDER BY descripcion asc");
            mpAlmacen->refrescar(consultaArt);
        }
        else
        {
            consultaArt.append(" ORDER BY descripcion desc");
            mpAlmacen->refrescar(consultaArt);
        }
    }


    //Devuelve la seccion del header que hemos clickeado
    if(headerArt->sortIndicatorSection() == 2)
    {
        headerArt->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(headerArt->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaArt.append(" ORDER BY cantidad asc");
            mpAlmacen->refrescar(consultaArt);
        }
        else
        {
            consultaArt.append(" ORDER BY cantidad desc");
            mpAlmacen->refrescar(consultaArt);
        }
    }


    //Devuelve la seccion del header que hemos clickeado
    if(headerArt->sortIndicatorSection() == 3)
    {
        headerArt->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(headerArt->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaArt.append(" ORDER BY iva asc");
            mpAlmacen->refrescar(consultaArt);
        }
        else
        {
            consultaArt.append(" ORDER BY iva desc");
            mpAlmacen->refrescar(consultaArt);
        }
    }


}

void WidgetIntroducirCompra::on_rbMostrarTodosAlmacen_clicked()
{
    //Consulta activa actualmente
    consultaActivaArt = "select articulos.codigoean, articulos.descripcion, articulos.cantidad, articulos.iva from articulos, artprov WHERE articulos.codigoean = artprov.codigoean and artprov.proveedor = '"+cifProveedor+"' ";
    //Consulta a modificar
    consultaArt = consultaActivaArt;

    mpAlmacen->refrescar(consultaArt);
}


WidgetIntroducirCompra::~WidgetIntroducirCompra()
{
    delete ui;
}

