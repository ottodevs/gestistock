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


#ifndef DIALOGCOMPRAS_H
#define DIALOGCOMPRAS_H

#include <QDialog>
#include <QSqlQuery>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>
#include <QDate>

#include "qsqlqueryarticulos.h"
#include "widgetintroducircompra.h"
#include "qsqlquerycompras.h"

class WidgetIntroducirCompra;

namespace Ui {
class DialogCompras;
}

/**
 * @brief Diálogo que permite introducir una compra en el sistema.
 *
 */
class DialogCompras : public QDialog
{
    Q_OBJECT
    
public:
    //explicit DialogCompras(QString codEan, QString proveedor, QDate date, QSqlQueryCompras *model, QSqlQueryArticulos *modelArticulos, QString consultaActiva, WidgetIntroducirCompra *wic, QWidget *parent = 0);
    /**
     * @brief Constructor del diálogo.
     *
     * @param user Usuario que realiza la compra
     * @param proveedor Proveedor al cual se le hace la compra
     * @param date Fecha de la compra
     * @param modelArticulos Model del QTableView artículos
     * @param modelCompras Model del QTableView compras
     * @param consultaArticulos Consulta actual del model de artículos
     * @param consultaCompras Consulta actual del model de compras
     * @param wic Puntero a la ventana WidgetIntroducirCompra, para poder hacer efectivos los cambios
     * @param parent Puntero a la ventana padre
     */
    explicit DialogCompras(QString user, QString proveedor, QDate date, QSqlQueryArticulos *modelArticulos, QSqlQueryCompras *modelCompras, QString consultaArticulos, QString consultaCompras, WidgetIntroducirCompra *wic, QWidget *parent = 0);
    /**
     * @brief Constructor del diálogo.
     *
     * @param user Usuario que realiza la compra
     * @param codEan Código de barras del artículo
     * @param proveedor Proveedor al cual se le hace la compra
     * @param date Fecha de la compra
     * @param modelArticulos Model del QTableView artículos
     * @param modelCompras Model del QTableView compras
     * @param consultaArticulos Consulta actual del model de artículos
     * @param consultaCompras Consulta actual del model de compras
     * @param wic Puntero a la ventana WidgetIntroducirCompra, para poder hacer efectivos los cambios
     * @param parent Puntero a la ventana padre
     */
    explicit DialogCompras(QString user, QString codEan, QString proveedor, QDate date, QSqlQueryArticulos *modelArticulos, QSqlQueryCompras *modelCompras, QString consultaArticulos, QString consultaCompras, WidgetIntroducirCompra *wic, QWidget *parent = 0);
    /**
     * @brief Destructor del diálogo DialogCompras.
     *
     */
    ~DialogCompras();
    
private slots:
    /**
     * @brief Slot activado al presionar el botón Cancelar, cierra la ventana.
     *
     */
    void on_pbCancelar_clicked();

    /**
     * @brief Slot activado al presionar el botón Guardar, guarda los cambios.
     *
     */
    void on_pbGuardar_clicked();

    /**
     * @brief Slot que se activa cuando se quita el foco del lineEdit, completando en este caso el código de barras introducido
     *
     */
    void on_leCodEAN_editingFinished();

protected:
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicación, o del sistema, procede a la traducción de todos los elementos.
     *
     * @param event Evento del sistema
     */
    void changeEvent(QEvent* event);

private:
    Ui::DialogCompras *ui; /**< TODO */
    QSqlQuery *consult; /**< TODO */
    QSqlQuery *consult2; /**< TODO */
    QPixmap *imagenArticulo; /**< TODO */
    QSqlQuery *actImagen; /**< TODO */
    QString codigoEAN; /**< TODO */
    QString provider; /**< TODO */
    QSqlQueryCompras *mpCompras; /**< TODO */
    QSqlQueryArticulos *mpAlmacen; /**< TODO */
    QString consultaModelCompras; /**< TODO */
    QString consultaModelAlmacen; /**< TODO */
    QDate fecha; /**< TODO */
    WidgetIntroducirCompra *pwic; /**< TODO */
    QString usuarioActivo; /**< TODO */

};

#endif // DIALOGCOMPRAS_H
