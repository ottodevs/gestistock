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


#ifndef WIDGETSALIDASARTICULOS_H
#define WIDGETSALIDASARTICULOS_H

#include <QWidget>
#include <QSqlQuery>
#include <QEvent>
#include <QString>
#include <QDateEdit>

#include "qsqlqueryarticulos.h"
#include "qsqlquerysalidas.h"
#include "delegatearticulos.h"
#include "delegate.h"
#include "dialogsalidaarticulo.h"

class DialogSalidaArticulo;

namespace Ui {
class WidgetSalidasArticulos;
}

/**
 * @brief Widget que permite la salida de art�culos del almac�n.
 *
 */
class WidgetSalidasArticulos : public QWidget
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor del Widget.
     *
     * @param user Usuario que realiza la salida
     * @param local Idioma de la aplicaci�n
     * @param parent Puntero a la ventana padre
     */
    explicit WidgetSalidasArticulos(QString user, QString *local, QWidget *parent = 0);
    /**
     * @brief Inicializa los elementos de la pesta�a art�culos.
     *
     */
    void inicializarTabArticulos();
    /**
     * @brief Inicializa los elementos de la pesta�a salidas.
     *
     */
    void inicializarTabSalidas();
    /**
     * @brief Rellena el comboBox con los tipos de art�culos.
     *
     */
    void rellenarComboTipos();
    /**
     * @brief Actualiza el idioma del calendario.
     *
     * @param idioma Idioma actual de la aplicaci�n.
     */
    void actualizarStatus(QString idioma);
    /**
     * @brief Sombrea el calendario, los d�as que ha habido salidas.
     *
     */
    void marcarCalendario();
    /**
     * @brief Evento que se emite cada vez que se presiona una tecla.
     *
     * @param ke Evento de tecla
     */
    void keyReleaseEvent(QKeyEvent *ke);
    /**
     * @brief Destructor del Widget
     *
     */
    ~WidgetSalidasArticulos();
    
public slots:
    /**
     * @brief Slot que permite la ordenaci�n de la tabla art�culos a partir de la selecci�n de su cabecera.
     *
     */
    void refreshOrdenarArticulos();
    /**
     * @brief Slot que permite la ordenaci�n de la tabla salidas a partir de la selecci�n de su cabecera.
     *
     */
    void refreshOrdenarSalidas();

protected:
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicaci�n, o del sistema, procede a la traducci�n de todos los elementos.
     *
     * @param event Evento del sistema
     */
     void changeEvent(QEvent* event);


private slots:
    /**
     * @brief Slot que confirma una b�squeda.
     *
     */
    void on_pbBuscar_clicked();

    /**
     * @brief Slot que indica que se desea filtrar la b�squeda por c�digo de barras.
     *
     */
    void on_rbCodigoEAN_clicked();

    /**
     * @brief Slot que indica que se desea filtrar la b�squeda por descripci�n.
     *
     */
    void on_rbDescripcion_clicked();

    /**
     * @brief Slot que indica que se desea filtrar la b�squeda por tipo de producto.
     *
     */
    void on_rbTipoProducto_clicked();

    /**
     * @brief Slot que indica que se muestren todos los elementos de la base de datos en la tabla.
     *
     */
    void on_rbMostrarTodos_clicked();

    /**
     * @brief Slot activado cuando se cambia la fecha del calendar widget
     *
     * @param date Fecha actual cambiada
     */
    void on_deDate_dateChanged(const QDate &date);

    /**
     * @brief Slot que se activa cuando se selecciona una fila del QTableView de art�culos
     *
     * @param index Datos de la fila seleccionada
     */
    void on_tvArticulos_clicked(const QModelIndex &index);

private:
    Ui::WidgetSalidasArticulos *ui; /**< TODO */
    QSqlQueryArticulos *mpArticulos; /**< TODO */
    QSqlQuerySalidas *mpSalidas; /**< TODO */
    QString *locale; /**< TODO */
    QString usuarioActivo; /**< TODO */
    QString consultaArt; /**< TODO */
    QString consultaActivaArt; /**< TODO */
    QString consultaSal; /**< TODO */
    QString consultaActivaSal; /**< TODO */
    QHeaderView *headerArt; /**< TODO */
    QHeaderView *headerSal; /**< TODO */
    DialogSalidaArticulo *dsa; /**< TODO */
    QSqlQuery *querySalidas; /**< TODO */
    QTextCharFormat fondoCalendar; /**< TODO */
    QSqlQuery *queryConsulta; /**< TODO */
    QString cad; /**< TODO */

};

#endif // WIDGETSALIDASARTICULOS_H
