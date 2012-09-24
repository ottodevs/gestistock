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


#ifndef DIALOGTIPOGRAFICA_H
#define DIALOGTIPOGRAFICA_H

#include <QDialog>
#include "mdiarea.h"

#include "widgetestadisticascompras.h"

class WidgetEstadisticasCompras;

namespace Ui {
class DialogTipoGrafica;
}

/**
 * @brief Diálogo que permite elegir el tipo de gráfica deseada para las estadísticas, así como, el criterio seguido para la construcción de las mismas.
 *
 */
class DialogTipoGrafica : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor del diálogo.
     *
     * @param mdi Puntero al mdiArea de la ventana principal, para poder introducir la ventana de las estadísticas dentro de ella
     * @param parent Puntero a la ventana padre
     */
    explicit DialogTipoGrafica(MdiArea *mdi, QWidget *parent = 0);
    /**
     * @brief Destructor del diálogo.
     *
     */
    ~DialogTipoGrafica();

protected:
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicación, o del sistema, procede a la traducción de todos los elementos.
     *
     * @param event Evento del sistema
     */
    void changeEvent(QEvent* event);
    
private slots:
    /**
     * @brief Slot que permite confirmar el tipo de la gráfica, así como, el criterio a partir del cual se construyen las estadísticas.
     *
     */
    void on_pbAceptar_clicked();

    /**
     * @brief Slot que contiene un criterio para construir las estadísticas.
     *
     */
    void on_rbCompras_clicked();

    /**
     * @brief Slot que contiene un criterio para construir las estadísticas.
     *
     */
    void on_rbSalidas_clicked();

    /**
     * @brief Slot que contiene un criterio para construir las estadísticas.
     *
     */
    void on_rbComprasCant_clicked();

private:
    Ui::DialogTipoGrafica *ui; /**< TODO */
    WidgetEstadisticasCompras *westc; /**< TODO */
    MdiArea *mdiArea; /**< TODO */

};

#endif // DIALOGTIPOGRAFICA_H
