#include "widgetvertipoproductos.h"
#include "ui_widgetvertipoproductos.h"

WidgetVerTipoProductos::WidgetVerTipoProductos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetVerTipoProductos)
{
    ui->setupUi(this);

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));
    this->setWindowTitle(tr("Tipos de Artículos"));

    //Establecemos el foco en la ventana actual
    this->setFocus();


    mp = new QSqlQueryTipos;

    //Consulta activa actualmente
    consultaActiva = "SELECT nombretipo FROM tipoproducto";
    //Consulta a modificar
    consulta = consultaActiva;

    mp->refrescar(consulta);

    ui->tableView->setFixedSize(368,350);

    ui->tableView->setModel(mp);

    header = ui->tableView->horizontalHeader();

    header->setSortIndicatorShown(false);

    //Conectamos el header al slot
    connect(header,SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), this, SLOT(refresh()));

    //item delegate
    ui->tableView->setItemDelegateForColumn(0, new Delegate(this));


    mp->setHeaderData(0,Qt::Horizontal,tr("Nombre\n"));

    //Para cuando se cliquea sobre un item se marque la fila completa
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);


}


void WidgetVerTipoProductos::refresh()
{
    //"consulta" es la que modificaremos añadiendole el resto del string
    consulta = consultaActiva;

    //Devuelve la seccion del header que hemos clickeado
    if(header->sortIndicatorSection() == 0)
    {
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consulta.append(" ORDER BY nombretipo asc");
            mp->refrescar(consulta);
        }
        else
        {
            consulta.append(" ORDER BY nombretipo desc");
            mp->refrescar(consulta);
        }
    }




}

void WidgetVerTipoProductos::on_tableView_clicked(const QModelIndex &index)
{
    QString nombre;

    //Con esto encontramos la clave primaria
    nombre = index.sibling(index.row(),0).data().toString();

    dmt = new DialogModificarTipo(nombre,consulta,mp,this);
    dmt->show();
}

void WidgetVerTipoProductos::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}

WidgetVerTipoProductos::~WidgetVerTipoProductos()
{
    delete ui;
}
