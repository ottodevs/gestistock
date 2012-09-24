#include "widgetsalidasarticulos.h"
#include "ui_widgetsalidasarticulos.h"


WidgetSalidasArticulos::WidgetSalidasArticulos(QString user, QString *local, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetSalidasArticulos)
{
    ui->setupUi(this);

    //Titulo
    this->setWindowTitle("Salida de Artículos");
    //Ventana modal
    this->setWindowModality(Qt::WindowModal);
    //Foco principal
    this->setFocus();
    this->setFocusPolicy(Qt::StrongFocus);

    querySalidas = new QSqlQuery;
    queryConsulta = new QSqlQuery;

    headerArt = ui->tvArticulos->horizontalHeader();
    headerSal = ui->tvSalidas->horizontalHeader();

    usuarioActivo = user;
    locale = local;

    mpArticulos = new QSqlQueryArticulos;
    mpSalidas = new QSqlQuerySalidas;

    //Inicializamos los elementos del tabWidget
    inicializarTabArticulos();
    inicializarTabSalidas();


    //Actualizar el idioma de la fecha
    this->actualizarStatus((*locale));

    //Marcamos los dias en el calendario
    marcarCalendario();
}

void WidgetSalidasArticulos::marcarCalendario()
{
    //Establecemos el fondo
    fondoCalendar.setBackground(Qt::cyan);

    //Limpiar el calendarWidget
    ui->deDate->calendarWidget()->setDateTextFormat(QDate(),fondoCalendar);

    //Ejecutamos la consulta para saber los dias que marcar en el calendario
    querySalidas->exec("SELECT DISTINCT fecha FROM salidasarticulos");

    while(querySalidas->next())
        ui->deDate->calendarWidget()->setDateTextFormat(querySalidas->value(0).toDate(),fondoCalendar);
}

void WidgetSalidasArticulos::actualizarStatus(QString idioma)
{
    QLocale newlocale;

    if(idioma == "es")
        newlocale = QLocale::Spanish;
    else
        newlocale = QLocale::English;

    ui->deDate->calendarWidget()->setLocale(newlocale);
    ui->deDate->setLocale(newlocale);
}

void WidgetSalidasArticulos::inicializarTabArticulos()
{
    //Consulta activa actualmente
    consultaActivaArt = "select codigoean,descripcion,cantidad,iva from articulos";
    //Consulta a modificar
    consultaArt = consultaActivaArt;

    mpArticulos->refrescar(consultaArt);

    ui->tvArticulos->setModel(mpArticulos);

    headerArt->setSortIndicatorShown(false);

    //Conectamos el header al slot
    connect(headerArt,SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), this, SLOT(refreshOrdenarArticulos()));

    //item delegate
    ui->tvArticulos->setItemDelegateForColumn(0, new DelegateArticulos(this));
    ui->tvArticulos->setItemDelegateForColumn(1, new DelegateArticulos(this));
    ui->tvArticulos->setItemDelegateForColumn(2, new DelegateArticulos(this));
    ui->tvArticulos->setItemDelegateForColumn(3, new DelegateArticulos(this));
    ui->tvArticulos->setItemDelegateForColumn(4, new DelegateArticulos(this));


    //Tamaño del QTableView
    ui->tvArticulos->setFixedSize(740,320);

    //Colocamos los nombres en el table
    mpArticulos->setHeaderData(0,Qt::Horizontal,tr("CódigoEAN\n"));
    mpArticulos->setHeaderData(1,Qt::Horizontal,tr("Descripción\n"));
    mpArticulos->setHeaderData(2,Qt::Horizontal,tr("Cantidad\n"));
    mpArticulos->setHeaderData(3,Qt::Horizontal,tr("IVA\n"));

    //Damos a cada columna la anchura deseada
    ui->tvArticulos->setColumnWidth(0,150);
    ui->tvArticulos->setColumnWidth(1,450);
    ui->tvArticulos->setColumnWidth(2,70);
    ui->tvArticulos->setColumnWidth(3,50);

    //Para cuando se cliquea sobre un item se marque la fila completa
    ui->tvArticulos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvArticulos->setSelectionMode(QAbstractItemView::SingleSelection);
}

void WidgetSalidasArticulos::inicializarTabSalidas()
{
    ui->deDate->setDate(QDate::currentDate());
    ui->deDate->setDisplayFormat("dddd, dd 'de' MMMM 'de' yyyy");

    rellenarComboTipos();

    //Consulta activa actualmente
    consultaActivaSal = "select salidasarticulos.articulo,articulos.descripcion,salidasarticulos.cantidad,articulos.tipoproducto from salidasarticulos,articulos WHERE salidasarticulos.fecha = '"+ui->deDate->date().toString("yyyy/MM/dd")+"' AND salidasarticulos.articulo = articulos.codigoean";
    //Consulta a modificar
    consultaSal = consultaActivaSal;

    mpSalidas->refrescar(consultaSal);

    ui->tvSalidas->setModel(mpSalidas);

    headerSal = ui->tvSalidas->horizontalHeader();

    headerSal->setSortIndicatorShown(false);

    //Conectamos el header al slot
    connect(headerSal,SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), this, SLOT(refreshOrdenarSalidas()));

    //item delegate
    ui->tvSalidas->setItemDelegateForColumn(0, new Delegate(this));
    ui->tvSalidas->setItemDelegateForColumn(1, new Delegate(this));
    ui->tvSalidas->setItemDelegateForColumn(2, new Delegate(this));
    ui->tvSalidas->setItemDelegateForColumn(3, new Delegate(this));
    ui->tvSalidas->setItemDelegateForColumn(4, new Delegate(this));


    //Tamaño del QTableView
    ui->tvSalidas->setFixedSize(740,320);

    //Colocamos los nombres en el table
    mpSalidas->setHeaderData(0,Qt::Horizontal,tr("CódigoEAN\n"));
    mpSalidas->setHeaderData(1,Qt::Horizontal,tr("Descripción\n"));
    mpSalidas->setHeaderData(2,Qt::Horizontal,tr("Cantidad\n"));
    mpSalidas->setHeaderData(3,Qt::Horizontal,tr("Tipo\n"));

    //Damos a cada columna la anchura deseada
    ui->tvSalidas->setColumnWidth(0,120);
    ui->tvSalidas->setColumnWidth(1,420);
    ui->tvSalidas->setColumnWidth(2,60);
    ui->tvSalidas->setColumnWidth(3,50);

    //Para cuando se cliquea sobre un item se marque la fila completa
    ui->tvSalidas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvSalidas->setSelectionMode(QAbstractItemView::SingleSelection);
}

void WidgetSalidasArticulos::refreshOrdenarArticulos()
{
    consultaArt = consultaActivaArt;

    if(headerArt->sortIndicatorSection() == 0)
    {
        headerArt->setSortIndicatorShown(false);

        //Vemos que indicador está puesto
        if(headerArt->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaArt.append(" ORDER BY articulo asc");
            mpArticulos->refrescar(consultaArt);

        }
        else
        {
            consultaArt.append(" ORDER BY articulo desc");
            mpArticulos->refrescar(consultaArt);
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
            mpArticulos->refrescar(consultaArt);

        }
        else
        {
            consultaArt.append(" ORDER BY descripcion desc");
            mpArticulos->refrescar(consultaArt);
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
            mpArticulos->refrescar(consultaArt);
        }
        else
        {
            consultaArt.append(" ORDER BY cantidad desc");
            mpArticulos->refrescar(consultaArt);
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
            mpArticulos->refrescar(consultaArt);
        }
        else
        {
            consultaArt.append(" ORDER BY iva desc");
            mpArticulos->refrescar(consultaArt);
        }
    }


}


void WidgetSalidasArticulos::refreshOrdenarSalidas()
{

    //No dejamos ordenarlo por CodigoEAN
    if(headerSal->sortIndicatorSection() == 0)
    {
        headerSal->setSortIndicatorShown(false);
    }


    //Devuelve la seccion del header que hemos clickeado
    if(headerSal->sortIndicatorSection() == 1)
    {
        headerSal->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(headerSal->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaSal.append(" ORDER BY descripcion asc");
            mpSalidas->refrescar(consultaSal);
            consultaSal = consultaActivaSal;
        }
        else
        {
            consultaSal.append(" ORDER BY descripcion desc");
            mpSalidas->refrescar(consultaSal);
            consultaSal = consultaActivaSal;
        }
    }


    //Devuelve la seccion del header que hemos clickeado
    if(headerSal->sortIndicatorSection() == 2)
    {
        headerSal->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(headerSal->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaSal.append(" ORDER BY cantidad asc");
            mpSalidas->refrescar(consultaSal);
            consultaSal = consultaActivaSal;
        }
        else
        {
            consultaSal.append(" ORDER BY cantidad desc");
            mpSalidas->refrescar(consultaSal);
            consultaSal = consultaActivaSal;
        }
    }


    //Devuelve la seccion del header que hemos clickeado
    if(headerSal->sortIndicatorSection() == 3)
    {
        headerSal->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(headerSal->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaSal.append(" ORDER BY tipoproducto asc");
            mpSalidas->refrescar(consultaSal);
            consultaSal = consultaActivaSal;
        }
        else
        {
            consultaSal.append(" ORDER BY tipoproducto desc");
            mpSalidas->refrescar(consultaSal);
            consultaSal = consultaActivaSal;
        }
    }


}


void WidgetSalidasArticulos::on_pbBuscar_clicked()
{
    if(ui->rbCodigoEAN->isChecked() == true)
    {
        consultaArt = "select CodigoEAN, Descripcion, Cantidad, IVA from articulos WHERE CodigoEAN like '%"+ui->leBuscar->text()+"%'";
        mpArticulos->refrescar(consultaArt);
        consultaActivaArt = consultaArt;
        //Desactivamos para mostrar la consulta y que no aparezca el indicador
        headerArt->setSortIndicatorShown(false);
    }

    if(ui->rbDescripcion->isChecked() == true)
    {
        consultaArt = "select CodigoEAN, Descripcion, Cantidad, IVA from articulos WHERE Descripcion like '%"+ui->leBuscar->text()+"%'";
        mpArticulos->refrescar(consultaArt);
        consultaActivaArt = consultaArt;
        headerArt->setSortIndicatorShown(false);
    }

    if(ui->rbTipoProducto->isChecked() == true)
    {
        consultaArt = "select CodigoEAN, Descripcion, Cantidad, IVA from articulos WHERE tipoproducto = '"+ui->cbTipoProducto->currentText()+"'";
        mpArticulos->refrescar(consultaArt);
        consultaActivaArt = consultaArt;
        headerArt->setSortIndicatorShown(false);
    }
}

void WidgetSalidasArticulos::rellenarComboTipos()
{
    QSqlQuery cn;
    QStringList tipos;

    cn.prepare("select nombretipo from tipoproducto");
    cn.exec();

    while(cn.next())
        tipos.append(cn.value(0).toString());

    ui->cbTipoProducto->addItems(tipos);
}

void WidgetSalidasArticulos::on_rbCodigoEAN_clicked()
{
    ui->leBuscar->setEnabled(true);
    ui->cbTipoProducto->setEnabled(false);
}

void WidgetSalidasArticulos::on_rbDescripcion_clicked()
{
    ui->leBuscar->setEnabled(true);
    ui->cbTipoProducto->setEnabled(false);
}

void WidgetSalidasArticulos::on_rbTipoProducto_clicked()
{
    ui->leBuscar->setEnabled(false);
    ui->cbTipoProducto->setEnabled(true);
}

void WidgetSalidasArticulos::on_rbMostrarTodos_clicked()
{
    ui->leBuscar->setEnabled(false);
    ui->cbTipoProducto->setEnabled(false);

    consultaArt = "select CodigoEAN, Descripcion, Cantidad, IVA from articulos";
    consultaActivaArt = consultaArt;

    mpArticulos->refrescar(consultaActivaArt);

}

void WidgetSalidasArticulos::changeEvent(QEvent* event)
{
    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
        {
            //Cambiamos el idioma del dateEdit
            actualizarStatus(*(locale));
            ui->retranslateUi(this);
        }
    }

    QWidget::changeEvent(event);
}


void WidgetSalidasArticulos::on_deDate_dateChanged(const QDate &date)
{
    //Desactivamos el indicador de ordenacion
    headerSal->setSortIndicatorShown(false);

    //Consulta activa actualmente
    consultaActivaSal = "select salidasarticulos.articulo,articulos.descripcion,salidasarticulos.cantidad,articulos.tipoproducto FROM salidasarticulos,articulos WHERE salidasarticulos.fecha = '"+ui->deDate->date().toString("yyyy/MM/dd")+"' AND salidasarticulos.articulo = articulos.codigoean";
    //Consulta a modificar
    consultaSal = consultaActivaSal;
    //Refrescamos el tableView
    mpSalidas->refrescar(consultaSal);

}


void WidgetSalidasArticulos::on_tvArticulos_clicked(const QModelIndex &index)
{
    //Con esto encontramos la clave primaria
    QString primaryKey;

    primaryKey = index.sibling(index.row(),0).data().toString();

    //Reserva de memoria, y pasamos al constructor la clave primaria
    dsa = new DialogSalidaArticulo(usuarioActivo,primaryKey,mpArticulos,mpSalidas,consultaActivaArt,consultaActivaSal,ui->deDate->date(),this,this);

    dsa->show();
}

void WidgetSalidasArticulos::keyReleaseEvent(QKeyEvent *ke)
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
                    queryConsulta->exec("SELECT * FROM articulos WHERE codigoean = '"+EAN+"' ");

                    //Si no hay ningun arti­culo con ese CodigoEAN...
                    if(queryConsulta->size() < 1)
                    {
                        QMessageBox::warning(this,"Aviso", "El artículo no se encuentra en el almacén","Aceptar");

                    //Si lo tenemos en la base de datos...
                    }else if(queryConsulta->size() > 0)
                    {
                        //Reserva de memoria, y pasamos al constructor la clave primaria
                        dsa = new DialogSalidaArticulo(usuarioActivo,EAN,mpArticulos,mpSalidas,consultaActivaArt,consultaActivaSal,ui->deDate->date(),this,this);
                        dsa->show();

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




WidgetSalidasArticulos::~WidgetSalidasArticulos()
{
    delete ui;
}
