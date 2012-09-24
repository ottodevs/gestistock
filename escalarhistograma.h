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


#ifndef ESCALARHISTOGRAMA_H
#define ESCALARHISTOGRAMA_H

#include <QVector>
#include <QString>
#include <iostream>

#include "qwt_scale_draw.h"

using namespace std;

/**
 * @brief Clase que introduce los datos del eje x en el histograma.
 *
 */
class EscalarHistograma : public QwtScaleDraw
{
public:
/**
 * @brief Constructor de la clase.
 *
 */
    EscalarHistograma();
    /**
     * @brief Destructor de la clase
     *
     */
    virtual ~EscalarHistograma(){}
    /**
     * @brief Colocar nombres en eje x.
     *
     * @param v Número de nombres
     */
    QwtText label(double v) const;


private:
    QVector <QString> enumeradosMeses; /**< TODO */
    int tipo; /**< TODO */
};

#endif // ESCALARHISTOGRAMA_H
