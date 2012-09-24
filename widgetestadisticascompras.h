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


#ifndef WIDGETESTADISTICASCOMPRAS_H
#define WIDGETESTADISTICASCOMPRAS_H

#include <QWidget>
#include <QPalette>
#include <QCloseEvent>
#include <QDate>
#include <QList>
#include <QTranslator>
#include <qwt_plot.h>
#include <qwt_plot_layout.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_histogram.h>
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_item.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_renderer.h>

#include "windowpantallaopcionesusuario.h"
#include "escalarcurva.h"
#include "escalarhistograma.h"

class WindowPantallaOpcionesUsuario;

namespace Ui {
class WidgetEstadisticasCompras;
}


/**
 * @brief Clase que crea una gráfica tipo histograma
 *
 */
class Histograma: public QwtPlotHistogram
{
public:
/**
 * @brief Constructor de la clase
 *
 * @param title Nombre del histograma
 * @param symbolColor Color determinado
 */
    Histograma(const QString &title, const QColor &symbolColor);
    /**
     * @brief Coloca el color determinado al histograma.
     *
     * @param symbolColor Color determinado
     */
    void setColor(const QColor &symbolColor);
    /**
     * @brief Coloca los valores al histograma.
     *
     * @param numValues Número de valores
     * @param values Valores del histograma
     */
    void setValues(uint numValues, const double *values);
};



/**
 * @brief Clase que permite la integración de un cartel de seguimiento de valores de la gráfica.
 *
 */
class MyPicker: public QwtPlotPicker
{
public:
/**
 * @brief Constructor de la clase
 *
 * @param canvas Lienzo sobre el que se dibujará
 */
    MyPicker(QwtPlotCanvas *canvas):
        QwtPlotPicker(canvas)
    {
        setTrackerMode(AlwaysOn);
    }

    /**
     * @brief Seguimiento del texto
     *
     * @param pos Posición
     * @return QwtText Texto a mostrar
     */
    virtual QwtText trackerTextF(const QPointF &pos) const
    {
        QColor bg(Qt::white);
        bg.setAlpha(200);

        QString texto;


        if(pos.x() < 1)
            texto.append(QObject::tr("Enero,"));
        else if(pos.x() >= 1 && pos.x() < 2)
            texto.append(QObject::tr("Febrero,"));
        else if(pos.x() >= 2 && pos.x() < 3)
            texto.append(QObject::tr("Marzo,"));
        else if(pos.x() >= 3 && pos.x() < 4)
            texto.append(QObject::tr("Abril,"));
        else if(pos.x() > 4 && pos.x() < 5)
            texto.append(QObject::tr("Mayo,"));
        else if(pos.x() > 5 && pos.x() < 6)
            texto.append(QObject::tr("Junio,"));
        else if(pos.x() > 6 && pos.x() < 7)
            texto.append(QObject::tr("Julio,"));
        else if(pos.x() > 7 && pos.x() < 8)
            texto.append(QObject::tr("Agosto,"));
        else if(pos.x() > 8 && pos.x() < 9)
            texto.append(QObject::tr("Septiembre,"));
        else if(pos.x() > 9 && pos.x() < 10)
            texto.append(QObject::tr("Octubre,"));
        else if(pos.x() > 10 && pos.x() < 11)
            texto.append(QObject::tr("Noviembre,"));
        else if(pos.x() > 11)
            texto.append(QObject::tr("Diciembre,"));

        QString ejeY;
        ejeY.setNum(pos.y());

        texto.append(ejeY);

        QwtText text(texto);
        text.setBackgroundBrush( QBrush( bg ));

        return text;
    }
};


/**
 * @brief Widget que muestra una gráfica según los criterios seleccionados.
 *
 */
class WidgetEstadisticasCompras : public QWidget
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
     * @brief Constructor del Widget.
     *
     * @param tipoGrafica Tipo de la gráfica elegida
     * @param tema Tema que tratará la gráfica
     * @param anio1 Año de comparativa
     * @param anio2 Año de comparativa
     * @param parent Puntero a la ventana padre
     */
    explicit WidgetEstadisticasCompras(int tipoGrafica, int tema, QString anio1, QString anio2, QWidget *parent = 0);
    /**
     * @brief Construye una gráfica de tipo histograma.
     *
     */
    void graficaHistograma();
    /**
     * @brief Construye una gráfica de tipo línea.
     *
     * @param tipo Tipo de línea.
     */
    void graficaLineas(int tipo);
    /**
     * @brief Crea las barras del histograma.
     *
     */
    void crearBarras();
    /**
     * @brief Coloca los meses en el eje x de la gráfica.
     *
     * @param indiceMax
     */
    void colocaMes(int indiceMax);
    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetEstadisticasCompras();


private Q_SLOTS:
    /**
     * @brief Slot que permite la aparición o desaparición del contenido de la gráfica.
     *
     * @param item Item de la gráfica
     * @param on Indicador de aparición del item
     */
    void showItem(QwtPlotItem *item, bool on);
    /**
     * @brief Slot que muestra un diálogo de impresión.
     *
     */
    void on_pbImprimir_clicked();
    /**
     * @brief Slot que permite la exportación de las gráficas a diferentes formatos.
     *
     */
    void on_pbExport_clicked();

private:
    Ui::WidgetEstadisticasCompras *ui; /**< TODO */
    QwtPlot *grafica; /**< TODO */
    WindowPantallaOpcionesUsuario *wp; /**< TODO */
    QTranslator translator; /**< TODO */
    QwtPlotPicker *picker; /**< TODO */
    QwtPlotCurve *m_curve; /**< TODO */
    QwtPlotCurve *m_curve2; /**< TODO */
    int tipoGraf; /**< TODO */
    int temaGraf; /**< TODO */
    QString year1; /**< TODO */
    QString year2; /**< TODO */
    int indiceMax; /**< TODO */

};

#endif // WIDGETESTADISTICASCOMPRAS_H
