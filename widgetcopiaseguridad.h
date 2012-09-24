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


#ifndef WIDGETCOPIASEGURIDAD_H
#define WIDGETCOPIASEGURIDAD_H

#include <QWidget>
#include <QProcess>
#include <QMessageBox>
#include <QTranslator>
#include "windowpantallaopcionesusuario.h"
#include "qprogressdialognew.h"

class WindowPantallaOpcionesUsuario;


namespace Ui {
    class WidgetCopiaSeguridad;
}

/**
 * @brief Widget que permite la realización de una copia de seguridad de la base de datos de la aplicación.
 *
 */
class WidgetCopiaSeguridad : public QWidget
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
     * @param parent Puntero a la ventana padre
     */
    explicit WidgetCopiaSeguridad(QWidget *parent = 0);
    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetCopiaSeguridad();


private slots:
    /**
     * @brief Slot que permite seleccionar una imagen a partir de un archivo y colocarla en un QLabel.
     *
     */
    void on_pbExaminar_clicked();
    /**
     * @brief Slot que se activa cuando un proceso a finalizado indicando el estado de finalización.
     *
     * @param int
     * @param exitStatus
     */
    void finalizado(int, QProcess::ExitStatus exitStatus);
    /**
     * @brief Slot que crea una copia de seguridad en el destino seleccionado.
     *
     */
    void on_pbCrear_clicked();

private:
    Ui::WidgetCopiaSeguridad *ui; /**< TODO */
    WindowPantallaOpcionesUsuario *wp; /**< TODO */
    QProcess *procesoCopia; /**< TODO */
    QProgressDialog *pb; /**< TODO */
    QProgressDialogNew *pdn; /**< TODO */
    QTranslator translator; /**< TODO */

};

#endif // WIDGETCOPIASEGURIDAD_H
