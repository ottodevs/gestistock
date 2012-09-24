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


#ifndef WIDGETRESTAURARCOPIASEGURIDAD_H
#define WIDGETRESTAURARCOPIASEGURIDAD_H

#include <QWidget>
#include <QProcess>
#include <QMessageBox>
#include <QFileDialog>
#include <QTranslator>

#include "windowpantallaopcionesusuario.h"
#include "qprogressdialognew.h"

class WindowPantallaOpcionesUsuario;

namespace Ui {
    class WidgetRestaurarCopiaSeguridad;
}

/**
 * @brief Widget que permite la restauración de una copia de seguridad.
 *
 */
class WidgetRestaurarCopiaSeguridad : public QWidget
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
     * @param wpo Puntero a la pantalla principal de la aplicación
     * @param parent Puntero a la ventana padre
     */
    explicit WidgetRestaurarCopiaSeguridad(WindowPantallaOpcionesUsuario *wpo, QWidget *parent = 0);
    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetRestaurarCopiaSeguridad();


private slots:
    /**
     * @brief Slot que permite la selección de una imagen para colocarla en un QLabel.
     *
     */
    void on_pbExaminar_clicked();
    /**
     * @brief Slot que se activa cuando el proceso de restauración ha terminado, determinando el estdo de finalización.
     *
     * @param int Entero recibido
     * @param exitStatus Estado de finalización
     */
    void finalizacion(int, QProcess::ExitStatus exitStatus);
    /**
     * @brief Slot que restaura la copia de seguridad en el sistema.
     *
     */
    void on_pbRestaurar_clicked();

private:
    Ui::WidgetRestaurarCopiaSeguridad *ui; /**< TODO */
    QProcess *procesoRestauracion; /**< TODO */
    QSqlDatabase db; /**< TODO */
    WindowPantallaOpcionesUsuario *wPantalla; /**< TODO */
    QTranslator translator; /**< TODO */
    QProgressDialogNew *pdn; /**< TODO */
};

#endif // WidgetRestaurarCopiaSeguridad_H
