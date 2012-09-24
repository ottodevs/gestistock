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


#ifndef WIDGETALTAUSUARIO_H
#define WIDGETALTAUSUARIO_H

#include <QWidget>
#include <QSqlQuery>
#include <QBuffer>
#include <QDebug>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include <QMdiArea>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QFileDialog>
#include <QTranslator>

#include "camerawidget.h"
#include "dialogwebcam.h"

namespace Ui {
class WidgetAltaUsuario;
}

/**
 * @brief Widget que permite el registro de un nuevo usuario.
 *
 */
class WidgetAltaUsuario : public QWidget
{
    Q_OBJECT

protected:
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicación, o del sistema, procede a la traducción de todos los elementos.
     *
     * @param event Evento del sistema
     */
     void changeEvent(QEvent*);

public:
/**
 * @brief Constructor del Widget.
 *
 * @param mdiArea Puntero al QMdiArea de la ventana principal
 * @param parent Puntero a la ventana padre
 */
     WidgetAltaUsuario(QMdiArea *mdiArea, QWidget *parent=0);
    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetAltaUsuario();
    
private slots:
    /**
     * @brief Slot que guarda el usuario en el sistema.
     *
     */
    void on_pbGuardar_clicked();
    /**
     * @brief Slot que cierra el Widget.
     *
     */
    void on_pbSalir_clicked();
    /**
     * @brief Slot que permite activar la cámara en pantalla.
     *
     */
    void on_pbActivarCamara_clicked();
    /**
     * @brief Slot que permite buscar un archivo de foto y cargarlo en un QLabel.
     *
     */
    void on_pbExaminar_clicked();


private:
    Ui::WidgetAltaUsuario *ui; /**< TODO */
    QString rutaImagen; /**< TODO */
    QSqlQuery *insertar; /**< TODO */
    QSqlQuery *cn1; /**< TODO */
    QByteArray ba; /**< TODO */
    //QBuffer buffer;
    bool fotoCargada; /**< TODO */
    QMdiArea *mdi; /**< TODO */
    int contadorFoto; /**< TODO */
    QLabel *fondo; /**< TODO */
    QPixmap a; /**< TODO */
    DialogWebCam *wb; /**< TODO */
    QTranslator translator; /**< TODO */



};

#endif // WidgetAltaUsuario_H
