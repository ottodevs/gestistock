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


#ifndef DIALOGNUEVOARTICULO_H
#define DIALOGNUEVOARTICULO_H

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
#include <QDate>
#include "windowverarticulos.h"
#include "camerawidget.h"
#include "dialogwebcam.h"
#include "widgetintroducircompra.h"
#include "qsqlquerycompras.h"


class WidgetIntroducirCompra;
class WindowVerArticulos;
class WindowPantallaOpcionesUsuario;
class QSqlQueryCompras;

using namespace std;

/**
 * @brief Definición del map, relación de la clave primaria del proveedor con su nombre.
 *
 */
typedef map <QString,QString> RelProv;

namespace Ui {
    class DialogNuevoArticulo;
}

/**
 * @brief Diálogo que permite crear un nuevo artículo en el sistema.
 *
 */
class DialogNuevoArticulo : public QDialog
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
      * @param usuarioActivo Usuario activo en el sistema
      * @param date Fecha de la introducción del nuevo artículo
      * @param parent Puntero a la ventana padre
      * @param mp Model de la tabla compras
      * @param consultaAct Consulta activa del model compras
      * @param codEAN Código de barras del artículo a insertar
      */
     explicit DialogNuevoArticulo(QString usuarioActivo, QDate date, QWidget *parent, QSqlQueryCompras *mp, QString consultaAct, QString codEAN = "");
     /**
      * @brief Introduce los items del comboBox de los proveedores.
      *
      */
     void iniciaComboProveedores();
     /**
      * @brief Introduce los items del comboBox de los tipos de artículos.
      *
      */
     void iniciaComboTipos();
    /**
     * @brief Destructor del diálogo
     *
     */
    ~DialogNuevoArticulo();


private slots:
    /**
     * @brief Slot que cierra el diálogo.
     *
     */
    void on_pbCancelar_clicked();
    /**
     * @brief Slot que detecta el evento de tecla ESC.
     *
     */
    void reject();
    /**
     * @brief Slot que detecta el evento de cierre.
     *
     * @param ev Evento de cierre
     */
    void closeEvent(QCloseEvent *ev);
    /**
     * @brief Slot que permite buscar una foto en el ordenador.
     *
     */
    void on_pbExaminar_clicked();
    /**
     * @brief Slot que registra el artículo en el sistema.
     *
     */
    void on_pbGuardar_clicked();
    /**
     * @brief Slot que muestra la cámara en pantalla.
     *
     */
    void on_pbCamara_clicked();

    /**
     * @brief Slot que detecta el cambio del texto de un textEdit.
     *
     */
    void on_teComentario_textChanged();

private:
    Ui::DialogNuevoArticulo *ui; /**< TODO */
    WindowVerArticulos *var; /**< TODO */
    QString userActivo; /**< TODO */
    RelProv rprov; /**< TODO */
    QPixmap *imagenArticulo; /**< TODO */
    QString rutaImagen; /**< TODO */
    WindowPantallaOpcionesUsuario *wpu; /**< TODO */
    QSqlQuery *insertar; /**< TODO */
    QString codigoEAN; /**< TODO */
    bool fotoCargada; /**< TODO */
    QSqlQuery *consulta; /**< TODO */
    QString consultaActiva; /**< TODO */
    DialogWebCam *wb; /**< TODO */
    QTranslator translator; /**< TODO */
    WidgetIntroducirCompra *wic; /**< TODO */
    QSqlQueryArticulos *mpArticulos; /**< TODO */
    QSqlQueryCompras *mpCompras; /**< TODO */
    QDate fecha; /**< TODO */
};

#endif // DIALOGNUEVOARTICULO_H
