#include "camerawidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
    QWidget(parent)
{

    layout = new QGridLayout;
    imageLabel = new QLabel;

    //Fijamos un tamaño al qlabel para que no haya problemas con "no foto"
    //imageLabel->setFixedSize(180,148);

    QImage im(100, 100, QImage::Format_RGB32);

    image = im;

    //Metemos en el layout el QLabel
    layout->addWidget(imageLabel);


    //Pixelamos
    for (int x = 0; x < 100; x ++)
        for (int y =0; y < 100; y++)
            image.setPixel(x,y,qRgb(x, y, y));

    imageLabel->setPixmap(QPixmap::fromImage(image));

    setLayout(layout);
}

void CameraWidget::putFrame(IplImage *image)
{
   //Escalamos el contenido para hacerlo proporcional al tamaño del QLabel
   imageLabel->setScaledContents(true);
   //Colocamos la imagen en el QLabel
   imageLabel->setPixmap(toPixmap(image));
}



//Convertimos a QPixmap para poder meterla en el QLabel
QPixmap CameraWidget::toPixmap(IplImage *cvimage) {
    int cvIndex, cvLineStart;

    switch (cvimage->depth) {
        case IPL_DEPTH_8U:
            switch (cvimage->nChannels) {
                case 3:
                    if ( (cvimage->width != image.width()) || (cvimage->height != image.height()) ) {
                        QImage temp(cvimage->width, cvimage->height, QImage::Format_RGB32);
                        image = temp;
                    }
                    cvIndex = 0; cvLineStart = 0;
                    for (int y = 0; y < cvimage->height; y++) {
                        unsigned char red,green,blue;
                        cvIndex = cvLineStart;
                        for (int x = 0; x < cvimage->width; x++) {
                            red = cvimage->imageData[cvIndex+2];
                            green = cvimage->imageData[cvIndex+1];
                            blue = cvimage->imageData[cvIndex+0];

                            image.setPixel(x,y,qRgb(red, green, blue));
                            cvIndex += 3;
                        }
                        cvLineStart += cvimage->widthStep;
                    }
                    break;
                default:
                    qWarning("El número de canales no es soportado\n");
                    break;
            }
            break;
        default:
            qWarning("Este tipo de IplImage no es implementado en QOpenCVWidget\n");
            break;
    }

    //Devolvemos la conversion a QPixmap
    return QPixmap::fromImage(image);
}

CameraWidget::~CameraWidget()
{
    delete imageLabel;
    delete layout;
}
