#include "widgetverusuarios.h"
#include "ui_widgetverusuarios.h"

WidgetVerUsuarios::WidgetVerUsuarios(QString user, QMdiArea *ma, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetVerUsuarios)
{
    ui->setupUi(this);

    //Titulo
    this->setWindowTitle(tr("Usuarios"));

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));

    //Usuario actual
    usuarioActivo = user;

    //Puntero al MdiArea
    mdi = ma;

    //Consulta para el QSqlQueryModel
    consultaActiva = "select nombreusuario,correo,date_format(fechaalta,'%d/%m/%Y'),if(superusuario < 1,'NO','SI') from usuarios WHERE usuarios.novisible = '0'";
    consulta = consultaActiva;

    mp = new QSqlQueryUsuarios;

    //Colocamo la consulta
    mp->refrescar(consulta);

    //Le colocamos el modelo al table view
    ui->tableView->setModel(mp);

    //Recogemos el header del table view
    header = ui->tableView->horizontalHeader();

    //El indicador de ordenacion lo quitamos
    header->setSortIndicatorShown(false);

    //Conectamos el header al slot
    connect(header,SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), this, SLOT(refresh()));

    //item delegate, delegamos para poder modificar el aspecto
    ui->tableView->setItemDelegateForColumn(0, new Delegate(this));
    ui->tableView->setItemDelegateForColumn(1, new Delegate(this));
    ui->tableView->setItemDelegateForColumn(2, new Delegate(this));
    ui->tableView->setItemDelegateForColumn(3, new Delegate(this));




    //Tamaño del QTableView
    ui->tableView->setFixedSize(600,345);

    //Colocamos los nombres en el table
    mp->setHeaderData(0,Qt::Horizontal,tr("Nombre\n"));
    mp->setHeaderData(1,Qt::Horizontal,tr("Correo electrónico\n"));
    mp->setHeaderData(2,Qt::Horizontal,tr("Fecha de alta\n"));
    mp->setHeaderData(3,Qt::Horizontal,tr("Administrador\n"));



    //Damos a cada columna la anchura deseada
    ui->tableView->setColumnWidth(0,120);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,90);
    ui->tableView->setColumnWidth(3,50);



    //Para cuando se cliquea sobre un item se marque la fila completa
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

}


WidgetVerUsuarios::~WidgetVerUsuarios()
{
    delete ui;
}

void WidgetVerUsuarios::on_pbSalir_clicked()
{
    //Esto hay que hacer
    mdi->closeActiveSubWindow();
}



void WidgetVerUsuarios::on_tableView_clicked(const QModelIndex &index)
{
    QString primaryKey;

    //Con esto encontramos la clave primaria
    primaryKey = index.sibling(index.row(),0).data().toString();
    //Reserva de memoria, y pasamos al constructor la clave primaria
    dmu = new DialogModificarUsuario(usuarioActivo,primaryKey,consulta,mp,this);
    //Mostramos la ventana
    dmu->setVisible(true);

}

void WidgetVerUsuarios::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}

void WidgetVerUsuarios::refresh()
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
            consulta.append(" ORDER BY nombreusuario asc");
            mp->refrescar(consulta);
        }
        else
        {
            consulta.append(" ORDER BY nombreusuario desc");
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
            consulta.append(" ORDER BY correo asc");
            mp->refrescar(consulta);
        }
        else
        {
            consulta.append(" ORDER BY correo desc");
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
            consulta.append(" ORDER BY fechaalta asc");
            mp->refrescar(consulta);
        }
        else
        {
            consulta.append(" ORDER BY fechaalta desc");
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
            consulta.append(" ORDER BY superusuario asc");
            mp->refrescar(consulta);
        }
        else
        {
            consulta.append(" ORDER BY superusuario desc");
            mp->refrescar(consulta);
        }
    }


}



