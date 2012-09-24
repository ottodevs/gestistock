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


#ifndef DIALOGMODIFICARUSUARIO_H
#define DIALOGMODIFICARUSUARIO_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>
#include <QFileDialog>
#include <QBuffer>
#include <QMessageBox>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QTranslator>
#include "widgetverusuarios.h"
#include "qsqlqueryusuarios.h"
#include "camerawidget.h"
#include "dialogwebcam.h"

class WidgetVerUsuarios;


namespace Ui {
class DialogModificarUsuario;
}

/**
 * @brief Diálogo que permite la modificación de los datos de un usuario.
 *
 */
class DialogModificarUsuario : public QDialog
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
     * @brief Constructor del diálogo.
     *
     * @param user Usuario del que se realiza la modificación
     * @param clave Clave primaria del usuario (DNI)
     * @param consulta Consulta activa del model usuarios
     * @param mp Model de usuarios
     * @param parent Puntero a la ventana padre
     */
    explicit DialogModificarUsuario(QString user, QString clave, QString consulta, QSqlQueryUsuarios *mp, QWidget *parent = 0);
    /**
     * @brief Constructor del diálogo.
     *
     * @param usuario Usuario que se modifica
     * @param parent Puntero a la ventana padre
     */
    explicit DialogModificarUsuario(QString usuario, QWidget *parent = 0);
    /**
     * @brief Destructor del diálogo.
     *
     */
    ~DialogModificarUsuario();
    
private slots:
    /**
     * @brief Slot que cierra la ventana.
     *
     */
    void on_pbSalir_clicked();
    /**
     * @brief Slot que muestra la cámara en pantalla.
     *
     */
    void on_pbCambiarImagen_clicked();
    /**
     * @brief Slot que permite cambiar la imagen del usuario a partir de un archivo.
     *
     */
    void on_pbGuardar_clicked();
    /**
     * @brief Slot que guarda las modificaciones a un usuario.
     *
     */
    void on_pbCamara_clicked();

    /**
     * @brief Slot que elimina un usuario.
     *
     */
    void on_pbEliminar_clicked();

private:
    Ui::DialogModificarUsuario *ui; /**< TODO */
    QSqlQuery *cn; /**< TODO */
    QString rutaImagen; /**< TODO */
    QString nombreUsuario; /**< TODO */
    QPixmap *imagenArticulo; /**< TODO */
    QSqlQuery *actualizar; /**< TODO */
    QSqlQueryUsuarios *model; /**< TODO */
    QString consultaUsuarios; /**< TODO */
    bool imagenActualizada; /**< TODO */
    DialogWebCam *wb; /**< TODO */
    QTranslator translator; /**< TODO */
    QString usuarioActivo; /**< TODO */
};

#endif // DIALOGMODIFICARUSUARIO_H
