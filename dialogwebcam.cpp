#include "dialogwebcam.h"
#include "ui_dialogwebcam.h"

//Variable externa
extern CvCapture *camara;

DialogWebCam::DialogWebCam(QLabel *fondo, bool *fotoCargada, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWebCam)
{
    ui->setupUi(this);

    //Icono
    setWindowIcon(QIcon(":/imagenes/logo.png"));


    labelFondo = fondo;
    fotoTomada = false;


    //Recogemos el puntero a fotoCargada
    fotoLoad = fotoCargada;

    //La colocamos como dialog modal
    setModal(true);

    //Quitamos la barra y ponemos el dialogo en primer plano
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint);


    //Comprobamos si hay captura...
    if(camara != NULL)
    {
        //Copiamos el Widget que despues incrustaremos en el layout
        m_cvwidget = new CameraWidget(this);

        //Incrustamos el video en el layout
        ui->layoutCamara->addWidget(m_cvwidget);

        //Inicia temporizador
        id = startTimer(1000/16);

    }
    else
        QMessageBox::critical(this,tr("Error"),tr("Cámara no disponible"),tr("Aceptar"));

}

bool DialogWebCam::disponible()
{
    if(camara != NULL)
        return true;
    else
        return false;
}

void DialogWebCam::on_pbSalir_clicked()
{
    this->close();
}


//Coloca un nuevo frame en el widget
void DialogWebCam::timerEvent(QTimerEvent*)
{
    IplImage *image = cvQueryFrame(camara);
    m_cvwidget->putFrame(image);
}

//Congelamos la imagen parando el video
void DialogWebCam::on_pbTomarFoto_clicked()
{
     IplImage *imagen = cvQueryFrame(camara);
     foto = m_cvwidget->toPixmap(imagen);

     //Paramos temporizador
     killTimer(id);
     fotoTomada = true;
}

//Descongelamos la imagen reiciciando el video
void DialogWebCam::on_pbLimpiar_clicked()
{
    if(fotoTomada)
    {
        //Inicia temporizador
        id = startTimer(0);
        //Eliminamo el indicador de foto tomada
        fotoTomada = false;
    }
}


void DialogWebCam::on_pbAceptar_clicked()
{
    if(fotoTomada)
    {
        //Colocamos la imagen en el QLabel
        labelFondo->setPixmap(foto);
        //Escalamos la imagen para hacerla proporcional al QLabel
        labelFondo->setScaledContents(true);
        (*fotoLoad) = true;
    }

    this->close();
}


void DialogWebCam::reject()
{
    this->close();
}

//Si cerramos la ventana...
void DialogWebCam::closeEvent(QCloseEvent *ev)
{
        //Si el usuario ha cerrado la ventana...
        if(ev->isAccepted())
        {
            //Para temporizador
            killTimer(id);
        }

}


DialogWebCam::~DialogWebCam()
{
    delete ui;
}

void DialogWebCam::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}




