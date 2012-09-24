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

        Copyright (C) 2012 Manuel Trinidad Garc�a
*/


#ifndef DIALOGWEBCAM_H
#define DIALOGWEBCAM_H

#include <QDialog>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTranslator>
#include "camerawidget.h"

namespace Ui {
class DialogWebCam;
}

/**
 * @brief Di�logo que muestra la c�mara en pantalla.
 *
 */
class DialogWebCam : public QDialog
{
    Q_OBJECT

protected:
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicaci�n, o del sistema, procede a la traducci�n de todos los elementos.
     *
     * @param event Evento del sistema
     */
    void changeEvent(QEvent*);

public:
    /**
     * @brief Constructor del di�logo.
     *
     * @param fondo Puntero al QLabel de la ventana en la que se introducir� la foto
     * @param fotoCargada Puntero al indicador que dice si se ha cargado una foto
     * @param parent Puntero a la ventana padre
     */
    explicit DialogWebCam(QLabel *fondo, bool *fotoCargada, QWidget *parent = 0);
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicaci�n, o del sistema, procede a la traducci�n de todos los elementos.
     *
     * @param event Evento del sistema
     */
    void closeEvent(QCloseEvent *ev);
    /**
     * @brief Evento de la tecla ESC.
     *
     */
    void reject();
    /**
     * @brief Indicador que dice si la c�mara se encuentra disponible.
     *
     * @return bool
     */
    bool disponible();
    /**
     * @brief Destructor del di�logo.
     *
     */
    ~DialogWebCam();
    
protected:
    /**
     * @brief Crea un objeto de evento con informaci�n espec�fica relacionada con los eventos timer.
     *
     * @param Objeto a partir del cual crea el objeto de evento
     */
    void timerEvent(QTimerEvent*);

private slots:
    /**
     * @brief Slot que cierra el di�logo.
     *
     */
    void on_pbSalir_clicked();

    /**
     * @brief Slot que captura una foto de la c�mara.
     *
     */
    void on_pbTomarFoto_clicked();

    /**
     * @brief Slot que permite volver a tomar otra foto, desbloqueando la anterior de la pantalla.
     *
     */
    void on_pbLimpiar_clicked();

    /**
     * @brief Slot que permite la introducci�n de la foto tomada en el QLabel de la pantalla padre.
     *
     */
    void on_pbAceptar_clicked();

private:
    Ui::DialogWebCam *ui; /**< TODO */
    CameraWidget *m_cvwidget; /**< TODO */
    QLabel *labelFondo; /**< TODO */
    int id; /**< TODO */
    bool *fotoLoad; /**< TODO */
    QPixmap foto; /**< TODO */
    bool fotoTomada; /**< TODO */
    QTranslator translator; /**< TODO */
};

#endif // DialogWebCam_H
