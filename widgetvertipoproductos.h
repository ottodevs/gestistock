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


#ifndef WIDGETVERTIPOPRODUCTOS_H
#define WIDGETVERTIPOPRODUCTOS_H

#include <QWidget>
#include <QSqlQuery>
#include <QHeaderView>

#include "qsqlquerytipos.h"
#include "delegate.h"
#include "dialogmodificartipo.h"

namespace Ui {
class WidgetVerTipoProductos;
}

/**
 * @brief Widget que muestra una tabla con los tipos de artículos registrados en el sistema.
 *
 */
class WidgetVerTipoProductos : public QWidget
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor del Widget.
     *
     * @param parent Puntero a la ventana padre.
     */
    explicit WidgetVerTipoProductos(QWidget *parent = 0);
    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetVerTipoProductos();

protected:
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicación, o del sistema, procede a la traducción de todos los elementos.
     *
     * @param event Evento del sistema
     */
    void changeEvent(QEvent* event);

private slots:
    /**
     * @brief Slots que permite la ordenación de los datos de la table en base al item seleccionado de la cabecera.
     *
     */
    void refresh();
    /**
     * @brief Slot que se activa cuando se selecciona una fila de un QTableView, en este caso el de tipos de artículos.
     *
     * @param index
     */
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::WidgetVerTipoProductos *ui; /**< TODO */
    QString consulta, consultaActiva; /**< TODO */
    QHeaderView *header; /**< TODO */
    QSqlQueryTipos *mp; /**< TODO */
    DialogModificarTipo *dmt; /**< TODO */
};

#endif // WIDGETVERTIPOPRODUCTOS_H
