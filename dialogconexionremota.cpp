#include "dialogconexionremota.h"
#include "ui_dialogconexionremota.h"

DialogConexionRemota::DialogConexionRemota(QSqlDatabase *bd, WindowCargarDatos *wcd, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConexionRemota)
{
    ui->setupUi(this);

    pwcd = wcd;

    this->setWindowTitle(tr("Conexión Remota"));
    this->setWindowIcon(QIcon(":/imagenes/irkick.png"));
    this->setModal(true);

    this->baseDatos = bd;

    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);



    ui->lePuerto->setValidator(new QIntValidator(0,99999,this));
    //NOTA: No se puede crear mas de un objeto QMessageBox como miembros de una clase
}


void DialogConexionRemota::conectBD()
{
    QMessageBox msgBox(this);
    QMessageBox msg(this);

    //Cerramos por si estan abiertas
    baseDatos->close();

    msgBox.setWindowTitle(tr("Conectando..."));
    msgBox.setText(tr("Realizando conexión...                     "));
    msgBox.setInformativeText(tr("Espere..."));
    msgBox.setIcon(QMessageBox::Information);
    //Sin botones
    msgBox.setStandardButtons(0);
    msgBox.setModal(true);
    msgBox.setWindowModality(Qt::WindowModal);
    msgBox.setWindowFlags(Qt::Tool | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    //Mostramos el mensaje
    msgBox.show();

    //Seguimos procesando los eventos de la aplicacion
    qApp->processEvents();
    qApp->sendPostedEvents();


    //Abro la base de datos comprobando si estan disponibles sus respectivos drivers
    if (QSqlDatabase::isDriverAvailable("QMYSQL"))
    {

        if(ui->leHost->text() != "" && !ui->leHost->text().simplified().isEmpty())
        {
            baseDatos->setHostName(ui->leHost->text());
            baseDatos->setPort(ui->lePuerto->text().toInt());
            baseDatos->setDatabaseName(ui->leBD->text());
            baseDatos->setUserName(ui->leNombreUsuario->text());
            baseDatos->setPassword(ui->lePass->text());

            //Abrimos la BD
            if(baseDatos->open())
            {
                //Cerramos el mensaje anterior
                msgBox.setVisible(false);

                //Preparamos el nuevo
                msg.setWindowTitle(tr("Conectado"));
                msg.setText(tr("Conexion efectuada                  "));
                msg.setInformativeText(tr("Pulse aceptar para volver al login"));
                msg.setIcon(QMessageBox::Information);
                msg.addButton(tr("Aceptar"),QMessageBox::AcceptRole);

                //Ejecutamos el mensaje esta vez con exec para parar los eventos posteriores
                msg.exec();

                pwcd->consultarIdioma();

                //Activamos la accion desconectar
                pwcd->botonDesconectar();

                //Cerramos la ventana
                this->close();

            }else{

                //Cerramos el mensaje anterior
                msgBox.setVisible(false);

                baseDatos->setHostName("localhost");
                baseDatos->setDatabaseName("bdgestistock");
                baseDatos->setPort(3306);
                baseDatos->setUserName("usergestistock");
                baseDatos->setPassword("1234");

                if(baseDatos->open())
                {
                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("No se ha podido conectar con el servidor              "));
                    msg.setInformativeText(tr("Reconectado a localhost"));
                    msg.setIcon(QMessageBox::Critical);
                    msg.addButton(tr("Aceptar"),QMessageBox::AcceptRole);

                    //Ejecutamos el mensaje esta vez con exec para parar los eventos posteriores
                    msg.exec();

                    //Cerramos la ventana
                    this->close();

                }else{

                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("La reconexión al servidor no ha sido posible              "));
                    msg.setInformativeText(tr("Desconectado"));
                    msg.setIcon(QMessageBox::Critical);
                    msg.addButton(tr("Aceptar"),QMessageBox::AcceptRole);

                    //Ejecutamos el mensaje bloqueando los eventos posteriores
                    msg.exec();
                }

            }

        }else{
            msgBox.setVisible(false);
            QMessageBox::critical(this,tr("Error"),tr("El nombre de host no es válido"),tr("Aceptar"));
        }

    }else
        msgBox.setVisible(false);

}


void DialogConexionRemota::on_pbConectar_clicked()
{
    //Establecemos una nueva conexión
    conectBD();
}

void DialogConexionRemota::on_checkBox_clicked(bool checked)
{
    if(checked == true)
    {
        ui->lePuerto->setText("3306");
        ui->lePuerto->setEnabled(false);
    }else{
        ui->lePuerto->clear();
        ui->lePuerto->setEnabled(true);
    }

}

void DialogConexionRemota::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}


DialogConexionRemota::~DialogConexionRemota()
{
    delete ui;
}


