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


#ifndef WIDGETINTRODUCIRCOMPRA_H
#define WIDGETINTRODUCIRCOMPRA_H

#include <QWidget>
#include <QKeyEvent>
#include <QDebug>
#include <QSqlQuery>
#include <QEvent>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

#include "dialogcompras.h"
#include "dialognuevoarticulo.h"
#include "qsqlquerycompras.h"
#include "dialogfechafactura.h"
#include "delegatearticulos.h"

class DialogNuevoArticulo;
class DialogCompras;

namespace Ui {
class WidgetIntroducirCompra;
}

/**
 * @brief Widget que permite la introducción de la compra
 *
 */
class WidgetIntroducirCompra : public QWidget
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor del Widget
     *
     * @param local Puntero al idioma de la aplicación
     * @param user Usuario que introduce la compra
     * @param parent Puntero a la ventana padre
     */
    explicit WidgetIntroducirCompra(QString *local, QString user, QWidget *parent = 0);
    /**
     * @brief Evento que detecta cuando un usuario ha tecleado algo.
     *
     * @param ke Evento de tecla presinada
     */
    void keyReleaseEvent(QKeyEvent *ke);
    /**
     * @brief Rellena los comboBox con el contenido apropiado.
     *
     */
    void rellenarCombos();
    /**
     * @brief Actualiza el idioma del calendar widget.
     *
     * @param idioma Idioma al que se tiene que actualizar
     */
    void actualizarStatus(QString idioma);
    /**
     * @brief Sombrea los días que ha habido compras en el calendario.
     *
     */
    void marcarCalendario();
    /**
     * @brief Inicializa los elementos de la pestaña compras.
     *
     */
    void inicializarTabCompras();
    /**
     * @brief Inicializa los elementos de la ventana almacén
     *
     */
    void inicializarTabAlmacen();
    /**
     * @brief Introduce los tipos de los artículos en su respectivo comboBox.
     *
     */
    void rellenarComboTipos();
    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetIntroducirCompra();
    
protected:
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicación, o del sistema, procede a la traducción de todos los elementos.
     *
     * @param event Evento del sistema
     */
     void changeEvent(QEvent* event);

public slots:
    /**
     * @brief Slot que permite la ordenación del QTableView de compras, a partir del seleccionado de su cabecera.
     *
     */
    void refresh();
    /**
     * @brief Slot que permite la ordenación del QTableView del almacén a partir del seleccionado de su cabecera.
     *
     */
    void refreshOrdenarArticulosAlmacen();


private slots:
    /**
     * @brief Slot que se activa cuando se cambia el índice de un comboBox, en este caso el del proveedor.
     *
     * @param arg1
     */
    void on_cbProveedor_currentIndexChanged(const QString &arg1);

    /**
     * @brief Slot que se activa cuando detecta que la fecha se ha cambiado.
     *
     * @param date Fecha nueva
     */
    void on_deFecha_dateChanged(const QDate &date);

    /**
     * @brief Slot que se activa cuando se selecciona un elemento de un QTableView.
     *
     * @param index Contenido de la fila seleccionada
     */
    void on_tableView_clicked(const QModelIndex &index);

    /**
     * @brief Slot activado cuando se presiona el botón para crear el artículo.
     *
     */
    void on_pbCrearArticulo_clicked();

    /**
     * @brief Slot que permite la introducción de una compra a partir de una factura.
     *
     */
    void on_pbFactura_clicked();

    /**
     * @brief Slot que realiza una búsqueda en el almacén en base a unos criterios.
     *
     */
    void on_pbBuscarAlmacen_clicked();

    /**
     * @brief Slot que se activa cuando se selecciona una fila de una tabla.
     *
     * @param index Datos de la fila seleccionada
     */
    void on_tvArticulosAlmacen_clicked(const QModelIndex &index);

    /**
     * @brief Slot que muestra todos los artículos del almacén en la tabla.
     *
     */
    void on_rbMostrarTodosAlmacen_clicked();

private:
    Ui::WidgetIntroducirCompra *ui; /**< TODO */
    QString cad; /**< TODO */
    QSqlQuery *consultArticulos; /**< TODO */
    DialogCompras *dc; /**< TODO */
    DialogNuevoArticulo *dna; /**< TODO */
    QString usuarioActivo; /**< TODO */
    QSqlQuery *consult; /**< TODO */
    QStringList *items; /**< TODO */
    QString *locale; /**< TODO */
    QHeaderView *header; /**< TODO */
    QSqlQueryCompras *mp; /**< TODO */
    QString consultaActiva; /**< TODO */
    QString consulta; /**< TODO */
    QSqlQuery *consultAux; /**< TODO */
    QTextCharFormat fondoCalendar; /**< TODO */
    QTranslator translator; /**< TODO */
    DialogFechaFactura *dff; /**< TODO */
    QString consultaActivaArt; /**< TODO */
    QString consultaArt; /**< TODO */
    QHeaderView *headerArt; /**< TODO */
    QSqlQueryArticulos *mpAlmacen; /**< TODO */
    QString cifProveedor; /**< TODO */

};

#endif // WIDGETINTRODUCIRCOMPRA_H
