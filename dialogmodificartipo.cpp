#include "dialogmodificartipo.h"
#include "ui_dialogmodificartipo.h"

DialogModificarTipo::DialogModificarTipo(QString nombre, QString consulta, QSqlQueryTipos *modelTipos, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogModificarTipo)
{
    ui->setupUi(this);

    //Titulo de la ventana
    this->setWindowTitle(tr("Modificar Tipo"));

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));

    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);

    //Ventana modal
    this->setModal(true);

    queryTipos = new QSqlQuery;

    //Guardamos el model
    model = modelTipos;

    //Guardamos la consulta
    consultaActiva = consulta;

    //Guardamos el nombre
    nombreTipo = nombre;

    queryTipos->exec("SELECT nombretipo, descripcion FROM tipoproducto WHERE nombretipo = '"+nombreTipo+"' ");
    queryTipos->first();

    //Rellenamos los campos
    ui->leNombre->setText(queryTipos->value(0).toString());
    ui->teComentario->setText(queryTipos->value(1).toString());

    //Bloqueamos el nombre que es la clave primaria
    ui->leNombre->setEnabled(false);

}


void DialogModificarTipo::on_pbCancelar_clicked()
{
    this->close();
}


void DialogModificarTipo::on_pbGuardar_clicked()
{
    QSqlQuery query;

    if(ui->teComentario->document()->isModified())
    {

        query.prepare("UPDATE tipoproducto SET descripcion = :descripcion WHERE nombretipo = '"+ui->leNombre->text()+"'");
        query.bindValue(":descripcion",ui->teComentario->toPlainText());

        if(query.exec())
        {
            QMessageBox::information(this,tr("Información"),tr("El tipo ha sido modificado"),tr("Aceptar"));
            this->close();
        }

    }else
        QMessageBox::information(this,tr("Información"),tr("No ha modificado nada"),tr("Aceptar"));

}


void DialogModificarTipo::on_pbEliminar_clicked()
{
    QSqlQuery query;
    QMessageBox msgBox(this);

    msgBox.setWindowTitle(tr("Eliminar"));
    msgBox.setText(tr("Eliminar tipo                             "));
    msgBox.setInformativeText(tr("¿Está seguro de que desea eliminar el tipo?"));
    msgBox.setIcon(QMessageBox::Question);
    msgBox.addButton(tr("Si"),QMessageBox::AcceptRole);

    //Guardamos el boton en una variable para despues hacerlo por defecto
    QPushButton *pb = msgBox.addButton(tr("No"),QMessageBox::RejectRole);

    //Por defecto el boton que saldra sombreado
    msgBox.setDefaultButton(pb);

    //Si la respuesta es si...
    if(!msgBox.exec())
    {
        query.prepare("DELETE FROM tipoproducto WHERE tipoproducto.nombretipo =  '"+ui->leNombre->text()+"' ");

        if(query.exec())
        {   //Refrescamos el modelo
            model->refrescar(consultaActiva);
            QMessageBox::information(this,tr("Información"),tr("El tipo ha sido eliminado"),tr("Aceptar"));
            this->close();
        }else
            QMessageBox::critical(this,tr("Error"),tr("No se ha podido eliminar el tipo, compruebe su actividad"),tr("Aceptar"));
    }
}

void DialogModificarTipo::changeEvent(QEvent* event)
{
    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}

void DialogModificarTipo::on_teComentario_textChanged()
{
    if(ui->teComentario->toPlainText().length() > 250)
        ui->teComentario->textCursor().deletePreviousChar();
}


DialogModificarTipo::~DialogModificarTipo()
{
    delete ui;
}
