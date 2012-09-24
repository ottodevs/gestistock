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

#ifndef DIALOGRECUPERARPASS_H
#define DIALOGRECUPERARPASS_H

#include <QDialog>
#include <QCloseEvent>
#include <QSqlQuery>
#include <QTranslator>
#include <QProcess>
#include "smtp.h"

namespace Ui {
    class DialogRecuperarPass;
}

/**
 * @brief Di�logo que permite recuperar la contrase�a del usuario.
 *
 */
class DialogRecuperarPass : public QDialog
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
     * @brief Constructor del di�logo.
     *
     * @param parent Puntero a la ventana padre
     */
    explicit DialogRecuperarPass(QWidget *parent = 0);
    /**
     * @brief Destructor del di�logo.
     *
     */
    ~DialogRecuperarPass();

private slots:
    /**
     * @brief Slot que envia la contrase�a al correo del usuario.
     *
     */
    void on_pbEnviar_clicked();
    /**
     * @brief Slot que cierra el di�logo.
     *
     */
    void on_pbCancelar_clicked();

private:
    Ui::DialogRecuperarPass *ui; /**< TODO */
    QSqlQuery *consultaUsuario; /**< TODO */
    QTranslator translator; /**< TODO */

};

#endif // DIALOGRECUPERARPASS_H
