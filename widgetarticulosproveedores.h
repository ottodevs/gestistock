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


#ifndef WIDGETARTICULOSPROVEEDORES_H
#define WIDGETARTICULOSPROVEEDORES_H

#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QMdiArea>
#include <QTranslator>

#include "dialogmodificararticuloproveedor.h"
#include "qsqlqueryarticulosproveedor.h"
#include "delegate.h"
#include "dialoganyadirarticuloproveedor.h"
#include "qsqlqueryarticulos.h"

class DialogModificarArticuloProveedor;

namespace Ui {
class WidgetArticulosProveedores;
}

/**
 * @brief Widget que permite visionar los art�culos de los proveedores.
 *
 */
class WidgetArticulosProveedores : public QWidget
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
     * @brief Constructor del Widget.
     *
     * @param user Usuario actual de la aplicaci�n
     * @param mdiArea Puntero al QMdiArea de la ventana principal
     * @param parent Puntero a la ventana padre
     */
    explicit WidgetArticulosProveedores(QString user, QMdiArea *mdiArea, QWidget *parent = 0);
     /**
      * @brief Introduce los proveedores en su comboBox.
      *
      */
     void rellenarComboProveedores();
     /**
      * @brief Inicializa los elementos de la pesta�a almac�n.
      *
      */
     void inicializarTabAlmacen();
     /**
      * @brief Inicializa los elementos de la pesta�a proveedores.
      *
      */
     void inicializarTabArticulosProveedor();
     /**
      * @brief Introduce los tipos de art�culos en su comboBox.
      *
      */
     void rellenarComboTipos();
     /**
      * @brief Evento activado al pulsar cualquier tecla.
      *
      * @param ke Evento de tecla.
      */
     void keyReleaseEvent(QKeyEvent *ke);
    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetArticulosProveedores();
    
private slots:
    /**
     * @brief Slot que se activa cuando se cambia el �ndice de un comboBox.
     *
     * @param arg1 Argumento nuevo del comboBox
     */
    void on_cbProveedor_currentIndexChanged(const QString &arg1);
    /**
     * @brief Slot que permite la ordenaci�n de los elementos de un QTableView a partir de la selecci�n de su cabecera.
     *
     */
    void refresh();
    /**
     * @brief Slot activado cuando se presiona un elemento de un QTableView.
     *
     * @param index Contiene los datos de la fila
     */
    void on_tvArticulosProveedor_clicked(const QModelIndex &index);
    /**
     * @brief Slot confirma una determinada b�squeda, al pulsar su bot�n.
     *
     */
    void on_pbBuscar_clicked();
    /**
     * @brief Slot que ordena un QTableView a partir de la selecci�n de su cabecera.
     *
     */
    void refreshOrdenarArticulosAlmacen();
    /**
     * @brief Slot activado cuando se presiona un elemento de un QTableView.
     *
     *
     * @param index Contiene los datos de la fila
     */
    void on_tvArticulos_clicked(const QModelIndex &index);
    /**
     * @brief Slot confirma una determinada b�squeda, al pulsar su bot�n.
     *
     */
    void on_pbBuscar_2_clicked();
    /**
     * @brief Al activarlo se refresca el QTableView de la pesta�a art�culos con todos los elementos.
     *
     */
    void on_rbMostrarTodos_clicked();
    /**
     * @brief Al activarlo se refresca el QTableView de la pesta�a almac�n con todos los elementos.
     *
     */
    void on_rbMostrarTodosAlmacen_clicked();

private:
    Ui::WidgetArticulosProveedores *ui; /**< TODO */
    DialogModificarArticuloProveedor *map; /**< TODO */
    QSqlQuery *cn; /**< TODO */
    QHeaderView *header; /**< TODO */
    QString consulta; /**< TODO */
    QString consultaActiva; /**< TODO */
    QSqlQueryArticulosProveedor *mp; /**< TODO */
    QSqlQueryArticulos *mpAlmacen; /**< TODO */
    QTranslator translator; /**< TODO */
    QString cifProveedor; /**< TODO */
    DialogAnyadirArticuloProveedor *darp; /**< TODO */
    QString consultaActivaArt; /**< TODO */
    QString consultaArt; /**< TODO */
    QHeaderView *headerArt; /**< TODO */
    QString usuarioActivo; /**< TODO */
    QSqlQuery *consultArticulos, *consultAlmacen; /**< TODO */
    QString cad; /**< TODO */

};

#endif // WIDGETARTICULOSPROVEEDORES_H
