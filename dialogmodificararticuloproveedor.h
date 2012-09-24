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


#ifndef DIALOGMODIFICARARTICULOPROVEEDOR_H
#define DIALOGMODIFICARARTICULOPROVEEDOR_H

#include <QDialog>
#include <QFileDialog>
#include <QBuffer>
#include <QSqlQuery>
#include <QSqlError>
#include <QTranslator>
#include "widgetarticulosproveedores.h"
#include "qsqlqueryarticulosproveedor.h"

class WidgetArticulosProveedores;

namespace Ui {
class DialogModificarArticuloProveedor;
}

/**
 * @brief Dialog que permite modificar los datos de los artículos de un proveedor.
 *
 */
class DialogModificarArticuloProveedor : public QDialog
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
     * @brief Constructor del diálogo.
     *
     * @param user Usuario que realiza la modificación
     * @param proveedor Proveedor al cual se le realiza la modificación del artículo
     * @param primaryKey Clave primaria del artículo a modificar
     * @param consulta Consulta actual del Model
     * @param mp Model del QTableView articulos de proveedor
     * @param parent Puntero a la ventana padre
     */
    explicit DialogModificarArticuloProveedor(QString user, QString proveedor, QString primaryKey, QString consulta, QSqlQueryArticulosProveedor *mp, QWidget *parent = 0);
    /**
     * @brief Destructor del diálogo
     *
     */
    ~DialogModificarArticuloProveedor();
    
private slots:
    /**
     * @brief Slot que guarda las modificaciones
     *
     */
    void on_pbGuardar_clicked();


    /**
     * @brief Slot que cierra el diálogo
     *
     */
    void on_pbCancelar_clicked();

    /**
     * @brief Slot que detecta si se ha cambiado el texto de un textEdit
     *
     */
    void on_teComentario_textChanged();

    /**
     * @brief Slot que elimina el artículo del proveedor
     *
     */
    void on_pbEliminar_clicked();

private:
    Ui::DialogModificarArticuloProveedor *ui; /**< TODO */
    QSqlQuery *consultaArticulo; /**< TODO */
    QSqlQuery *consultaAuxiliar; /**< TODO */
    QString codEAN; /**< TODO */
    QString consultaAct; /**< TODO */
    QPixmap *imagenArticulo; /**< TODO */
    QSqlQueryArticulosProveedor *model; /**< TODO */
    QTranslator translator; /**< TODO */
    QString usuarioActivo; /**< TODO */
};

#endif // DIALOGMODIFICARARTICULOPROVEEDOR_H
