#include "widgetproveedoresmascomprados.h"
#include "ui_widgetproveedoresmascomprados.h"

WidgetProveedoresMasComprados::WidgetProveedoresMasComprados(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetProveedoresMasComprados)
{
    ui->setupUi(this);

    consultaProveedores = new QSqlQuery;
    mp = new QSqlQueryProveedoresMasComprados;

    //Titulo
    this->setWindowTitle(tr("TOP Proveedores"));

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));

    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);

    consulta = "SELECT @rownum:=@rownum + 1 'row_number', T.nombreproveedor, T.cantidadArticulos, T.Importe FROM (SELECT @rownum:=0) R,(SELECT proveedores.nombreproveedor, SUM(compraproductos.cantidad) as cantidadArticulos, ROUND(SUM((compraproductos.precio + ( compraproductos.precio * ( compraproductos.iva /100 ))) * compraproductos.cantidad),2) as 'Importe' FROM compraproductos, proveedores WHERE compraproductos.proveedor = proveedores.cif GROUP BY compraproductos.proveedor ORDER BY Importe desc) T ORDER BY T.Importe desc";

    mp->refrescar(consulta);

    ui->tableView->setModel(mp);

    //Limpiamos
    consultaProveedores->clear();
    consultaProveedores->exec("SELECT nombreproveedor, localidad ,cif, correo FROM proveedores WHERE proveedores.nombreproveedor = '"+mp->data(mp->index(0,1)).toString()+"' ");
    consultaProveedores->first();

    //Rellenamos los campos
    if(consultaProveedores->isValid())
    {
        ui->leNombre->setText(consultaProveedores->value(0).toString());
        ui->leLocalidad->setText(consultaProveedores->value(1).toString());
        ui->leCIF->setText(consultaProveedores->value(2).toString());
        ui->leCorreo->setText(consultaProveedores->value(3).toString());
    }

    ui->leNombre->setEnabled(false);
    ui->leLocalidad->setEnabled(false);
    ui->leCIF->setEnabled(false);
    ui->leCorreo->setEnabled(false);

    ui->tableView->setSortingEnabled(false);

    //item delegate
    ui->tableView->setItemDelegateForColumn(0, new Delegate(this));
    ui->tableView->setItemDelegateForColumn(1, new Delegate(this));
    ui->tableView->setItemDelegateForColumn(2, new Delegate(this));
    ui->tableView->setItemDelegateForColumn(3, new Delegate(this));

    //Tamaño del QTableView
    ui->tableView->setFixedSize(600,250);

    //Colocamos los nombres en el table
    mp->setHeaderData(0,Qt::Horizontal,tr("Posición\n"));
    mp->setHeaderData(1,Qt::Horizontal,tr("Nombre\n"));
    mp->setHeaderData(2,Qt::Horizontal,tr("Cantidad\n"));
    mp->setHeaderData(3,Qt::Horizontal,tr("Importe\n"));


    //Damos a cada columna la anchura deseada
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,320);
    ui->tableView->setColumnWidth(2,70);


    //Para cuando se cliquea sobre un item se marque la fila completa
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

}


void WidgetProveedoresMasComprados::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}


WidgetProveedoresMasComprados::~WidgetProveedoresMasComprados()
{
    delete ui;
}
