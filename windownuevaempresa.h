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


#ifndef WINDOWNUEVAEMPRESA_H
#define WINDOWNUEVAEMPRESA_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTime>
#include <QLineEdit>
#include <QSqlQuery>
#include <QTranslator>
#include "smtp.h"
#include "windowcargardatos.h"

class WindowCargarDatos;

namespace Ui {
    class WindowNuevaEmpresa;
}

/**
 * @brief Ventana que permite el registro de una empresa en el sistema.
 *
 */
class WindowNuevaEmpresa : public QMainWindow
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
     * @brief Constructor de la ventana.
     *
     * @param wcd Puntero a la ventana inicial.
     * @param parent Puntero a la ventana padre.
     */
    explicit WindowNuevaEmpresa(WindowCargarDatos *wcd,QMainWindow *parent = 0);
    /**
     * @brief Destructor de la ventana.
     *
     */
    ~WindowNuevaEmpresa();

private slots:
    /**
     * @brief Slot que cierra la ventana.
     *
     */
    void on_pbSalir_clicked();
    /**
     * @brief Slot que limpia los campos de la ventana.
     *
     */
    void on_pbLimpiar_clicked();
    /**
     * @brief Slot que registra la empresa y el usuario inicial en el sistema.
     *
     */
    void on_pbCompletar_clicked();

private:
    Ui::WindowNuevaEmpresa *ui; /**< TODO */
    WindowCargarDatos *wcd; /**< TODO */
    QTranslator translator; /**< TODO */
    QSqlQuery *insertarUsuario; /**< TODO */
    QSqlQuery *insertarEmpresa; /**< TODO */
    WindowCargarDatos *pwcd; /**< TODO */
};

#endif // WINDOWNUEVAEMPRESA_H
