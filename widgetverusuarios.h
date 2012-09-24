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


#ifndef WIDGETVERUSUARIOS_H
#define WIDGETVERUSUARIOS_H

#include <QWidget>
#include <QSqlQuery>
#include <QDate>
#include <QDebug>
#include <QMdiArea>
#include <QTranslator>

#include "dialogmodificarusuario.h"
#include "qsqlqueryusuarios.h"
#include "delegate.h"

class DialogModificarUsuario;

namespace Ui {
class WidgetVerUsuarios;
}

/**
 * @brief Muestra una tabla con los usuarios registrados en el sistema.
 *
 */
class WidgetVerUsuarios : public QWidget
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
     * @param user Usuario activo en la aplicación
     * @param ma Puntero al QMdiArea de la pantalla principal
     * @param parent Puntero a la ventana padre.
     */
    explicit WidgetVerUsuarios(QString user, QMdiArea *ma,QWidget *parent = 0);
    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetVerUsuarios();
    
private slots:
    /**
     * @brief Slot que cierra el Widget.
     *
     */
    void on_pbSalir_clicked();
    /**
     * @brief Slot que se activa al presionar una fila de la tabla.
     *
     * @param index Datos de la fila seleccionada
     */
    void on_tableView_clicked(const QModelIndex &index);
    /**
     * @brief Slot que ordena el QTableView según el criterio marcado.
     *
     */
    void refresh();

private:
    Ui::WidgetVerUsuarios *ui; /**< TODO */
    DialogModificarUsuario *dmu; /**< TODO */
    QSqlQueryUsuarios *mp; /**< TODO */
    QString consulta; /**< TODO */
    QHeaderView *header; /**< TODO */
    QMdiArea *mdi; /**< TODO */
    QTranslator translator; /**< TODO */
    QString usuarioActivo; /**< TODO */
    QString consultaActiva;
};

#endif // WIDGETVERSUSUARIOS_H
