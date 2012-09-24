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


#ifndef DIALOGANYADIRARTICULOPROVEEDOR_H
#define DIALOGANYADIRARTICULOPROVEEDOR_H

#include <QDialog>

#include "qsqlqueryarticulosproveedor.h"

namespace Ui {
class DialogAnyadirArticuloProveedor;
}



/**
 * @brief Diálogo que permite añadir un artículo a un proveedor.
 *
 */
class DialogAnyadirArticuloProveedor : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor del diálogo para añadir un artículo a un proveedor.
     *
     * @param primaryKey Clave primaria del artículo
     * @param mp Puntero al modelo que trabaja contra la base de datos en el QTableView
     * @param consulta Consulta actual de la tabla de la ventana padre
     * @param parent Puntero a la ventana padre
     */
    explicit DialogAnyadirArticuloProveedor(QString primaryKey, QSqlQueryArticulosProveedor *mp, QString consulta, QWidget *parent = 0);
    /**
     * @brief Destructor de la clase DialogAnyadirArticuloProveedor.
     *
     */
    ~DialogAnyadirArticuloProveedor();
    
private slots:
    /**
     * @brief Slot que se activa al presionar el botón Cancelar, cierra la ventana.
     *
     */
    void on_pbCancelar_clicked();
    /**
     * @brief Slot que se activa al presionar el botón Guardar, guarda los cambios realizados.
     *
     */
    void on_pbGuardar_clicked();
    /**
     * @brief Slot que se activa al cambiar el comboBox, devuelve el argumento del índice actual.
     *
     * @param arg1 Parámetro que determina que valor ha cambiado en el comboBox
     */
    void on_cbProveedorArticulo_currentIndexChanged(const QString &arg1);
    /**
     * @brief Función que inicializa el comboBox.
     *
     */
    void inicializarCombo();

protected:
    /**
     * @brief Utilizada para capturar el evento de cambio de idioma.
     *
     * @param event Evento del sistema
     */
    void changeEvent(QEvent* event);

private:
    Ui::DialogAnyadirArticuloProveedor *ui; /**< TODO */
    QSqlQueryArticulosProveedor *mpArticulosProveedor; /**< TODO */
    QString consultaModel; /**< TODO */
    QString codigoEAN; /**< TODO */
    QPixmap *imagenArticulo; /**< TODO */
    QSqlQuery *actImagen; /**< TODO */
    QSqlQuery *consult; /**< TODO */
    bool existeArticuloProveedor; /**< TODO */
};

#endif // DIALOGANYADIRARTICULOPROVEEDOR_H
