#include "widgetarticulosproveedores.h"
#include "ui_widgetarticulosproveedores.h"



WidgetArticulosProveedores::WidgetArticulosProveedores(QString user, QMdiArea *mdiArea, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetArticulosProveedores)
{
    ui->setupUi(this);

    //Titulo
    this->setWindowTitle("Articulos de Proveedores");
    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));
    //Modalidad
    this->setWindowModality(Qt::WindowModal);
    this->setFocus();

    cad = "";

    consultArticulos = new QSqlQuery;
    consultAlmacen = new QSqlQuery;

    usuarioActivo = user;

    inicializarTabArticulosProveedor();
    inicializarTabAlmacen();


}

void WidgetArticulosProveedores::inicializarTabArticulosProveedor()
{
    cn = new QSqlQuery;
    mp = new QSqlQueryArticulosProveedor;

    /*****************Proveedores*****************/

    this->rellenarComboProveedores();

    /***************FinProveedores****************/


    ui->cbProveedor->setCurrentIndex(0);

    header = ui->tvArticulosProveedor->horizontalHeader();

    header->setSortIndicatorShown(false);

    //Conectamos el header al slot
    connect(header,SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), this, SLOT(refresh()));

    //item delegate
    ui->tvArticulosProveedor->setItemDelegateForColumn(0, new Delegate(this));
    ui->tvArticulosProveedor->setItemDelegateForColumn(1, new Delegate(this));
    ui->tvArticulosProveedor->setItemDelegateForColumn(2, new Delegate(this));


    //Tamaño del QTableView
    ui->tvArticulosProveedor->setFixedSize(600,290);

    //Colocamos los nombres en el table
    mp->setHeaderData(0,Qt::Horizontal,tr("CódigoEAN\n"));
    mp->setHeaderData(1,Qt::Horizontal,tr("Descripción\n"));
    mp->setHeaderData(2,Qt::Horizontal,tr("Precio\n"));

    //Damos a cada columna la anchura deseada
    ui->tvArticulosProveedor->setColumnWidth(0,120);
    ui->tvArticulosProveedor->setColumnWidth(1,400);
    ui->tvArticulosProveedor->setColumnWidth(2,60);


    //Para cuando se cliquea sobre un item se marque la fila completa
    ui->tvArticulosProveedor->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvArticulosProveedor->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->rbCodigoEAN->setChecked(true);
}

void WidgetArticulosProveedores::inicializarTabAlmacen()
{
    mpAlmacen = new QSqlQueryArticulos;
    headerArt = ui->tvArticulos->horizontalHeader();

    rellenarComboTipos();

    //Consulta activa actualmente
    consultaActivaArt = "select codigoean,descripcion,cantidad,iva from articulos";
    //Consulta a modificar
    consultaArt = consultaActivaArt;

    mpAlmacen->refrescar(consultaArt);

    ui->tvArticulos->setModel(mpAlmacen);

    headerArt->setSortIndicatorShown(false);

    //Conectamos el header al slot
    connect(headerArt,SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), this, SLOT(refreshOrdenarArticulosAlmacen()));

    //item delegate
    ui->tvArticulos->setItemDelegateForColumn(0, new Delegate(this));
    ui->tvArticulos->setItemDelegateForColumn(1, new Delegate(this));
    ui->tvArticulos->setItemDelegateForColumn(2, new Delegate(this));
    ui->tvArticulos->setItemDelegateForColumn(3, new Delegate(this));
    ui->tvArticulos->setItemDelegateForColumn(4, new Delegate(this));


    //Tamaño del QTableView
    ui->tvArticulos->setFixedSize(740,320);

    //Colocamos los nombres en el table
    mpAlmacen->setHeaderData(0,Qt::Horizontal,tr("CódigoEAN\n"));
    mpAlmacen->setHeaderData(1,Qt::Horizontal,tr("Descripción\n"));
    mpAlmacen->setHeaderData(2,Qt::Horizontal,tr("Cantidad\n"));
    mpAlmacen->setHeaderData(3,Qt::Horizontal,tr("IVA\n"));

    //Damos a cada columna la anchura deseada
    ui->tvArticulos->setColumnWidth(0,150);
    ui->tvArticulos->setColumnWidth(1,450);
    ui->tvArticulos->setColumnWidth(2,70);
    ui->tvArticulos->setColumnWidth(3,50);

    //Para cuando se cliquea sobre un item se marque la fila completa
    ui->tvArticulos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvArticulos->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->rbCodigoEANAlmacen->setChecked(true);
}

void WidgetArticulosProveedores::rellenarComboProveedores()
{
    QStringList proveedores;

    cn->exec("SELECT nombreproveedor FROM proveedores");

    while(cn->next())
        proveedores.append(cn->value(0).toString());

    ui->cbProveedor->addItems(proveedores);
}

void WidgetArticulosProveedores::refresh()
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
            consulta.append(" ORDER BY codigoean asc");
            mp->refrescar(consulta);
        }
        else
        {
            consulta.append(" ORDER BY codigoean desc");
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
            consulta.append(" ORDER BY descripcion asc");
            mp->refrescar(consulta);
        }
        else
        {
            consulta.append(" ORDER BY descripcion desc");
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
            consulta.append(" ORDER BY precio asc");
            mp->refrescar(consulta);
        }
        else
        {
            consulta.append(" ORDER BY precio desc");
            mp->refrescar(consulta);
        }
    }
}

//Articulos proveedor
void WidgetArticulosProveedores::on_rbMostrarTodos_clicked()
{
    //Consulta activa actualmente
    consultaActiva = "select articulos.codigoean, articulos.descripcion, artprov.precio from articulos, artprov, proveedores where articulos.codigoean = artprov.codigoean and proveedores.cif = '"+cifProveedor+"' AND proveedores.cif = artprov.proveedor";
    mp->refrescar(consultaActiva);
    //Consulta a modificar
    consulta = consultaActiva;
}




void WidgetArticulosProveedores::on_cbProveedor_currentIndexChanged(const QString &arg1)
{
    QSqlQuery claveProveedores;

    claveProveedores.exec("SELECT proveedores.cif FROM proveedores WHERE proveedores.nombreproveedor = '"+arg1+"'");
    claveProveedores.first();

    cifProveedor = claveProveedores.value(0).toString();

    //Consulta activa actualmente
    consultaActiva = "select articulos.codigoean, articulos.descripcion, artprov.precio from articulos, artprov, proveedores where articulos.codigoean = artprov.codigoean and proveedores.cif = '"+cifProveedor+"' AND proveedores.cif = artprov.proveedor";

    mp->refrescar(consultaActiva);

    //Consulta a modificar
    consulta = consultaActiva;

    ui->tvArticulosProveedor->setModel(mp);

}


WidgetArticulosProveedores::~WidgetArticulosProveedores()
{
    delete ui;
}

void WidgetArticulosProveedores::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}


//Articulos proveedor
void WidgetArticulosProveedores::on_tvArticulosProveedor_clicked(const QModelIndex &index)
{
    //Con esto encontramos la clave primaria
    QString primaryKey;

    primaryKey = index.sibling(index.row(),0).data().toString();

    //Reserva de memoria, y pasamos al constructor la clave primaria
    map = new DialogModificarArticuloProveedor(usuarioActivo,cifProveedor,primaryKey,consulta,mp,this);

    //Mostramos la ventana
    map->show();
}

//Articulos proveedores
void WidgetArticulosProveedores::on_pbBuscar_clicked()
{
    if(ui->rbCodigoEAN->isChecked() == true)
    {
        consulta = "select articulos.codigoean, articulos.descripcion, artprov.precio from articulos, artprov, proveedores WHERE articulos.codigoean = artprov.codigoean and proveedores.cif = '"+cifProveedor+"' AND proveedores.cif = artprov.proveedor AND articulos.codigoean like '%"+ui->leBuscar->text()+"%'";
        mp->refrescar(consulta);
        consultaActiva = consulta;
        //Desactivamos para mostrar la consulta y que no aparezca el indicador
        header->setSortIndicatorShown(false);
    }

    if(ui->rbDescripcion->isChecked() == true)
    {
        consulta = "select articulos.codigoean, articulos.descripcion, artprov.precio from articulos, artprov, proveedores WHERE articulos.codigoean = artprov.codigoean and proveedores.cif = '"+cifProveedor+"' AND proveedores.cif = artprov.proveedor AND articulos.descripcion like '%"+ui->leBuscar->text()+"%'";
        mp->refrescar(consulta);
        consultaActiva = consulta;
        header->setSortIndicatorShown(false);
    }

}

void WidgetArticulosProveedores::refreshOrdenarArticulosAlmacen()
{
    consultaArt = consultaActivaArt;

    //No dejamos ordenarlo por CodigoEAN
    if(headerArt->sortIndicatorSection() == 0)
    {
        headerArt->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(headerArt->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaArt.append(" ORDER BY codigoean asc");
            mpAlmacen->refrescar(consultaArt);
        }
        else
        {
            consultaArt.append(" ORDER BY codigoean desc");
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

//Articulos almacen
void WidgetArticulosProveedores::on_tvArticulos_clicked(const QModelIndex &index)
{
    //Con esto encontramos la clave primaria
    QString primaryKey;
    QSqlQuery query;

    primaryKey = index.sibling(index.row(),0).data().toString();


    query.exec("SELECT nombreproveedor FROM proveedores WHERE cif NOT IN(SELECT proveedor FROM artprov WHERE codigoean = '"+primaryKey+"') ");
    query.first();

    if(query.isValid())
    {
        //Reserva de memoria, y pasamos al constructor la clave primaria
        darp = new DialogAnyadirArticuloProveedor(primaryKey,mp,consulta,this);
        darp->show();

    }else
        QMessageBox::warning(this,tr("Aviso"),tr("Artículo relacionado con todos los proveedores"),tr("Aceptar"));
}


//Boton de buscar almacen
void WidgetArticulosProveedores::on_pbBuscar_2_clicked()
{
    if(ui->rbCodigoEANAlmacen->isChecked() == true)
    {
        consultaArt = "select CodigoEAN, Descripcion, Cantidad, IVA from articulos WHERE CodigoEAN like '%"+ui->leBuscar_2->text()+"%'";
        mpAlmacen->refrescar(consultaArt);
        consultaActivaArt = consultaArt;
        //Desactivamos para mostrar la consulta y que no aparezca el indicador
        headerArt->setSortIndicatorShown(false);
    }

    if(ui->rbDescripcionAlmacen->isChecked() == true)
    {
        consultaArt = "select CodigoEAN, Descripcion, Cantidad, IVA from articulos WHERE Descripcion like '%"+ui->leBuscar_2->text()+"%'";
        mpAlmacen->refrescar(consultaArt);
        consultaActivaArt = consultaArt;
        headerArt->setSortIndicatorShown(false);
    }

    if(ui->rbTipoProductoAlmacen->isChecked() == true)
    {
        consultaArt = "select CodigoEAN, Descripcion, Cantidad, IVA from articulos WHERE tipoproducto = '"+ui->cbTipoProducto->currentText()+"'";
        mpAlmacen->refrescar(consultaArt);
        consultaActivaArt = consultaArt;
        headerArt->setSortIndicatorShown(false);
    }
}




void WidgetArticulosProveedores::on_rbMostrarTodosAlmacen_clicked()
{
    //Consulta activa actualmente
    consultaActivaArt = "select codigoean,descripcion,cantidad,iva from articulos";
    //Consulta a modificar
    consultaArt = consultaActivaArt;

    mpAlmacen->refrescar(consultaArt);
}


void WidgetArticulosProveedores::rellenarComboTipos()
{
    QSqlQuery cn;
    QStringList tipos;

    cn.prepare("select nombretipo from tipoproducto");
    cn.exec();

    while(cn.next())
        tipos.append(cn.value(0).toString());

    ui->cbTipoProducto->addItems(tipos);
}


void WidgetArticulosProveedores::keyReleaseEvent(QKeyEvent *ke)
{
    qDebug() << ui->tabWidget->currentIndex();

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

                    //Comprobamos si el articulo lo tenemos ya en la base de datos
                    consultArticulos->exec("SELECT * FROM artprov WHERE artprov.codigoean = '"+EAN+"' and artprov.proveedor = '"+cifProveedor+"' ");
                    consultAlmacen->exec("SELECT * FROM articulos WHERE articulos.codigoean = '"+EAN+"' ");

                    if(consultAlmacen->size() > 0 )
                    {
                        //Si no hay ningun arti­culo con ese CodigoEAN en el provedor...
                        if(consultArticulos->size() < 1)
                        {
                            darp = new DialogAnyadirArticuloProveedor(EAN,mp,consulta,this);
                            darp->show();


                        //Si lo tenemos en el proveedor...
                        }else if(consultArticulos->size() > 0)
                        {
                            //Reserva de memoria, y pasamos al constructor la clave primaria
                            map = new DialogModificarArticuloProveedor(usuarioActivo,cifProveedor,EAN,consulta,mp,this);
                            map->show();
                        }



                    }else
                        QMessageBox::warning(this,"Aviso","El artículo no se encuentra en el almacén","Aceptar");


                }else{

                    qDebug() << "Esto no es un codigo";

                }


                qDebug() << "Digito resultado: " << Res;
                qDebug() << "Digito solución: " << DigitoControl;
            }

        }

}
