#include "widgetcopiaseguridad.h"
#include "ui_widgetcopiaseguridad.h"

WidgetCopiaSeguridad::WidgetCopiaSeguridad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetCopiaSeguridad)
{
    ui->setupUi(this);

    //Titulo
    this->setWindowTitle(tr("Copia de Seguridad"));
    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));

    ui->pbCrear->setEnabled(false);

}

void WidgetCopiaSeguridad::on_pbCrear_clicked()
{
        //Reserva de memoria
        pdn = new QProgressDialogNew();
        procesoCopia = new QProcess();

        //Configuracion del QProgressDialogNew
        pdn->setParent(this);
        pdn->setLabelText(tr("Procesando..."));
        pdn->setCancelButtonText(0);
        pdn->setRange(0,0);
        pdn->setFixedSize(200,60);


        QStringList args;

        //args << "-uroot" << "-p1234" << "bdgestistock";
        //args << "--opt" << "--password=1234" << "--user=usergestistock" << "bdgestistock";
        args << "--opt" << "--password=1234" << "--user=usergestistock" << "bdgestistock";

        pdn->setWindowModality(Qt::WindowModal);

        //Quitamos la barra y ponemos el dialogo en primer plano
        pdn->setWindowFlags(Qt::Tool | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

        procesoCopia->setStandardOutputFile(ui->leDestino->text());

        //Importante, en mi pc no tengo que poner ruta porque la tengo en el path
        //procesoCopia->setWorkingDirectory("C:/MySQL/bin");

        //qDebug() << procesoCopia->workingDirectory();

        procesoCopia->start("mysqldump.exe",args);

        //Cuando haya terminado llama al slot copiaExitosa
        connect(procesoCopia,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(finalizado(int,QProcess::ExitStatus)));

        pdn->exec();
}

void WidgetCopiaSeguridad::on_pbExaminar_clicked()
{
    QString destino = QFileDialog::getSaveFileName(this, tr("Guardar Copia"),QDir::currentPath(),tr("Base de datos (*.sql)"));

    ui->leDestino->setText(destino);

    if(destino != "")
        ui->pbCrear->setEnabled(true);

}

void WidgetCopiaSeguridad::finalizado(int, QProcess::ExitStatus exitStatus)
{
    pdn->setVisible(false);

    if(exitStatus == QProcess::CrashExit)
        QMessageBox::critical(this,tr("Error"),tr("Proceso de copia fallido"),tr("Aceptar"));
    else
        QMessageBox::information(this,tr("Copia de Seguridad"),tr("Proceso completado"),tr("Aceptar"));
}

void WidgetCopiaSeguridad::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}


WidgetCopiaSeguridad::~WidgetCopiaSeguridad()
{
    delete ui;
}

