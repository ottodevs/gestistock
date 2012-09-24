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


#ifndef WINDOWVERARTICULOS_H
#define WINDOWVERARTICULOS_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <QItemDelegate>
#include <QHeaderView>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QTranslator>

#include "qsqlqueryarticulos.h"
#include "windowpantallaopcionesusuario.h"
#include "dialognuevoarticuloalmacen.h"
#include "dialogmodificararticulo.h"
#include "delegatearticulos.h"

class DialogNuevoArticuloAlmacen;
class DialogModificarArticulo;
class WindowPantallaOpcionesUsuario;


namespace Ui {
    class WindowVerArticulos;
}

/**
 * @brief Ventana que a trav�s de una tabla muestra todos los art�culos del almac�n.
 *
 */
class WindowVerArticulos : public QMainWindow
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
     * @brief Constructor de la ventana.
     *
     * @param userActivo Usuario actual de la aplicaci�n.
     * @param parent Puntero a la ventana padre.
     */
    explicit WindowVerArticulos(QString userActivo, QWidget *parent=0);
    /**
     * @brief Evento que detecta todas las pulsaciones de teclas.
     *
     * @param ke Evento de tecla
     */
    void keyReleaseEvent( QKeyEvent *ke);
    /**
     * @brief Rellena el comboBox de los tipos de productos.
     *
     */
    void rellenarCombo();
    /**
     * @brief Destructor de la ventana.
     *
     */
    ~WindowVerArticulos();

private slots:
    /**
     * @brief Slot que muestra el di�logo de nuevo art�culo en almac�n.
     *
     */
    void on_actionNuevo_Articulo_activated();
    /**
     * @brief Slot que permite la ordenacion de las filas de la tabla, previa selecci�n un item de la cabecera en la misma.
     *
     */
    void refresh();
    /**
     * @brief Slot que busca los art�culos del almac�n en base a unos criterios seleccionados.
     *
     */
    void on_pbBuscar_clicked();
    /**
     * @brief Slot que se activa cuando el usuario desea filtrar por tipo de art�culo.
     *
     */
    void on_rbTipoProducto_clicked();
    /**
     * @brief Slot que se activa cuando el usuario desea filtrar por tipo de descripci�n.
     *
     */
    void on_rbDescripcion_clicked();
    /**
     * @brief Slot que se activa cuando el usuario desea mostrar todos los art�culos del almac�n.
     *
     */
    void on_rbMostrarTodos_clicked();
    /**
     * @brief Slot que se activa cuando el usuario desea filtrar por c�digo de barras.
     *
     */
    void on_rbCodigoEAN_clicked();
    /**
     * @brief Slot que se activa cuando el usuario selecciona una fila del table view del alamc�n.
     *
     * @param index Datos de la fila seleccionada.
     */
    void on_tableView_clicked(const QModelIndex &index);
    /**
     * @brief Slot que muestra el di�logo de nuevo art�culo en almac�n.
     *
     */
    void on_pbNuevoArticulo_clicked();


private:
    Ui::WindowVerArticulos *ui; /**< TODO */
    DialogModificarArticulo *ma; /**< TODO */
    DialogNuevoArticuloAlmacen *naa; /**< TODO */
    WindowPantallaOpcionesUsuario *wpu; /**< TODO */
    QString usuarioActivo; /**< TODO */
    QHeaderView *header; /**< TODO */
    QSqlQueryArticulos *mp; /**< TODO */
    QString consultaActiva; /**< TODO */
    QString consulta; /**< TODO */
    QSqlQuery *consultArticulos; /**< TODO */
    QTranslator translator; /**< TODO */

};

#endif // WINDOWVERARTICULOS_H

