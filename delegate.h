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


#ifndef DELEGATE_H
#define DELEGATE_H

#include <QItemDelegate>
#include <QSqlQuery>
#include <QPainter>


/**
 * @brief Clase delegada para la edición de un QTableView.
 *
 */
class Delegate : public QItemDelegate
{
public:
/**
 * @brief Constructor de Delegate.
 *
 * @param parent Puntero al padre
 */
    Delegate(QObject *parent);
    /**
     * @brief Función paint para poder editar cada item del QTableView.
     *
     * @param painter objeto de la clase QPainter
     * @param option objeto de la clase QStyleOptionViewItem
     * @param index datos del item
     */
    void paint(QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DELEGATE_H

