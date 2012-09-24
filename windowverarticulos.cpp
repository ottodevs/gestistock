#include "windowverarticulos.h"
#include "ui_windowverarticulos.h"

QString cad = "";

WindowVerArticulos::WindowVerArticulos(QString userActivo, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowVerArticulos)
{
    ui->setupUi(this);

    //Titulo
    this->setWindowTitle(tr("Almacén"));

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/ark.png"));

    //Establecemos el foco en la ventana actual
    this->setFocus();

    consultArticulos = new QSqlQuery;
    mp = new QSqlQueryArticulos;

    //Usuario activo
    usuarioActivo = userActivo;

    //Consulta activa actualmente
    consultaActiva = "select codigoean,descripcion,cantidad,iva from articulos";

    //Consulta a modificar
    consulta = consultaActiva;

    //Marcamos el radioButton CodigoEAN inicialmente
    ui->rbCodigoEAN->setChecked(true);

    //Agregamos los items al combo
    rellenarCombo();

    mp->refrescar(consulta);

    ui->tableView->setModel(mp);

    header = ui->tableView->horizontalHeader();

    header->setSortIndicatorShown(false);

    //Conectamos el header al slot
    connect(header,SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), this, SLOT(refresh()));

    //item delegate
    ui->tableView->setItemDelegateForColumn(0, new DelegateArticulos(this));
    ui->tableView->setItemDelegateForColumn(1, new DelegateArticulos(this));
    ui->tableView->setItemDelegateForColumn(2, new DelegateArticulos(this));
    ui->tableView->setItemDelegateForColumn(3, new DelegateArticulos(this));
    ui->tableView->setItemDelegateForColumn(4, new DelegateArticulos(this));


    //Tamaño del QTableView
    ui->tableView->setFixedSize(740,330);

    //Colocamos los nombres en el table
    mp->setHeaderData(0,Qt::Horizontal,tr("CódigoEAN\n"));
    mp->setHeaderData(1,Qt::Horizontal,tr("Descripción\n"));
    mp->setHeaderData(2,Qt::Horizontal,tr("Cantidad\n"));
    mp->setHeaderData(3,Qt::Horizontal,tr("IVA\n"));

    //Damos a cada columna la anchura deseada
    ui->tableView->setColumnWidth(0,150);
    ui->tableView->setColumnWidth(1,450);
    ui->tableView->setColumnWidth(2,70);
    ui->tableView->setColumnWidth(3,50);

    //Para cuando se cliquea sobre un item se marque la fila completa
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);


    //Contamos los items del model para mostrarlos en el display
    ui->lcdNumeroArticulos->display(mp->rowCount());

}


void WindowVerArticulos::refresh()
{
    //"consulta" es la que modificaremos añadiendole el resto del string
    consulta = consultaActiva;

    if(header->sortIndicatorSection() == 0)
    {
       // header->setSortIndicatorShown(false);
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consulta.append(" ORDER BY codigoean asc");
            mp->refrescar(consulta);
            //consulta = consultaActiva;
            ui->lcdNumeroArticulos->display(mp->rowCount());
        }
        else
        {
            consulta.append(" ORDER BY codigoean desc");
            mp->refrescar(consulta);
            //consulta = consultaActiva;
            ui->lcdNumeroArticulos->display(mp->rowCount());
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
            //consulta = consultaActiva;
            ui->lcdNumeroArticulos->display(mp->rowCount());
        }
        else
        {
            consulta.append(" ORDER BY descripcion desc");
            mp->refrescar(consulta);
            //consulta = consultaActiva;
            ui->lcdNumeroArticulos->display(mp->rowCount());
        }
    }


    //Devuelve la seccion del header que hemos clickeado
    if(header->sortIndicatorSection() == 2)
    {
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consulta.append(" ORDER BY cantidad asc");
            mp->refrescar(consulta);
            //consulta = consultaActiva;
            ui->lcdNumeroArticulos->display(mp->rowCount());

        }
        else
        {
            consulta.append(" ORDER BY cantidad desc");
            mp->refrescar(consulta);
            //consulta = consultaActiva;
            ui->lcdNumeroArticulos->display(mp->rowCount());
        }
    }


    //Devuelve la seccion del header que hemos clickeado
    if(header->sortIndicatorSection() == 3)
    {
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consulta.append(" ORDER BY iva asc");
            mp->refrescar(consulta);
            //consulta = consultaActiva;
            ui->lcdNumeroArticulos->display(mp->rowCount());
        }
        else
        {
            consulta.append(" ORDER BY iva desc");
            mp->refrescar(consulta);
            //consulta = consultaActiva;
            ui->lcdNumeroArticulos->display(mp->rowCount());
        }
    }


}


void WindowVerArticulos::on_actionNuevo_Articulo_activated()
{
    /*
    //Reservamos memoria
    na = new dNuevoArticulo(usuarioActivo,this,this);
    //Desactivamos la ventana actual
    this->setEnabled(false);
    //Activamos la hija
    na->setEnabled(true);
    //Mostramos la pantalla hija
    na->setVisible(true);
    */
}



void WindowVerArticulos::on_pbBuscar_clicked()
{

    if(ui->rbCodigoEAN->isChecked() == true)
    {
        consulta = "select CodigoEAN, Descripcion, Cantidad, IVA from articulos WHERE CodigoEAN like '%"+ui->leBuscar->text()+"%'";
        mp->refrescar(consulta);
        consultaActiva = consulta;
        ui->lcdNumeroArticulos->display(mp->rowCount());
        //Desactivamos para mostrar la consulta y que no aparezca el indicador
        header->setSortIndicatorShown(false);
    }

    if(ui->rbDescripcion->isChecked() == true)
    {
        consulta = "select CodigoEAN, Descripcion, Cantidad, IVA from articulos WHERE Descripcion like '%"+ui->leBuscar->text()+"%'";
        mp->refrescar(consulta);
        consultaActiva = consulta;
        ui->lcdNumeroArticulos->display(mp->rowCount());
        header->setSortIndicatorShown(false);
    }

    if(ui->rbTipoProducto->isChecked() == true)
    {
        consulta = "select CodigoEAN, Descripcion, Cantidad, IVA from articulos WHERE tipoproducto = '"+ui->cbTipoProducto->currentText()+"'";
        mp->refrescar(consulta);
        consultaActiva = consulta;
        ui->lcdNumeroArticulos->display(mp->rowCount());
        header->setSortIndicatorShown(false);
    }
}



void WindowVerArticulos::rellenarCombo()
{
    QSqlQuery cn;
    QStringList tipos;

    cn.prepare("select nombretipo from tipoproducto");
    cn.exec();

    while(cn.next())
        tipos.append(cn.value(0).toString());

    ui->cbTipoProducto->addItems(tipos);

}



void WindowVerArticulos::on_rbTipoProducto_clicked()
{
    ui->leBuscar->setEnabled(false);
    ui->cbTipoProducto->setEnabled(true);
}

void WindowVerArticulos::on_rbDescripcion_clicked()
{
    ui->leBuscar->setEnabled(true);
    ui->cbTipoProducto->setEnabled(false);
}

void WindowVerArticulos::on_rbMostrarTodos_clicked()
{
    ui->leBuscar->setEnabled(false);
    ui->cbTipoProducto->setEnabled(false);

    consulta = "select CodigoEAN, Descripcion, Cantidad, IVA from articulos";
    consultaActiva = consulta;

    mp->refrescar(consultaActiva);

    ui->lcdNumeroArticulos->display(mp->rowCount());
}

void WindowVerArticulos::on_rbCodigoEAN_clicked()
{
    ui->leBuscar->setEnabled(true);
    ui->cbTipoProducto->setEnabled(false);
}

void WindowVerArticulos::keyReleaseEvent(QKeyEvent *ke)
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
                        naa = new DialogNuevoArticuloAlmacen(usuarioActivo,this,mp,consulta,ui->lcdNumeroArticulos,EAN);
                        naa->show();


                    //Si lo tenemos en la base de datos...
                    }else if(consultArticulos->size() > 0)
                    {
                        ma = new DialogModificarArticulo(usuarioActivo,EAN,consulta,mp,this);
                        ma->show();

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


void WindowVerArticulos::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QMainWindow::changeEvent(event);
}


void WindowVerArticulos::on_pbNuevoArticulo_clicked()
{
    //Reservamos memoria
    naa = new DialogNuevoArticuloAlmacen(usuarioActivo,this,mp,consulta,ui->lcdNumeroArticulos);
    //Mostramos la ventana
    naa->show();
}


void WindowVerArticulos::on_tableView_clicked(const QModelIndex &index)
{
    //Con esto encontramos la clave primaria
    QString primaryKey;

    primaryKey = index.sibling(index.row(),0).data().toString();

    //Reserva de memoria, y pasamos al constructor la clave primaria
    ma = new DialogModificarArticulo(usuarioActivo,primaryKey,consulta,mp,this);

    //Mostramos la ventana
    ma->show();
}


WindowVerArticulos::~WindowVerArticulos()
{
    delete ui;
}
