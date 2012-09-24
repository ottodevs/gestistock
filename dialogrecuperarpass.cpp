#include "dialogrecuperarpass.h"
#include "ui_dialogrecuperarpass.h"


DialogRecuperarPass::DialogRecuperarPass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRecuperarPass)
{
    ui->setupUi(this);

    //Titulo
    this->setWindowTitle(tr("Recuperar contraseña"));

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/password.png"));

    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);


    //Ponemos la ventana como modal
    this->setModal(true);

    //Reserva de memoria
    consultaUsuario = new QSqlQuery;
}


void DialogRecuperarPass::on_pbEnviar_clicked()
{
    //Creamos la consulta
    consultaUsuario->exec("SELECT AES_DECRYPT(password,'MyPass'), correo FROM usuarios WHERE nombreusuario = '"+ui->leUsuario->text()+"' ");

    //Si existe...enviamos la contraseña al correo deseado
    if(consultaUsuario->first())
    {
        Smtp *newMail  = new Smtp("remoteserver","username","pass");
        newMail->Send("from@address.com","to@address.com"," Your Subject","My body text");

        this->close();

    }else
        QMessageBox::critical(this,tr("Error"),tr("El usuario no existe"),tr("Aceptar"));


}


void DialogRecuperarPass::on_pbCancelar_clicked()
{
    //Cerramos la ventana
    this->close();
}

DialogRecuperarPass::~DialogRecuperarPass()
{
    delete ui;
}

void DialogRecuperarPass::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}
