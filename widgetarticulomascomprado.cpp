#include "widgetarticulomascomprado.h"
#include "ui_widgetarticulomascomprado.h"

WidgetArticuloMasComprado::WidgetArticuloMasComprado(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetArticuloMasComprado)
{
    ui->setupUi(this);

    consultaArticulos = new QSqlQuery;
    mp = new QSqlQueryArticulosMasComprados;

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));

    this->setWindowTitle(tr("TOP Compras"));

    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);

    consulta = "SELECT @rownum:=@rownum + 1 'row_number', T.codigoean, T.descripcion, T.cantidadCompra, T.Importe FROM (SELECT @rownum:=0) R,(SELECT articulos.codigoean, articulos.descripcion,SUM(compraproductos.cantidad) as cantidadCompra, ROUND(SUM( (compraproductos.precio + ( compraproductos.precio * ( compraproductos.iva /100 ) ) ) * compraproductos.cantidad),3) as Importe FROM compraproductos, articulos WHERE compraproductos.articulo = articulos.codigoean GROUP BY compraproductos.articulo ORDER BY cantidadCompra desc) T ORDER BY T.cantidadCompra desc";

    mp->refrescar(consulta);

    ui->tableView->setModel(mp);

    qDebug() << "Model" << mp->data(mp->index(0,1)).toString();

    //Limpiamos
    consultaArticulos->clear();
    consultaArticulos->exec("SELECT articulos.descripcion, articulos.tipoproducto, articulos.codigoean FROM articulos WHERE articulos.codigoean = '"+mp->data(mp->index(0,1)).toString()+"'");
    consultaArticulos->first();


    //Rellenamos los campos
    if(consultaArticulos->isValid())
    {
        ui->leNombre->setText(consultaArticulos->value(0).toString());
        ui->leTipo->setText(consultaArticulos->value(1).toString());
        ui->leCodEAN->setText(consultaArticulos->value(2).toString());
        ui->leCantidad->setText(mp->data(mp->index(0,3)).toString());
        ui->leDinero->setText(mp->data(mp->index(0,4)).toString());
    }

    ui->leCodEAN->setEnabled(false);
    ui->leCantidad->setEnabled(false);
    ui->leDinero->setEnabled(false);
    ui->leNombre->setEnabled(false);
    ui->leTipo->setEnabled(false);

    ui->tableView->setSortingEnabled(false);

    //item delegate
    ui->tableView->setItemDelegateForColumn(0, new Delegate(this));
    ui->tableView->setItemDelegateForColumn(1, new Delegate(this));
    ui->tableView->setItemDelegateForColumn(2, new Delegate(this));
    ui->tableView->setItemDelegateForColumn(3, new Delegate(this));
    ui->tableView->setItemDelegateForColumn(4, new Delegate(this));

    //Tamaño del QTableView
    ui->tableView->setFixedSize(600,290);

    //Colocamos los nombres en el table
    mp->setHeaderData(0,Qt::Horizontal,tr("Posición\n"));
    mp->setHeaderData(1,Qt::Horizontal,tr("CódigoEAN\n"));
    mp->setHeaderData(2,Qt::Horizontal,tr("Nombre\n"));
    mp->setHeaderData(3,Qt::Horizontal,tr("Cantidad\n"));
    mp->setHeaderData(4,Qt::Horizontal,tr("Importe\n"));


    //Damos a cada columna la anchura deseada
    ui->tableView->setColumnWidth(0,60);
    ui->tableView->setColumnWidth(1,120);
    ui->tableView->setColumnWidth(2,280);
    ui->tableView->setColumnWidth(3,60);
    ui->tableView->setColumnWidth(4,60);

    //Para cuando se cliquea sobre un item se marque la fila completa
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

WidgetArticuloMasComprado::~WidgetArticuloMasComprado()
{
    delete ui;
}

void WidgetArticuloMasComprado::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}
