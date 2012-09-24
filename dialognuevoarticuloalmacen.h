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
 * @brief Di�logo que permite la creaci�n de un nuevo art�culo en el almac�n.
 *
 */
class DialogNuevoArticuloAlmacen : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor del di�logo.
     *
     * @param usuarioActivo Usuario que crea el art�culo
     * @param parent Puntero a la ventana padre
     * @param mp Model de la tabla del almac�n
     * @param consultaAct Consulta activa del model almac�n
     * @param lcd Muestra el n�mero de art�culos que contiene la tabla en cada momento
     * @param codEAN C�digo de barras del art�culo a crear
     */
    explicit DialogNuevoArticuloAlmacen(QString usuarioActivo, QWidget *parent, QSqlQueryArticulos *mp, QString consultaAct, QLCDNumber *lcd, QString codEAN="");
    /**
     * @brief Rellena los items del comboBox de los tipos.
     *
     */
    void iniciaComboTipos();
    /**
     * @brief Destructor del di�logo.
     *
     */
    ~DialogNuevoArticuloAlmacen();

protected:
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicaci�n, o del sistema, procede a la traducci�n de todos los elementos.
     *
     * @param event Evento del sistema
     */

    void changeEvent(QEvent* event);
    
private slots:
    /**
     * @brief Slot que permite la asignaci�n de una foto al art�culo.
     *
     */
    void on_pbExaminar_clicked();

    /**
     * @brief Slot que muestra la pantalla de la c�mara.
     *
     */
    void on_pbCamara_clicked();

    /**
     * @brief Slot que cierra el di�logo.
     *
     */
    void on_pbCancelar_clicked();

    /**
     * @brief Slot que guarda el nuevo art�culo en el almac�n.
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
