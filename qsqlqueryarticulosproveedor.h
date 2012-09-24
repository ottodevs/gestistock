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


#ifndef QSQLQUERYARTICULOSPROVEEDOR_H
#define QSQLQUERYARTICULOSPROVEEDOR_H

#include <QtGui/QWidget>
#include <QtGui>
#include <QtSql>
#include <QSqlQueryModel>
#include <QSqlRecord>

/**
 * @brief Model de consulta sobre la base de datos.
 *
 */
class QSqlQueryArticulosProveedor: public QSqlQueryModel
{
    Q_OBJECT

public:
/**
 * @brief Constructor de la clase.
 *
 */
    QSqlQueryArticulosProveedor(){}
    /**
     * @brief Permite refrescar la consult del model según el precio descendente.
     *
     */
    void refrescarPrecioDesc();
    /**
     * @brief Permite refrescar la consult del model según el precio ascendente.
     *
     */
    void refrescarPrecioAsc();
    /**
     * @brief Permite refrescar la consult del model según la descripción descendente.
     *
     */
    void refrescarDescripcionDesc();
    /**
     * @brief Permite refrescar la consult del model según la descripción ascendente.
     *
     */
    void refrescarDescripcionAsc();
    /**
     * @brief Permite refrescar la consult del model según el codigo de barras ascendente.
     *
     */
    void refrescarCodigoEANDesc();
    /**
     * @brief Permite refrescar la consult del model según el codigo ean ascendente.
     *
     */
    void refrescarCodigoEANAsc();
    /**
     * @brief Permite refrescar la consulta del model.
     *
     * @param consulta Consulta a establecer en el model
     */
    void refrescar(QString consulta);
    /**
     * @brief Destructor de la clase.
     *
     */
    ~QSqlQueryArticulosProveedor(){}
};

#endif // QSQLQUERYARTICULOSPROVEEDOR_H
