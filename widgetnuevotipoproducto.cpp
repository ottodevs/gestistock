#include "widgetnuevotipoproducto.h"
#include "ui_widgetnuevotipoproducto.h"

WidgetNuevoTipoProducto::WidgetNuevoTipoProducto(QMdiArea *mdiArea,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetNuevoTipoProducto)
{
    ui->setupUi(this);

    //Titulo
    this->setWindowTitle(tr("Nuevo Tipo"));

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));

    //Guardamos el puntero
    mdi = mdiArea;

    //Reserva de memoria
    insertarTipo = new QSqlQuery;
    comprobar = new QSqlQuery;

}

void WidgetNuevoTipoProducto::on_pbCancelar_clicked()
{
    mdi->closeActiveSubWindow();
}

void WidgetNuevoTipoProducto::on_pbGuardar_clicked()
{
    //Consultamos la existencia del tipo producto
    comprobar->exec("select nombretipo from tipoproducto where nombretipo = '"+ui->leNombre->text()+"' ");

    //Preparamos la consulta
    insertarTipo->prepare("insert into tipoproducto VALUES ('"+ui->leNombre->text()+"', '"+ui->teComentario->toPlainText()+"')");

    //Comprobamos si el tipo ya existe
    if(ui->leNombre->text().isEmpty())
        QMessageBox::critical(this,tr("Error"),tr("El nombre está vacío"),tr("Aceptar"));
    else if(comprobar->size() == 0 && insertarTipo->exec()){
        QMessageBox::information(this,tr("Información"),tr("Tipo insertado correctamente"),tr("Aceptar"));
        mdi->closeActiveSubWindow();
    }else
        QMessageBox::critical(this,tr("Error"),tr("Ya existe un tipo con ese nombre"),tr("Aceptar"));
}

void WidgetNuevoTipoProducto::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}


void WidgetNuevoTipoProducto::on_teComentario_textChanged()
{
    if(ui->teComentario->toPlainText().length() > 250)
        ui->teComentario->textCursor().deletePreviousChar();
}


WidgetNuevoTipoProducto::~WidgetNuevoTipoProducto()
{
    delete ui;
}

