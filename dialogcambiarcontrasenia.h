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


#ifndef DIALOGCAMBIARCONTRASENIA_H
#define DIALOGCAMBIARCONTRASENIA_H

#include <QDialog>
#include <QCloseEvent>
#include <QSqlQuery>
#include <QDebug>
#include <QTranslator>
#include <QMessageBox>

namespace Ui {
    class DialogCambiarContrasenia;
}

/**
 * @brief Diálogo que permite el cambio de contraseña de un usuario.
 *
 */
class DialogCambiarContrasenia : public QDialog
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
     * @brief Constructor del diálogo.
     *
     * @param userActivo Es el usuario actual del sistema, del que se quiere realizar el cambio de contraseña
     * @param parent Puntero a la ventana padre.
     */
    explicit DialogCambiarContrasenia(QString userActivo, QWidget *parent = 0);
    /**
     * @brief Destructor del diálogo.
     *
     */
    ~DialogCambiarContrasenia();

private slots:
    /**
     * @brief Slot que se activa cuando se presiona el botón cambiar, cambia la contraseña del usuario.
     *
     */
    void on_pbCambiar_clicked();

private:
    Ui::DialogCambiarContrasenia *ui; /**< TODO */
    QTranslator translator; /**< TODO */
    QString UsuarioActivo; /**< TODO */
};

#endif // DIALOGCAMBIARCONTRASENIA_H
