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


#ifndef WIDGETACTIVIDADUSUARIO_H
#define WIDGETACTIVIDADUSUARIO_H

#include <QWidget>
#include <QCalendarWidget>
#include <QDateEdit>
#include <QSqlQuery>
#include <QHeaderView>
#include <QItemDelegate>
#include <QMdiArea>
#include <QTranslator>


#include "qsqlqueryactividad.h"
#include "delegate.h"

class QSqlQueryActividad;


namespace Ui {
class WidgetActividadUsuario;
}

/**
 * @brief Widget que muestra la actividad de los usuarios.
 *
 */
class WidgetActividadUsuario : public QWidget
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
    explicit WidgetActividadUsuario(QMdiArea *mdiArea, QWidget *parent = 0);
    /**
     * @brief Introduce los usuarios en el comboBox.
     *
     */
    void rellenarComboUsuarios();
    /**
     * @brief Introduce los tipos de movimientos en el comboBox.
     *
     */
    void rellenarComboTipoMovimientos();
    /**
     * @brief Introduce los artículos en el comboBox.
     *
     */
    void rellenarComboArticulos();

    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetActividadUsuario();

private slots:
    /**
     * @brief Slot que realiza una búsqueda con los criterios determinados por el usuario.
     *
     */
    void on_pbAplicar_clicked();
    /**
     * @brief Slot que permite la ordenación de las tablas a traves de las cabeceras de las mismas.
     *
     */
    void refresh();
    /**
     * @brief Slot que permite borrar toda la actividad del sistema.
     *
     */
    void on_pbBorrar_clicked();

private:
    Ui::WidgetActividadUsuario *ui; /**< TODO */
    QSqlQuery *consultaArticulos; /**< TODO */
    QSqlQuery *consultaUsuarios; /**< TODO */
    QSqlQueryActividad *mp; /**< TODO */
    QHeaderView *header; /**< TODO */
    QString consultaActiva; /**< TODO */
    QString consultaModificable; /**< TODO */
    QTranslator translator; /**< TODO */
};



#endif // WidgetActividadUsuario_H


