#include "widgetactividadusuario.h"
#include "ui_widgetactividadusuario.h"

WidgetActividadUsuario::WidgetActividadUsuario(QMdiArea *mdiArea, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetActividadUsuario)
{
    ui->setupUi(this);

    //Reserva de memoria
    consultaUsuarios = new QSqlQuery();
    consultaArticulos = new QSqlQuery();
    mp = new QSqlQueryActividad;

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));

    //Nombre de la ventana
    this->setWindowTitle(tr("Actividad de Usuarios"));

    //Consulta activa actualmente
    consultaActiva = "select usuarios.nombreusuario, actividad.tipomovimiento, articulos.descripcion, actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,articulos,usuarios WHERE actividad.articulo = articulos.codigoean and usuarios.dni = actividad.usuario";

    //Consulta a modificar
    consultaModificable = consultaActiva;

    //rellenamos los combos
    rellenarComboUsuarios();
    rellenarComboTipoMovimientos();
    rellenarComboArticulos();

    //Ponemos la fecha actual
    ui->deFecha->setDate(QDate::currentDate());

    mp->refrescar(consultaModificable);

    ui->tvActividad->setModel(mp);

    header = ui->tvActividad->horizontalHeader();
    header->setSortIndicatorShown(false);

    header->showNormal();

    //Conectamos el header al slot
    connect(header,SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)),this,SLOT(refresh()));

    //item delegate
    ui->tvActividad->setItemDelegateForColumn(0, new Delegate(this));
    ui->tvActividad->setItemDelegateForColumn(1, new Delegate(this));
    ui->tvActividad->setItemDelegateForColumn(2, new Delegate(this));
    ui->tvActividad->setItemDelegateForColumn(3, new Delegate(this));
    ui->tvActividad->setItemDelegateForColumn(4, new Delegate(this));
    ui->tvActividad->setItemDelegateForColumn(5, new Delegate(this));

    //Tamaño del QTableView
    ui->tvActividad->setFixedSize(790,345);

    //Colocamos los nombres en el table
    mp->setHeaderData(0,Qt::Horizontal,tr("Usuario\n"));
    mp->setHeaderData(1,Qt::Horizontal,tr("Tipo de movimiento\n"));
    mp->setHeaderData(2,Qt::Horizontal,tr("Artículo\n"));
    mp->setHeaderData(3,Qt::Horizontal,tr("Cantidad\n"));
    mp->setHeaderData(4,Qt::Horizontal,tr("Fecha\n"));


    //Damos a cada columna la anchura deseada
    ui->tvActividad->setColumnWidth(0,110);
    ui->tvActividad->setColumnWidth(1,120);
    ui->tvActividad->setColumnWidth(2,350);
    ui->tvActividad->setColumnWidth(3,60);
    //Esta dimension se corrige sola, al definir stretch last section
    ui->tvActividad->setColumnWidth(4,50);


    //Para cuando se cliquea sobre un item se marque la fila completa
    ui->tvActividad->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvActividad->setSelectionMode(QAbstractItemView::SingleSelection);

}

void WidgetActividadUsuario::refresh()
{

    //"consultaModificable" es la que modificaremos añadiendole el resto del string
    consultaModificable = consultaActiva;

    //Devuelve la seccion del header que hemos clickeado
    if(header->sortIndicatorSection() == 0)
    {
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaModificable.append(" ORDER BY nombreusuario asc");
            mp->refrescar(consultaModificable);

        }
        else
        {
            consultaModificable.append(" ORDER BY nombreusuario desc");
            mp->refrescar(consultaModificable);

        }
    }


    //Devuelve la seccion del header que hemos clickeado
    if(header->sortIndicatorSection() == 1)
    {
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaModificable.append(" ORDER BY tipomovimiento asc");
            mp->refrescar(consultaModificable);

        }
        else
        {
            consultaModificable.append(" ORDER BY tipomovimiento desc");
            mp->refrescar(consultaModificable);

        }
    }


    //Devuelve la seccion del header que hemos clickeado
    if(header->sortIndicatorSection() == 2)
    {
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaModificable.append(" ORDER BY articulo asc");
            mp->refrescar(consultaModificable);

        }
        else
        {
            consultaModificable.append(" ORDER BY articulo desc");
            mp->refrescar(consultaModificable);

        }
    }

    //Devuelve la seccion del header que hemos clickeado
    if(header->sortIndicatorSection() == 3)
    {
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaModificable.append(" ORDER BY cantidad asc");
            mp->refrescar(consultaModificable);

        }
        else
        {
            consultaModificable.append(" ORDER BY cantidad desc");
            mp->refrescar(consultaModificable);

        }
    }

    //Devuelve la seccion del header que hemos clickeado
    if(header->sortIndicatorSection() == 4)
    {
        header->setSortIndicatorShown(true);

        //Vemos que indicador está puesto
        if(header->sortIndicatorOrder() == Qt::AscendingOrder)
        {
            consultaModificable.append(" ORDER BY fechamov asc");
            mp->refrescar(consultaModificable);

        }
        else
        {
            consultaModificable.append(" ORDER BY fechamov desc");
            mp->refrescar(consultaModificable);

        }
    }

}


void WidgetActividadUsuario::rellenarComboUsuarios()
{
    QStringList nombresUsuarios;

    consultaUsuarios->exec("select nombreusuario from usuarios");

    //Introducimos un campo vacio
    ui->cbUsuario->addItem(tr("Seleccione..."));

    //Rellenamos el combobox
    while(consultaUsuarios->next())
    {
        nombresUsuarios.append(consultaUsuarios->value(0).toString());
    }

    ui->cbUsuario->addItems(nombresUsuarios);
}


void WidgetActividadUsuario::rellenarComboTipoMovimientos()
{
    ui->cbMovimiento->addItem(tr("Seleccione..."));
    //No se puede traducir, porque entonces al comprobar cadenas fallaria
    ui->cbMovimiento->addItem("Insertar");
    ui->cbMovimiento->addItem("Eliminar");

}

void WidgetActividadUsuario::rellenarComboArticulos()
{
    QStringList nombresArticulos;

    consultaArticulos->exec("select descripcion from articulos");

    //Introducimos un campo vacio
    ui->cbArticulo->addItem(tr("Seleccione..."));

    //Rellenamos el combobox
    while(consultaArticulos->next())
    {
        nombresArticulos.append(consultaArticulos->value(0).toString());
    }

    ui->cbArticulo->addItems(nombresArticulos);

}



void WidgetActividadUsuario::on_pbAplicar_clicked()
{

    if(ui->chSinFiltros->isChecked())
    {
        consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
        mp->refrescar(consultaModificable);
        consultaActiva = consultaModificable;
        //Desactivamos para mostrar la consulta y que no aparezca el indicador
        header->setSortIndicatorShown(false);

    }else if(!ui->chFecha->isChecked() && !ui->chMovimiento->isChecked() && !ui->chUsuario->isChecked() && !ui->chArticulo->isChecked()){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);


    }else if(!ui->chFecha->isChecked() && !ui->chMovimiento->isChecked() && !ui->chUsuario->isChecked() && ui->chArticulo->isChecked()){

        if(ui->cbArticulo->currentText() != tr("Seleccione...")){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE articulos.descripcion = '"+ui->cbArticulo->currentText()+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);

        }else
            QMessageBox::critical(this,tr("Error"),tr("Revise los campos marcados"),tr("Aceptar"));


    }else if(!ui->chFecha->isChecked() && !ui->chMovimiento->isChecked() && ui->chUsuario->isChecked() && !ui->chArticulo->isChecked()){

        if(ui->cbUsuario->currentText() != tr("Seleccione...")){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE nombreusuario = '"+ui->cbUsuario->currentText()+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);

        }else
            QMessageBox::critical(this,tr("Error"),tr("Alguno de los campos marcados está vacío"),tr("Aceptar"));


    }else if(!ui->chFecha->isChecked() && !ui->chMovimiento->isChecked() && ui->chUsuario->isChecked() && ui->chArticulo->isChecked()){

        if(ui->cbArticulo->currentText() != tr("Seleccione...") || ui->cbUsuario->currentText() != tr("Seleccione...")){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE nombreusuario = '"+ui->cbUsuario->currentText()+"' and articulos.descripcion = '"+ui->cbArticulo->currentText()+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);

        }else
            QMessageBox::critical(this,tr("Error"),tr("Alguno de los campos marcados está vacío"),tr("Aceptar"));



    }else if(!ui->chFecha->isChecked() && ui->chMovimiento->isChecked() && !ui->chUsuario->isChecked() && !ui->chArticulo->isChecked()){

        if(ui->cbMovimiento->currentText() != tr("Seleccione...")){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE tipomovimiento = '"+ui->cbMovimiento->currentText()+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);

        }else
            QMessageBox::critical(this,tr("Error"),tr("Alguno de los campos marcados está vacío"),tr("Aceptar"));


    }else if(!ui->chFecha->isChecked() && ui->chMovimiento->isChecked() && !ui->chUsuario->isChecked() && ui->chArticulo->isChecked()){

        if(ui->cbMovimiento->currentText() != tr("Seleccione...") || ui->cbArticulo->currentText() != tr("Seleccione...")){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE tipomovimiento = '"+ui->cbMovimiento->currentText()+"' and articulos.descripcion = '"+ui->cbArticulo->currentText()+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);

        }else
            QMessageBox::critical(this,tr("Error"),tr("Alguno de los campos marcados está vacío"),tr("Aceptar"));




    }else if(!ui->chFecha->isChecked() && ui->chMovimiento->isChecked() && ui->chUsuario->isChecked() && !ui->chArticulo->isChecked()){

        if(ui->cbMovimiento->currentText() != tr("Seleccione...") || ui->cbUsuario->currentText() != tr("Seleccione...")){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE tipomovimiento = '"+ui->cbMovimiento->currentText()+"' and nombreusuario = '"+ui->cbUsuario->currentText()+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);

        }else
            QMessageBox::critical(this,tr("Error"),tr("Alguno de los campos marcados está vacío"),tr("Aceptar"));


    }else if(!ui->chFecha->isChecked() && ui->chMovimiento->isChecked() && ui->chUsuario->isChecked() && ui->chArticulo->isChecked()){

        if(ui->cbMovimiento->currentText() != tr("Seleccione...") || ui->cbUsuario->currentText() != tr("Seleccione...") || ui->cbArticulo->currentText() != tr("Seleccione...")){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE tipomovimiento = '"+ui->cbMovimiento->currentText()+"' and nombreusuario = '"+ui->cbUsuario->currentText()+"' and articulos.descripcion = '"+ui->cbArticulo->currentText()+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);

        }else
            QMessageBox::critical(this,tr("Error"),tr("Alguno de los campos marcados está vacío"),tr("Aceptar"));



    }else if(ui->chFecha->isChecked() && !ui->chMovimiento->isChecked() && !ui->chUsuario->isChecked() && !ui->chArticulo->isChecked()){

        //Para la fecha no hace falta poner condicion

        consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE DATE(fechamov) = '"+ui->deFecha->date().toString("yyyy-MM-dd")+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
        mp->refrescar(consultaModificable);
        consultaActiva = consultaModificable;
        //Desactivamos para mostrar la consulta y que no aparezca el indicador
        header->setSortIndicatorShown(false);




    }else if(ui->chFecha->isChecked() && !ui->chMovimiento->isChecked() && !ui->chUsuario->isChecked() && ui->chArticulo->isChecked()){

        if(ui->cbArticulo->currentText() != tr("Seleccione...")){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE DATE(fechamov) = '"+ui->deFecha->date().toString("yyyy-MM-dd")+"' and articulos.descripcion = '"+ui->cbArticulo->currentText()+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);
        }else
            QMessageBox::critical(this,tr("Error"),tr("Alguno de los campos marcados está vacío"),tr("Aceptar"));




    }else if(ui->chFecha->isChecked() && !ui->chMovimiento->isChecked() && ui->chUsuario->isChecked() && !ui->chArticulo->isChecked()){


        if(ui->cbUsuario->currentText() != tr("Seleccione...")){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE DATE(fechamov) = '"+ui->deFecha->date().toString("yyyy-MM-dd")+"' and nombreusuario = '"+ui->cbUsuario->currentText()+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);

        }else
            QMessageBox::critical(this,tr("Error"),tr("Alguno de los campos marcados está vacío"),tr("Aceptar"));



    }else if(ui->chFecha->isChecked() && !ui->chMovimiento->isChecked() && ui->chUsuario->isChecked() && ui->chArticulo->isChecked()){

        if(ui->cbUsuario->currentText() != tr("Seleccione...") || ui->cbArticulo->currentText() != tr("Seleccione...")){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE DATE(fechamov) = '"+ui->deFecha->date().toString("yyyy-MM-dd")+"' and nombreusuario = '"+ui->cbUsuario->currentText()+"' and articulos.descripcion = '"+ui->cbArticulo->currentText()+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);

        }else
            QMessageBox::critical(this,tr("Error"),tr("Alguno de los campos marcados está vacío"),tr("Aceptar"));



    }else if(ui->chFecha->isChecked() && ui->chMovimiento->isChecked() && !ui->chUsuario->isChecked() && !ui->chArticulo->isChecked()){

        if(ui->cbMovimiento->currentText() != tr("Seleccione...")){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE DATE(fechamov) = '"+ui->deFecha->date().toString("yyyy-MM-dd")+"' and tipomovimiento = '"+ui->cbMovimiento->currentText()+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);

        }else
            QMessageBox::critical(this,tr("Error"),tr("Alguno de los campos marcados está vacío"),tr("Aceptar"));


    }else if(ui->chFecha->isChecked() && ui->chMovimiento->isChecked() && !ui->chUsuario->isChecked() && ui->chArticulo->isChecked()){

        if(ui->cbMovimiento->currentText() != tr("Seleccione...") || ui->cbArticulo->currentText() != tr("Seleccione...")){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE DATE(fechamov) = '"+ui->deFecha->date().toString("yyyy-MM-dd")+"' and tipomovimiento = '"+ui->cbMovimiento->currentText()+"' and articulos.descripcion = '"+ui->cbArticulo->currentText()+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);

        }else
            QMessageBox::critical(this,tr("Error"),tr("Alguno de los campos marcados está vacío"),tr("Aceptar"));


    }else if(ui->chFecha->isChecked() && ui->chMovimiento->isChecked() && ui->chUsuario->isChecked() && !ui->chArticulo->isChecked()){

        if(ui->cbMovimiento->currentText() != tr("Seleccione...") || ui->cbUsuario->currentText() != tr("Seleccione...")){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,articulos,usuarios WHERE DATE(fechamov) = '"+ui->deFecha->date().toString("yyyy-MM-dd")+"' and tipomovimiento = '"+ui->cbMovimiento->currentText()+"' and nombreusuario = '"+ui->cbUsuario->currentText()+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);

        }else
            QMessageBox::critical(this,tr("Error"),tr("Alguno de los campos marcados está vacío"),tr("Aceptar"));


    }else if(ui->chFecha->isChecked() && ui->chMovimiento->isChecked() && ui->chUsuario->isChecked() && ui->chArticulo->isChecked()){

        if(ui->cbMovimiento->currentText() != tr("Seleccione...") || ui->cbUsuario->currentText() != tr("Seleccione...") || ui->cbArticulo->currentText() != tr("Seleccione...")){

            consultaModificable = "select usuarios.nombreusuario,actividad.tipomovimiento,articulos.descripcion,actividad.cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios,articulos WHERE DATE(fechamov) = '"+ui->deFecha->date().toString("yyyy-MM-dd")+"' and tipomovimiento = '"+ui->cbMovimiento->currentText()+"' and nombreusuario = '"+ui->cbUsuario->currentText()+"' and articulos.descripcion = '"+ui->cbArticulo->currentText()+"' and usuarios.dni = actividad.usuario and actividad.articulo = articulos.codigoean";
            mp->refrescar(consultaModificable);
            consultaActiva = consultaModificable;
            //Desactivamos para mostrar la consulta y que no aparezca el indicador
            header->setSortIndicatorShown(false);

        }else
            QMessageBox::critical(this,tr("Error"),tr("Alguno de los campos marcados está vacío"),tr("Aceptar"));


    }

}


void WidgetActividadUsuario::on_pbBorrar_clicked()
{
    QMessageBox msgBox(this);

    msgBox.setWindowTitle(tr("Eliminar"));
    msgBox.setText(tr("Eliminar actividad"));
    msgBox.setInformativeText(tr("¿Está seguro de eliminar toda la actividad del programa hasta la fecha?"));
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.addButton(tr("Si"),QMessageBox::AcceptRole);

    //Guardamos el boton en una variable para despues hacerlo por defecto
    QPushButton *pb = msgBox.addButton(tr("No"),QMessageBox::RejectRole);

    //Por defecto el boton que saldra sombreado
    msgBox.setDefaultButton(pb);

    //Devuelve la respuesta que hayamos dado, si contesta que si, borramos
    if(!msgBox.exec()){
        consultaUsuarios->exec("DELETE FROM actividad");
        consultaModificable = "select nombreusuario,tipomovimiento,articulo, cantidad, DATE_FORMAT(fechamov, '%d/%m/%Y %H:%i:%s') from actividad,usuarios WHERE and usuarios.dni = actividad.usuario";
        mp->refrescar(consultaModificable);
        consultaActiva = consultaModificable;
    }

}


/*
void WidgetActividadUsuario::on_pushButton_clicked()
{
    //ui->deFecha->date().day();
    //ui->deFecha->date().month();
    //ui->deFecha->date().year();

    QDate a(ui->deFecha->date().year(),ui->deFecha->date().month(),ui->deFecha->date().day());

}*/


void WidgetActividadUsuario::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}


WidgetActividadUsuario::~WidgetActividadUsuario()
{
    delete ui;
}
