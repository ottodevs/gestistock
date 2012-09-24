#include <QtGui/QApplication>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QTimer>
#include <QTranslator>
#include <QDebug>

#include "camerawidget.h"
#include "windowcargardatos.h"

CvCapture *camara;

int main(int argc, char *argv[])
{
    //QString locale = QLocale::system().name();
    QApplication a(argc, argv);
    WindowCargarDatos wC;
    QSize size = wC.size();
    QDesktopWidget *d = QApplication::desktop();

    //Creamos la captura
    camara = cvCreateCameraCapture(0);

    //Situamos la ventana en el centro de la pantalla
    wC.move((d->width()/2) - (size.width()/2),(d->height()/2) - (size.height()/2));

    //Mostramos la ventana
    wC.show();

    //Lanzamos la aplicacion
    int retval = a.exec();

    //Cortamos la captura
    cvReleaseCapture(&camara);

return retval;
}
