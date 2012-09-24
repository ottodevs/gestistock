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


#ifndef WIDGETDARTICULOMASCOMPRADO_H
#define WIDGETDARTICULOMASCOMPRADO_H

#include <QWidget>
#include <QTranslator>
#include <QSqlQuery>

#include "qsqlqueryarticulosmascomprados.h"
#include "delegate.h"


namespace Ui {
class WidgetArticuloMasComprado;
}

/**
 * @brief Widget que permite visionar cual ha sido el artículo más comprado.
 *
 */
class WidgetArticuloMasComprado : public QWidget
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
     * @param parent Puntero a la ventana padre
     */
    explicit WidgetArticuloMasComprado(QWidget *parent = 0);
    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetArticuloMasComprado();
    
private:
    Ui::WidgetArticuloMasComprado *ui; /**< TODO */
    QTranslator translator; /**< TODO */
    QSqlQuery *consultaArticulos; /**< TODO */
    QSqlQueryArticulosMasComprados *mp; /**< TODO */
    QString consulta; /**< TODO */
};

#endif // WidgetArticuloMasComprado_H
