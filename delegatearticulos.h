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


#ifndef DELEGATEARTICULOS_H
#define DELEGATEARTICULOS_H

#include <QItemDelegate>
#include <QPainter>
#include <QSqlQuery>



/**
 * @brief Delegado para editar los items de un QTableView
 *
 */
class DelegateArticulos : public QItemDelegate
{
public:
/**
 * @brief Constructor del delegado.
 *
 * @param parent Puntero a un objeto padre
 */
    DelegateArticulos(QObject *parent);
    /**
     * @brief Sobrecarga de la función paint para poder editar el Item
     *
     * @param painter Objeto QPainter
     * @param option Opciones de estilo
     * @param index Model con los datos del item
     */
    void paint(QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DELEGATEARTICULOS_H
