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


#ifndef DIALOGMODIFICARARTICULO_H
#define DIALOGMODIFICARARTICULO_H

#include <QDialog>
#include <QSqlQuery>
#include <QCloseEvent>
#include <QPixmap>
#include <QFileDialog>
#include <QBuffer>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <map>
#include <QTranslator>

#include "windowverarticulos.h"
#include "dialogwebcam.h"
#include "camerawidget.h"

class WindowVerArticulos;


namespace Ui {
    class DialogModificarArticulo;
}

/**
 * @brief Dialog que permite la modificación de un artículo.
 *
 */
class DialogModificarArticulo : public QDialog
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
     * @param user Usuario que modifica el artículo
     * @param codEan Codigo de barras del artículo a modificar
     * @param consulta Consulta de la tabla artículos, a partir de la cual se refrescará dicha tabla
     * @param mp Model artículos
     * @param parent Puntero a la ventana padre
     */
    explicit DialogModificarArticulo(QString user, QString codEan, QString consulta, QSqlQueryArticulos *mp, QWidget *parent = 0);
    /**
     * @brief Destructor del diálogo.
     *
     */
    ~DialogModificarArticulo();


private slots:

    /**
     * @brief Slot que cierra el diálogo.
     *
     */
    void on_pbCancelar_clicked();

    /**
     * @brief Slot que guarda los cambios al artículo
     *
     */
    void on_pbAceptar_clicked();

    /**
     * @brief Slot que cambia la imagen del artículo
     *
     */
    void on_pbCambiarImagen_clicked();

    /**
     * @brief Slot que muestra la pantalla de la cámara
     *
     */
    void on_pbCamera_clicked();

    /**
     * @brief Slot que se activa cuando cambia el texto del textEdit
     *
     */
    void on_teComentario_textChanged();

    /**
     * @brief Slot que elimina el artículo
     *
     */
    void on_pbEliminar_clicked();

private:
    Ui::DialogModificarArticulo *ui; /**< TODO */
    WindowVerArticulos *var; /**< TODO */
    QString usuarioActivo; /**< TODO */
    QString rutaImagen; /**< TODO */
    QPixmap *imagenArticulo; /**< TODO */
    QSqlQuery *actImagen; /**< TODO */
    QString CodigoTienda; /**< TODO */
    QSqlQuery *acept; /**< TODO */
    QSqlQueryArticulos *model; /**< TODO */
    QString consultaAct; /**< TODO */
    bool fotoCargada; /**< TODO */
    DialogWebCam *wb; /**< TODO */
    QTranslator translator; /**< TODO */
    QSqlQuery *consult; /**< TODO */
    int indiceCombo; /**< TODO */
};

#endif // DialogModificarArticulo_H
