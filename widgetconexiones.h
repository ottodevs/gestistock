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


#ifndef WIDGETCONEXIONES_H
#define WIDGETCONEXIONES_H

#include <QWidget>
#include <QMdiArea>
#include <QHeaderView>
#include <QTranslator>

#include "delegate.h"
#include "qsqlqueryconexiones.h"



namespace Ui {
class WidgetConexiones;
}

/**
 * @brief Widget que muestra las diferentes conexiones realizadas al sistema.
 *
 */
class WidgetConexiones : public QWidget
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
    explicit WidgetConexiones(QMdiArea *mdiArea,QWidget *parent = 0);
    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetConexiones();
    
private slots:
    /**
     * @brief Slot que cierra el Widget.
     *
     */
    void on_pbSalir_clicked();
    /**
     * @brief Slot que borra las conexiones.
     *
     */
    void on_pbBorrar_clicked();
    /**
     * @brief Slot que ordena las conexiones al seleccionar la cabecera.
     *
     */
    void refresh();

private:
    Ui::WidgetConexiones *ui; /**< TODO */
    QMdiArea *mdi; /**< TODO */
    QHeaderView *header; /**< TODO */
    QSqlQueryConexiones *mp; /**< TODO */
    QSqlQuery *consultaConexiones; /**< TODO */
    QString consultaActiva; /**< TODO */
    QString consultaModificable; /**< TODO */
    QTranslator translator; /**< TODO */
};

#endif // WIDGETCONEXIONES_H
