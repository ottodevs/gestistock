#include "escalarcurva.h"

EscalarCurva::EscalarCurva()
{
    enumeradosMeses.append(QObject::tr("Enero"));
    enumeradosMeses.append(QObject::tr("Febrero"));
    enumeradosMeses.append(QObject::tr("Marzo"));
    enumeradosMeses.append(QObject::tr("Abril"));
    enumeradosMeses.append(QObject::tr("Mayo"));
    enumeradosMeses.append(QObject::tr("Junio"));
    enumeradosMeses.append(QObject::tr("Julio"));
    enumeradosMeses.append(QObject::tr("Agosto"));
    enumeradosMeses.append(QObject::tr("Septiembre"));
    enumeradosMeses.append(QObject::tr("Octubre"));
    enumeradosMeses.append(QObject::tr("Noviembre"));
    enumeradosMeses.append(QObject::tr("Diciembre"));


    //Espaciado con los items del eje x, y la rotacion
    setSpacing(30);
    setLabelRotation(-60.0);

    //Poner las li­neas de la escala
    setTickLength( QwtScaleDiv::MajorTick, 3 );
    setTickLength( QwtScaleDiv::MinorTick, 0 );
    setTickLength( QwtScaleDiv::MediumTick, 6 );

    setLabelAlignment(Qt::AlignBottom);
}


QwtText EscalarCurva::label(double v) const
{
    return enumeradosMeses.at((int)v);
}

