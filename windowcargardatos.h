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


#ifndef WINDOWCARGARDATOS_H
#define WINDOWCARGARDATOS_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDesktopWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QSqlQuery>
#include <QTranslator>
#include "windownuevaempresa.h"
#include "dialogrecuperarpass.h"
#include "windowpantallaopcionesusuario.h"
#include "dialogconexionremota.h"
#include "dialogacercagestistock.h"


#include "qwt_plot.h"

class WindowPantallaOpcionesUsuario;
class WindowNuevaEmpresa;
class DialogConexionRemota;

namespace Ui {
    class WindowCargarDatos;
}

/**
 * @brief Ventana que permite el logueo de un usuario en el sistema.
 *
 */
class WindowCargarDatos : public QMainWindow
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
     * @brief Constructor de la ventana de inicio.
     *
     * @param parent
     */
    explicit WindowCargarDatos(QWidget *parent=0);
    /**
     * @brief Carga el lenguaje de la aplicación.
     *
     * @param locale Lenguaje de la aplicación.
     */
    void cargarLenguaje(const QString locale);
    /**
     * @brief Bloquea las funciones a los usuarios que no tienen privilegios de administrador.
     *
     */
    //void BloquearBotones();
    /**
     * @brief
     *
     */
    //void DesbloquearBotones();
    /**
     * @brief Crea la base de datos en el servidor, en el primer arranque del programa.
     *
     */
    void crearBD();
    /**
     * @brief Conecta a la base de datos de la aplicación.
     *
     * @return bool
     */
    bool conectBD();
    /**
     * @brief Crea las tablas de la base de datos, en el primer arranque del programa.
     *
     */
    void crearTablasBD();
    /**
     * @brief Comprueba si existe el usuario de la base de datos.
     *
     * @return bool Devuelve true si existe, y false si no existe
     */
    bool existeUsuarioBD();
    /**
     * @brief Comprueba si existe la base de datos en el servidor.
     *
     * @return bool
     */
    bool existeBD();
    /**
     * @brief Comprueba si ya hay una empresa registrada, en caso afirmativo bloquea el botón de crear una nueva.
     *
     */
    void comprobarAccion();
    /**
     * @brief Consulta el idioma almacenado de la aplicación.
     *
     */
    void consultarIdioma();
    /**
     * @brief Desconecta del servidor externo, y conecta a localhost.
     *
     */
    void botonDesconectar();
    /**
     * @brief Destructor de la ventana inicial.
     *
     */
    ~WindowCargarDatos();

private slots:

    /**
     * @brief Slot que limpia los campos de usuario y contraseña.
     *
     */
    void on_pbLimpiar_clicked();

    /**
     * @brief Slot que comprueba el usuario y contraseña introducidos por el usuario, para dar paso a la ventana principal.
     *
     */
    void on_pbAceptar_clicked();

    /**
     * @brief Slot que muestra la pantalla de creación de nueva empresa.
     *
     */
    void on_actionNueva_Empresa_activated();

    /**
     * @brief Slot que cierra la ventana inicial.
     *
     */
    void on_actionSalir_activated();

    /**
     * @brief Slot que muestra la ventana de recuperación de contraseña.
     *
     */
    void on_actionRecuperar_Contrase_a_2_activated();

    /**
     * @brief Slot que pone la aplicación en español.
     *
     */
    void on_actionEspa_ol_activated();

    /**
     * @brief Slot que pone la aplicación en inglés.
     *
     */
    void on_actionIngl_s_activated();

    /**
     * @brief Slot que muestra la pantalla de base de datos remota.
     *
     */
    void on_actionBD_Remota_activated();

    /**
     * @brief Slot que muestra la pantalla de descripción de Qt Creator.
     *
     */
    void on_actionAcerca_de_Qt_activated();

    /**
     * @brief Slot que conecta al servidor local, y desconecta del remoto.
     *
     */
    void on_actionDesconectar_BD_Remota_activated();

    /**
     * @brief Slot que muestra la pantalla de descripción de GestiStock Software.
     *
     */
    void on_actionAcerca_de_GestiStock_Software_activated();

private:
    Ui::WindowCargarDatos *ui; /**< TODO */
    WindowPantallaOpcionesUsuario *pu; /**< TODO */
    QSqlDatabase bd; /**< TODO */
    WindowNuevaEmpresa *Wne; /**< TODO */
    DialogRecuperarPass *drp; /**< TODO */
    QDesktopWidget *d; /**< TODO */
    QTranslator translator; /**< TODO */
    QString locale; /**< TODO */
    DialogConexionRemota *dcr; /**< TODO */
    QSqlQuery *consulta; /**< TODO */
    DialogAcercaGestiStock *dag; /**< TODO */
};

#endif // WINDOWCARGARDATOS_H

