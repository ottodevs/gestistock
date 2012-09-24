#include "widgetrestaurarcopiaseguridad.h"
#include "ui_widgetrestaurarcopiaseguridad.h"

WidgetRestaurarCopiaSeguridad::WidgetRestaurarCopiaSeguridad(WindowPantallaOpcionesUsuario *wpo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetRestaurarCopiaSeguridad)
{
    ui->setupUi(this);

    //Titulo
    this->setWindowTitle(tr("Restaurar Copia de Seguridad"));

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));

    //Bloqueamos el boton de maximizar
    this->setWindowFlags(windowFlags() ^ Qt::WindowMaximizeButtonHint);

    wPantalla = wpo;

    ui->pbRestaurar->setEnabled(false);
}


void WidgetRestaurarCopiaSeguridad::on_pbExaminar_clicked()
{
    QString destino = QFileDialog::getOpenFileName(this, tr("Cargar Fichero"),QDir::currentPath(),tr("Base de datos (*.sql)"));

    ui->leOrigen->setText(destino);

    if(destino != "")
        ui->pbRestaurar->setEnabled(true);

}

void WidgetRestaurarCopiaSeguridad::on_pbRestaurar_clicked()
{
    QMessageBox msgBox(this);
    //Reserva de memoria
    pdn = new QProgressDialogNew();

    msgBox.setWindowTitle(tr("Cerrar"));
    msgBox.setText(tr("Restaurar Copia de Seguridad                                              "));
    msgBox.setInformativeText(tr("¿Está seguro de restaurar la copia de seguridad?. Esto cerrará la sesión actual"));
    msgBox.setIcon(QMessageBox::Question);
    msgBox.addButton(tr("Si"),QMessageBox::AcceptRole);

    //Guardamos el boton en una variable para despues hacerlo por defecto
    QPushButton *pb = msgBox.addButton(tr("No"),QMessageBox::RejectRole);
    //Por defecto el boton que saldra sombreado
    msgBox.setDefaultButton(pb);


    //Devuelve la respuesta que hayamos dado...
    if(!msgBox.exec())
    {
        //Configuracion del QProgressDialogNew
        pdn->setParent(this);
        pdn->setLabelText(tr("Procesando..."));
        pdn->setCancelButtonText(0);
        pdn->setRange(0,0);
        pdn->setFixedSize(200,60);

        QStringList args;
        args << "-uroot" << "-p1234" << "bdgestistock";

        pdn->setWindowModality(Qt::WindowModal);

        //Quitamos la barra y ponemos el dialogo en primer plano
        pdn->setWindowFlags(Qt::Tool | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

        procesoRestauracion = new QProcess;

        procesoRestauracion->setStandardInputFile(ui->leOrigen->text());
        procesoRestauracion->start("mysql", args);

        connect(procesoRestauracion,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(finalizacion(int,QProcess::ExitStatus)));

        pdn->exec();
    }
}


void WidgetRestaurarCopiaSeguridad::finalizacion(int, QProcess::ExitStatus exitStatus)
{
    //Ocultamos la barra de progreso
    pdn->setVisible(false);

    if(exitStatus == QProcess::CrashExit)
            QMessageBox::critical(this,tr("Error"),tr("Proceso de restauración fallido"),tr("Cerrar"));
    else
            QMessageBox::information(this,tr("Información"),tr("Proceso completado"),tr("Aceptar"));

    //Para cerrar pantalla principal y omitir el dialogo
    wPantalla->confirmarCierre = true;
    wPantalla->close();

}


WidgetRestaurarCopiaSeguridad::~WidgetRestaurarCopiaSeguridad()
{
    delete ui;
}

void WidgetRestaurarCopiaSeguridad::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}
