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


#ifndef MDIAREA_H
#define MDIAREA_H

#include <QMdiArea>
#include <QResizeEvent>
#include <QPainter>

/**
 * @brief Clase que hereda las características de un QMdiArea, para poder modificar más características de esta.
 *
 */
class MdiArea : public QMdiArea
{
    Q_OBJECT
public:
/**
 * @brief Constructor del MdiArea.
 *
 * @param backgroundImage Imagen de fondo
 * @param backgroundBrush Pincel de fondo
 */
    MdiArea(QImage backgroundImage, QBrush backgroundBrush);

protected:
    /**
     * @brief Captura el evento de redimensionamiento, para poder modificar la imagen, y adaptarla al tamaño.
     *
     * @param resizeEvent Evento de redimensionamiento.
     */
    void resizeEvent(QResizeEvent *resizeEvent);

private:
    QImage i; /**< TODO */
    QBrush b; /**< TODO */
};

#endif // MDIAREA_H
