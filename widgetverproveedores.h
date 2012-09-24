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


#ifndef WIDGETVERPROVEEDORES_H
#define WIDGETVERPROVEEDORES_H

#include <QWidget>
#include <QTranslator>
#include <QStringList>

#include "windowpantallaopcionesusuario.h"

class WindowPantallaOpcionesUsuario;

namespace Ui {
    class WidgetVerProveedores;
}

/**
 * @brief Widget que muestra los proveedores registrados en el sistema, permitiendo su modificación.
 *
 */
class WidgetVerProveedores : public QWidget
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
     * @param ma Puntero al QMdiArea de la pantalla principal
     * @param parent Puntero a la ventana padre
     */
    explicit WidgetVerProveedores(QMdiArea *ma, QWidget *parent = 0);
    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetVerProveedores();

private slots:
    /**
     * @brief Slot que se activa cuando se cambia el item del comboBox, en este caso el de proveedores.
     *
     * @param arg1 Nuevo item seleccionado
     */
    void on_cbProveedor_currentIndexChanged(const QString &arg1);

    /**
     * @brief Slot que cambia la imagen del proveedor.
     *
     */
    void on_pbCambiarImagen_clicked();

    /**
     * @brief Slot que cierra el Widget.
     *
     */
    void on_pbSalir_clicked();

    /**
     * @brief Slot que guarda los datos modificados del proveedor.
     *
     */
    void on_pbGuardarCambios_clicked();

    /**
     * @brief Slot que elimina el proveedor del sistema.
     *
     */
    void on_pbEliminar_clicked();

private:
    Ui::WidgetVerProveedores *ui; /**< TODO */
    QSqlQuery *consult; /**< TODO */
    QSqlQuery *cn; /**< TODO */
    QSqlQuery *cn1; /**< TODO */
    WindowPantallaOpcionesUsuario *wp; /**< TODO */
    QString rutaImagen; /**< TODO */
    QByteArray ba; /**< TODO */
    WindowPantallaOpcionesUsuario *wpo; /**< TODO */
    QPixmap *imagenArticulo; /**< TODO */
    QMdiArea *mdi; /**< TODO */
    QSqlQuery *actualizar; /**< TODO */
    bool ImagenActualizada; /**< TODO */
    QTranslator translator; /**< TODO */
    bool fotoCargada; /**< TODO */
};

#endif // WIDGETVERPROVEEDORES_H
