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


#ifndef DIALOGSALIDAARTICULO_H
#define DIALOGSALIDAARTICULO_H

#include <QDialog>
#include <QSqlQuery>
#include <QDate>
#include <QMessageBox>

#include "qsqlqueryarticulos.h"
#include "qsqlquerysalidas.h"
#include "widgetsalidasarticulos.h"

class WidgetSalidasArticulos;

namespace Ui {
class DialogSalidaArticulo;
}

/**
 * @brief Di�logo que permite la salida de un art�culo del almac�n.
 *
 */
class DialogSalidaArticulo : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor del di�logo.
     *
     * @param user Usuario que efect�a la salida de art�culo del almac�n
     * @param codEAN Codigo de barras del art�culo
     * @param modelArticulos Model de la tabla del almac�n
     * @param modelSalidas Model de la tabla salidas
     * @param consultaActivaArt Consulta activa del model del almac�n
     * @param consultaActivaSal Consulta activa del model de las salidas
     * @param date Fecha de la salida del almac�n
     * @param wsa Puntero a la ventana WidgetSalidasArticulos para actualizar varios datos
     * @param parent Puntero a la ventana padre
     */
    explicit DialogSalidaArticulo(QString user, QString codEAN, QSqlQueryArticulos *modelArticulos, QSqlQuerySalidas *modelSalidas, QString consultaActivaArt, QString consultaActivaSal, QDate date, WidgetSalidasArticulos *wsa, QWidget *parent = 0);
    /**
     * @brief Sombre en el calendario los dias que hay compras registradas.
     *
     */
    void sombrearCalendario();
    /**
     * @brief Destructor del di�logo.
     *
     */
    ~DialogSalidaArticulo();


protected:
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicaci�n, o del sistema, procede a la traducci�n de todos los elementos.
     *
     * @param event Evento del sistema
     */
    void changeEvent(QEvent* event);


private slots:
    /**
     * @brief Slot que cierra la pantalla.
     *
     */
    void on_pbCancelar_clicked();
    /**
     * @brief Slot que guarda la salida del almac�n.
     *
     */
    void on_pbGuardar_clicked();

private:
    Ui::DialogSalidaArticulo *ui; /**< TODO */
    QString codigoEAN; /**< TODO */
    QSqlQueryArticulos *mpArticulos; /**< TODO */
    QSqlQuerySalidas *mpSalidas; /**< TODO */
    QString consultaModelArt; /**< TODO */
    QString consultaModelSal; /**< TODO */
    QDate fecha; /**< TODO */
    QString usuarioActivo; /**< TODO */
    QSqlQuery *datos; /**< TODO */
    WidgetSalidasArticulos *pwsa; /**< TODO */
    QSqlQuery *querySalidas; /**< TODO */
    QTextCharFormat fondoCalendar; /**< TODO */
};

#endif // DIALOGSALIDAARTICULO_H
