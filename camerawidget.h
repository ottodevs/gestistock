/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see http://www.gnu.org/licenses/.

        Copyright (C) 2012 Manuel Trinidad García
*/


#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QImage>
#include <QDebug>
#include <opencv/cv.h>


/**
 * @brief Clase que permite la conversión de la imagen de la cámara a un formato legible por un QLabel.
 *
 */
class CameraWidget : public QWidget
{
    Q_OBJECT
    
public:
/**
 * @brief Constructor de CameraWidget.
 *
 * @param parent Puntero a un QWidget padre
 */
    CameraWidget(QWidget *parent = 0);
    /**
     * @brief Destructor de la clase CameraWidget
     *
     */
    ~CameraWidget();
    /**
     * @brief Función que convierte un IplImage a QPixmap.
     *
     * @param Puntero al objeto que devuelve la cámara
     * @return QPixmap Formato al que convierte esta función
     */
    QPixmap toPixmap(IplImage *);
    /**
     * @brief Coloca una IplImage en un frame, en este caso un QLabel
     *
     * @param Objeto a introducir en el frame
     */
    void putFrame(IplImage *);
    
private:
    QLabel *imageLabel; /**< TODO */
    QGridLayout *layout; /**< TODO */
    QImage image; /**< TODO */
};

#endif // CAMERAWIDGET_H
