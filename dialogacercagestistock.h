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


#ifndef DIALOGACERCAGESTISTOCK_H
#define DIALOGACERCAGESTISTOCK_H

#include <QDialog>

namespace Ui {
class DialogAcercaGestiStock;
}

/**
 * @brief Di�logo que muestra datos relevantes de GestiStock Software, y de su desarrollador.
 *
 */
class DialogAcercaGestiStock : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor del di�logo.
     *
     * @param parent Puntero a la ventana padre
     */
    explicit DialogAcercaGestiStock(QWidget *parent = 0);
    /**
     * @brief Destructor del di�logo
     *
     */
    ~DialogAcercaGestiStock();
    
private slots:
    /**
     * @brief Slots que se activa al presionar el bot�n cerrar, cierra la pantalla.
     *
     */
    void on_pbCerrar_clicked();

protected:
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicaci�n, o del sistema, procede a la traducci�n de todos los elementos.
     *
     * @param event Evento del sistema
     */
    void changeEvent(QEvent* event);

private:
    Ui::DialogAcercaGestiStock *ui; /**< TODO */
};

#endif // DIALOGACERCAGESTISTOCK_H
