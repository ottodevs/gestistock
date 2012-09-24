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


#ifndef DIALOGCONEXIONREMOTA_H
#define DIALOGCONEXIONREMOTA_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QDebug>

#include "windowcargardatos.h"

class WindowCargarDatos;

namespace Ui {
class DialogConexionRemota;
}

/**
 * @brief Diálogo que permite la conexión remota a un servidor externo.
 *
 */
class DialogConexionRemota : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor del diálogo.
     *
     * @param bd Puntero a la base de datos a la cual está conectada la aplicación.
     * @param wcd Puntero a la ventana de la clase WindowCargarDatos, para poder cambiar algunos detalles de la misma
     * @param parent Puntero a la ventana padre.
     */
    explicit DialogConexionRemota(QSqlDatabase *bd, WindowCargarDatos *wcd, QWidget *parent = 0);
    /**
     * @brief Destructor del diálogo.
     *
     */
    ~DialogConexionRemota();
    /**
     * @brief Comprueba si existe el usuario de la base de datos.
     *
     * @return bool Devuelve true si existe, y false si no existe
     */
    bool existeUsuarioBD();
    /**
     * @brief Comprueba si existe la base de datos.
     *
     * @return bool Devuelve true si existe, y false si no existe
     */
    bool existeBD();
    /**
     * @brief Conecta a la base de datos.
     *
     */
    void conectBD();
    /**
     * @brief Comprueba la conexión
     *
     */

protected:
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicación, o del sistema, procede a la traducción de todos los elementos.
     *
     * @param event Evento del sistema
     */
    void changeEvent(QEvent* event);

    
private slots:
    /**
     * @brief Slot que permite la conexión a la base de datos remota.
     *
     */
    void on_pbConectar_clicked();
    /**
     * @brief Slot que se activa al marcar la casilla predeterminada.
     *
     * @param checked
     */
    void on_checkBox_clicked(bool checked);

private:
    Ui::DialogConexionRemota *ui; /**< TODO */
    QSqlDatabase *baseDatos; /**< TODO */
    QSqlDatabase db; /**< TODO */
    WindowCargarDatos *pwcd; /**< TODO */
};

#endif // DIALOGCONEXIONREMOTA_H
