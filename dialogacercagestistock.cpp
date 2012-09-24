#include "dialogacercagestistock.h"
#include "ui_dialogacercagestistock.h"

DialogAcercaGestiStock::DialogAcercaGestiStock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAcercaGestiStock)
{
    ui->setupUi(this);

    //Ventana modal
    this->setModal(true);
    //Titulo de la ventana
    this->setWindowTitle(tr("Acerca de GestiStock Software"));
    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logoSolo.png"));
    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
}

void DialogAcercaGestiStock::on_pbCerrar_clicked()
{
    this->close();
}

void DialogAcercaGestiStock::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}

DialogAcercaGestiStock::~DialogAcercaGestiStock()
{
    delete ui;
}


