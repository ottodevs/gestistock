#include "widgetconexiones.h"
#include "ui_widgetconexiones.h"

WidgetConexiones::WidgetConexiones(QMdiArea *mdiArea, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetConexiones)
{
    ui->setupUi(this);

    //Titulo
    this->setWindowTitle(tr("Conexiones"));

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));

    //Puntero al MdiArea
    mdi = mdiArea;

    //Consulta para el QSqlQueryModel
    consultaActiva = "select date_format(conexiones.fechaentrada,'%d/%m/%Y %H:%i:%s'), usuarios.nombreusuario ,date_format(conexiones.fechasalida,'%d/%m/%Y %H:%i:%s') from conexiones,usuarios WHERE conexiones.usuario = usuarios.dni ";

    //Consulta a modificar
    consultaModificable = consultaActiva;

    //Reserva de memoria
    mp = new QSqlQueryConexiones;
    consultaConexiones = new QSqlQuery;

    //Colocamo la consulta
    mp->refrescar(consultaActiva);

    //Le colocamos el modelo al table view
    ui->tvConexiones->setModel(mp);

    //Recogemos el header del table view
    header = ui->tvConexiones->horizontalHeader();

    //El indicador de ordenacion lo quitamos
    header->setSortIndicatorShown(false);


    //Conectamos el header al slot
    connect(header,SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)),this,SLOT(refresh()));

    //item delegate, delegamos para poder modificar el aspecto
    ui->tvConexiones->setItemDelegateForColumn(0, new Delegate(this));
    ui->tvConexiones->setItemDelegateForColumn(1, new Delegate(this));
    ui->tvConexiones->setItemDelegateForColumn(2, new Delegate(this));


    //Tamaño del QTableView
    ui->tvConexiones->setFixedSize(380,345);

    //Colocamos los nombres en el table
    mp->setHeaderData(0,Qt::Horizontal,tr("Fecha de entrada\n"));
    mp->setHeaderData(1,Qt::Horizontal,tr("Usuario\n"));
    mp->setHeaderData(2,Qt::Horizontal,tr("Fecha de salida\n"));

    //Damos a cada columna la anchura deseada
    ui->tvConexiones->setColumnWidth(0,130);
    ui->tvConexiones->setColumnWidth(1,100);
    ui->tvConexiones->setColumnWidth(2,120);


    //Para cuando se cliquea sobre un item se marque la fila completa
    ui->tvConexiones->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvConexiones->setSelectionMode(QAbstractItemView::SingleSelection);

}

void WidgetConexiones::on_pbSalir_clicked()
{
    //Cerramos la ventana
    mdi->closeActiveSubWindow();

}


void WidgetConexiones::refresh()
{

    //"consultaModificable" es la que modificaremos añadiendole el resto del string
    //consultaModificable = consultaActiva;

    //Devuelve la seccion del header que hemos clickeado
    if(header->sortIndicatorSection() == 0)
    {
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaModificable.append(" ORDER BY fechaentrada asc");
            mp->refrescar(consultaModificable);
            consultaModificable = consultaActiva;

        }
        else
        {
            consultaModificable.append(" ORDER BY fechaentrada desc");
            mp->refrescar(consultaModificable);
            consultaModificable = consultaActiva;

        }
    }


    //Devuelve la seccion del header que hemos clickeado
    if(header->sortIndicatorSection() == 1)
    {
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaModificable.append(" ORDER BY usuario asc");
            mp->refrescar(consultaModificable);
            consultaModificable = consultaActiva;

        }
        else
        {
            consultaModificable.append(" ORDER BY usuario desc");
            mp->refrescar(consultaModificable);
            consultaModificable = consultaActiva;

        }
    }


    //Devuelve la seccion del header que hemos clickeado
    if(header->sortIndicatorSection() == 2)
    {
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaModificable.append(" ORDER BY fechasalida asc");
            mp->refrescar(consultaModificable);
            consultaModificable = consultaActiva;

        }
        else
        {
            consultaModificable.append(" ORDER BY fechasalida desc");
            mp->refrescar(consultaModificable);
            consultaModificable = consultaActiva;

        }
    }

}



void WidgetConexiones::on_pbBorrar_clicked()
{
    QMessageBox msgBox(this);

    msgBox.setWindowTitle(tr("Eliminar"));
    msgBox.setText(tr("Eliminar conexiones"));
    msgBox.setInformativeText(tr("¿Está seguro de eliminar todas las conexiones del programa hasta la fecha?"));
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.addButton(tr("Si"),QMessageBox::AcceptRole);

    //Guardamos el boton en una variable para despues hacerlo por defecto
    QPushButton *pb = msgBox.addButton(tr("No"),QMessageBox::RejectRole);

    //Por defecto el boton que saldra sombreado
    msgBox.setDefaultButton(pb);

    //Devuelve la respuesta que hayamos dado, si contesta que si, borramos
    if(!msgBox.exec())
    {
        consultaConexiones->exec("DELETE FROM conexiones WHERE fechaentrada != fechasalida");
        consultaModificable = "select DATE_FORMAT(conexiones.fechaentrada, '%d/%m/%Y %H:%i:%s'),usuarios.nombreusuario,DATE_FORMAT(conexiones.fechasalida, '%d/%m/%Y %H:%i:%s') from conexiones, usuarios WHERE usuarios.dni = conexiones.usuario";
        mp->refrescar(consultaModificable);
        consultaActiva = consultaModificable;
    }

}


void WidgetConexiones::changeEvent(QEvent* event)
{
    if(event != NULL)
    {   
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}



WidgetConexiones::~WidgetConexiones()
{
    delete ui;
}
