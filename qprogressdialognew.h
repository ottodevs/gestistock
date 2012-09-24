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


#ifndef QPROGRESSDIALOGNEW_H
#define QPROGRESSDIALOGNEW_H

#include <QProgressDialog>
#include <QCloseEvent>

/**
 * @brief Clase que hereda las características de una QProgressDialog y para crear una con características modificadas.
 *
 */
class QProgressDialogNew: public QProgressDialog
{
public:
/**
 * @brief Constructor de la barra de progreso.
 *
 */
    QProgressDialogNew(){}
    /**
     * @brief Evento de la tecla ESC.
     *
     */
    void reject();
    /**
     * @brief Captura el evento de cierre, no permitiendo el cierre de la barra de progreso.
     *
     * @param e Evento de cierre
     */
    inline void closeEvent(QCloseEvent *e){e->ignore();}
    /**
     * @brief Destructor de la QProgressDialogNew
     *
     */
    ~QProgressDialogNew(){}

private:

};

#endif // QPROGRESSDIALOGNEW_H
