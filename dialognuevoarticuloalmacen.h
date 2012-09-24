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


#ifndef DIALOGNUEVOARTICULOALMACEN_H
#define DIALOGNUEVOARTICULOALMACEN_H

#include <QDialog>
#include <map>
#include <iostream>
#include <iterator>
#include <QPixmap>
#include <QBuffer>
#include <QDebug>
#include <QSqlError>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QTranslator>

#include "windowverarticulos.h"
#include "camerawidget.h"
#include "dialogwebcam.h"



namespace Ui {
class DialogNuevoArticuloAlmacen;
}

/**
 * @brief Diálogo que permite la creación de un nuevo artículo en el almacén.
 *
 */
class DialogNuevoArticuloAlmacen : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor del diálogo.
     *
     * @param usuarioActivo Usuario que crea el artículo
     * @param parent Puntero a la ventana padre
     * @param mp Model de la tabla del almacén
     * @param consultaAct Consulta activa del model almacén
     * @param lcd Muestra el número de artículos que contiene la tabla en cada momento
     * @param codEAN Código de barras del artículo a crear
     */
    explicit DialogNuevoArticuloAlmacen(QString usuarioActivo, QWidget *parent, QSqlQueryArticulos *mp, QString consultaAct, QLCDNumber *lcd, QString codEAN="");
    /**
     * @brief Rellena los items del comboBox de los tipos.
     *
     */
    void iniciaComboTipos();
    /**
     * @brief Destructor del diálogo.
     *
     */
    ~DialogNuevoArticuloAlmacen();

protected:
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicación, o del sistema, procede a la traducción de todos los elementos.
     *
     * @param event Evento del sistema
     */

    void changeEvent(QEvent* event);
    
private slots:
    /**
     * @brief Slot que permite la asignación de una foto al artículo.
     *
     */
    void on_pbExaminar_clicked();

    /**
     * @brief Slot que muestra la pantalla de la cámara.
     *
     */
    void on_pbCamara_clicked();

    /**
     * @brief Slot que cierra el diálogo.
     *
     */
    void on_pbCancelar_clicked();

    /**
     * @brief Slot que guarda el nuevo artículo en el almacén.
     *
     */
    void on_pbGuardar_clicked();

    /**
     * @brief Slot que detecta un cambio en el texto de un textEdit.
     *
     */
    void on_teComentario_textChanged();

private:
    Ui::DialogNuevoArticuloAlmacen *ui; /**< TODO */
    QString userActivo; /**< TODO */
    QPixmap *imagenArticulo; /**< TODO */
    QString rutaImagen; /**< TODO */
    QString codigoEAN; /**< TODO */
    bool fotoCargada; /**< TODO */
    QString consultaActual; /**< TODO */
    DialogWebCam *wb; /**< TODO */
    QTranslator translator; /**< TODO */
    QSqlQueryArticulos *mpArticulos; /**< TODO */
    QSqlQuery *insertarArticulo; /**< TODO */
    QLCDNumber *plcd; /**< TODO */
};

#endif // DIALOGNUEVOARTICULOALMACEN_H
