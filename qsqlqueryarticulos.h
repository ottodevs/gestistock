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


#ifndef QSQLQUERYARTICULOS_H
#define QSQLQUERYARTICULOS_H

#include <QtGui/QWidget>
#include <QtGui>
#include <QtSql>
#include <QSqlQueryModel>
#include <QSqlRecord>

/**
 * @brief Model de consulta sobre la base de datos.
 *
 */
class QSqlQueryArticulos: public QSqlQueryModel
{
    Q_OBJECT

public:
/**
 * @brief Constructor de la clase
 *
 */
    QSqlQueryArticulos(){}
    /**
     * @brief Permite refrescar la consulta del model.
     *
     * @param consulta Consulta a establecer en el model
     */
    void refrescar(QString consulta);
    /**
     * @brief
     *
     */
    ~QSqlQueryArticulos(){}

private:

};

#endif // QSQLQUERYARTICULOS_H


