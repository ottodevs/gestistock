#include "widgetestadisticascompras.h"
#include "ui_widgetestadisticascompras.h"


Histograma::Histograma(const QString &title, const QColor &symbolColor):
    QwtPlotHistogram(title)
{
    setStyle(QwtPlotHistogram::Columns);
    setColor(symbolColor);
}

void Histograma::setColor(const QColor &symbolColor)
{
    QColor color = symbolColor;
    color.setAlpha(180);

    setPen(QPen(Qt::black));
    setBrush(QBrush(color));

    QwtColumnSymbol *symbol = new QwtColumnSymbol(QwtColumnSymbol::Box);
    symbol->setFrameStyle(QwtColumnSymbol::Raised);
    symbol->setLineWidth(2);
    symbol->setPalette(QPalette(color));
    setSymbol(symbol);
}


void Histograma::setValues(uint numValues, const double *values)
{
    QVector<QwtIntervalSample> samples(numValues);
    for ( uint i = 0; i < numValues; i++ )
    {
        QwtInterval interval(double(i), i + 1.0);
        interval.setBorderFlags(QwtInterval::ExcludeMaximum);
        samples[i] = QwtIntervalSample(values[i], interval);
    }

    setData(new QwtIntervalSeriesData(samples));
}



WidgetEstadisticasCompras::WidgetEstadisticasCompras(int tipoGrafica, int tema, QString anio1, QString anio2, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetEstadisticasCompras)
{
    ui->setupUi(this);

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logo.png"));

    this->setWindowTitle(tr("Estadísticas"));

    this->setFixedHeight(this->parentWidget()->size().height() - 2);

    //Guardamos los parametros
    tipoGraf = tipoGrafica;
    temaGraf = tema;
    year1 = anio1;
    year2 = anio2;
    indiceMax = 0;


    if(temaGraf == -2)
        grafica = new QwtPlot(tr("Dinero invertido"));
    else if(temaGraf == -3)
        grafica = new QwtPlot(tr("Cantidad de compras"));
    else
        grafica = new QwtPlot(tr("Salidas artículos"));


    //Bloqueamos el boton de maximizar
    //this->setWindowFlags(windowFlags() ^ Qt::WindowMaximizeButtonHint);


    grafica->setCanvasBackground(QColor(Qt::lightGray));
    //grafica->plotLayout()->setAlignCanvasToScales(true);


    //La rejilla de fondo
    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableX(true);
    grid->enableY(true);
    grid->enableXMin(false);
    grid->enableYMin(false);
    grid->setMajPen(QPen(Qt::black, 0, Qt::DotLine));
    //grid->AutoScale;
    grid->attach(grafica);


    //grafica->setAxisTitle(QwtPlot::yLeft, tr("Euros"));
    //grafica->setAxisTitle(QwtPlot::xBottom, "Mes");

    //Dibujamos la gráfica que queramos
    if(tipoGraf == -6)
        graficaHistograma();
    else
        graficaLineas(tipoGraf);


    picker = new MyPicker(grafica->canvas());

    grafica->replot();

    //Tamaño de la grafica
    grafica->setFixedSize(600,400);

    ui->gridLayout_2->addWidget(grafica);

}

void WidgetEstadisticasCompras::crearBarras()
{
    Histograma *histogram = new Histograma(year1, Qt::red);
    Histograma *histogram1 = new Histograma(year2, Qt::yellow);

    QSqlQuery meses,meses2;
    double valores[] = {0,0,0,0,0,0,0,0,0,0,0,0};
    double valores2[] = {0,0,0,0,0,0,0,0,0,0,0,0};

    int i = 0;
    double max = 0;


    //Si es de compras
    if(temaGraf == -2)
    {
        if(year1 == year2)
        {
            meses.exec("SELECT MONTH(fecha), sum((precio + (precio * (iva/100)))*cantidad) FROM compraproductos WHERE YEAR(fecha) = '"+year1+"' GROUP BY MONTH(fecha)");

            while(meses.next())
                valores[(meses.value(0).toInt() - 1)] = meses.value(1).toDouble();


            while(i < 12)
            {
                if(max < valores[i]){
                    max = valores[i];
                    indiceMax = i;
                }

                i++;
            }

            //histogram->AutoScale;
            histogram->setValues(sizeof(valores) / sizeof(double), valores);
            //Metemos en la gráfica
            histogram->attach(grafica);


        }else{

            meses.exec("SELECT MONTH(fecha), sum((precio + (precio * (iva/100)))*cantidad) FROM compraproductos WHERE YEAR(fecha) = '"+year1+"' GROUP BY MONTH(fecha)");

            while(meses.next())
                valores[(meses.value(0).toInt() - 1)] = meses.value(1).toDouble();

            meses2.exec("SELECT MONTH(fecha), sum((precio + (precio * (iva/100)))*cantidad) FROM compraproductos WHERE YEAR(fecha) = '"+year2+"' GROUP BY MONTH(fecha)");

            while(meses2.next())
                valores2[(meses2.value(0).toInt() - 1)] = meses2.value(1).toDouble();


            while(i < 12)
            {
                if(max < valores[i]){
                    max = valores[i];
                    indiceMax = i;
                }

                if(max < valores2[i]){
                    max = valores2[i];
                    indiceMax = i;
                }

                i++;
            }

            //histogram->AutoScale;
            histogram->setValues(sizeof(valores) / sizeof(double), valores);
            //Metemos en la gráfica
            histogram->attach(grafica);

            //histogram->AutoScale;
            histogram1->setValues(sizeof(valores2) / sizeof(double), valores2);
            //Metemos en la gráfica
            histogram1->attach(grafica);
        }

    }else if (temaGraf == -3){

        if(year1 == year2)
        {
            meses.exec("SELECT MONTH(fecha), sum(cantidad) FROM compraproductos WHERE YEAR(fecha) = '"+year2+"' GROUP BY MONTH(fecha)");

            while(meses.next())
                valores[(meses.value(0).toInt() - 1)] = meses.value(1).toDouble();


            while(i < 12)
            {
                if(max < valores[i]){
                    max = valores[i];
                    indiceMax = i;
                }

                i++;
            }

            //histogram->AutoScale;
            histogram->setValues(sizeof(valores) / sizeof(double), valores);
            //Metemos en la gráfica
            histogram->attach(grafica);


        }else{

            meses.exec("SELECT MONTH(fecha), sum(cantidad) FROM compraproductos WHERE YEAR(fecha) = '"+year1+"' GROUP BY MONTH(fecha)");

            while(meses.next())
                valores[(meses.value(0).toInt() - 1)] = meses.value(1).toDouble();

            meses2.exec("SELECT MONTH(fecha), sum(cantidad) FROM compraproductos WHERE YEAR(fecha) = '"+year2+"' GROUP BY MONTH(fecha)");

            while(meses2.next())
                valores2[(meses2.value(0).toInt() - 1)] = meses2.value(1).toDouble();


            while(i < 12)
            {
                if(max < valores[i]){
                    max = valores[i];
                    indiceMax = i;
                }

                if(max < valores2[i]){
                    max = valores2[i];
                    indiceMax = i;
                }

                i++;
            }

            //histogram->AutoScale;
            histogram->setValues(sizeof(valores) / sizeof(double), valores);
            //Metemos en la gráfica
            histogram->attach(grafica);

            //histogram->AutoScale;
            histogram1->setValues(sizeof(valores2) / sizeof(double), valores2);
            //Metemos en la gráfica
            histogram1->attach(grafica);
        }

    }else if(temaGraf == -4){

        if(year1 == year2)
        {
            meses.exec("SELECT MONTH(fecha), sum(cantidad) FROM salidasarticulos WHERE YEAR(fecha) = '"+year1+"' GROUP BY MONTH(fecha)");

            while(meses.next())
                valores[(meses.value(0).toInt() - 1)] = meses.value(1).toDouble();


            while(i < 12)
            {
                if(max < valores[i]){
                    max = valores[i];
                    indiceMax = i;
                }

                i++;
            }

            //histogram->AutoScale;
            histogram->setValues(sizeof(valores) / sizeof(double), valores);
            //Metemos en la gráfica
            histogram->attach(grafica);


        }else{

            meses.exec("SELECT MONTH(fecha), sum(cantidad) FROM salidasarticulos WHERE YEAR(fecha) = '"+year1+"' GROUP BY MONTH(fecha)");

            while(meses.next())
                valores[(meses.value(0).toInt() - 1)] = meses.value(1).toDouble();

            meses2.exec("SELECT MONTH(fecha), sum(cantidad) FROM salidasarticulos WHERE YEAR(fecha) = '"+year2+"' GROUP BY MONTH(fecha)");

            while(meses2.next())
                valores2[(meses2.value(0).toInt() - 1)] = meses2.value(1).toDouble();


            while(i < 12)
            {
                if(max < valores[i]){
                    max = valores[i];
                    indiceMax = i;
                }

                if(max < valores2[i]){
                    max = valores2[i];
                    indiceMax = i;
                }

                i++;
            }

            //histogram->AutoScale;
            histogram->setValues(sizeof(valores) / sizeof(double), valores);
            //Metemos en la gráfica
            histogram->attach(grafica);

            //histogram->AutoScale;
            histogram1->setValues(sizeof(valores2) / sizeof(double), valores2);
            //Metemos en la gráfica
            histogram1->attach(grafica);
        }

    }


    //Establecemos la escala del eje y para que no sea autoescalada
    grafica->setAxisScale(grafica->yLeft,0,max,max/10);

    ui->leResultado->setText(QString::number(max));

    //Coloca el mes en el lineEdit
    colocaMes(indiceMax);

}

void WidgetEstadisticasCompras::showItem(QwtPlotItem *item, bool on)
{
    item->setVisible(on);
}


WidgetEstadisticasCompras::~WidgetEstadisticasCompras()
{
    delete ui;
}

void WidgetEstadisticasCompras::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
        {
            //Volvemos a dibujar el eje x
            grafica->setAxisScaleDraw(QwtPlot::xBottom,new EscalarHistograma());
            ui->retranslateUi(this);

        }
    }

    QWidget::changeEvent(event);
}



void WidgetEstadisticasCompras::graficaHistograma()
{
    QwtLegend *legend = new QwtLegend;
    legend->setItemMode(QwtLegend::CheckableItem);

    //Numeros de items del eje x
    grafica->setAxisScale(grafica->xBottom,0,12,1);

    //Establecemos la escala del eje y para que no sea autoescalada
    //grafica->setAxisScale(grafica->yLeft,0,300,100);

    //Nombres del eje x
    grafica->setAxisScaleDraw(QwtPlot::xBottom,new EscalarHistograma());

    grafica->setLineWidth(5);

    grafica->insertLegend(legend, QwtPlot::RightLegend);

    grafica->plotLayout()->setAlignCanvasToScales(true);

    //Valores
    crearBarras();

    connect(grafica, SIGNAL(legendChecked(QwtPlotItem *, bool)), SLOT(showItem(QwtPlotItem *, bool)));

    //Creamos las leyendas
    grafica->replot();

    QwtPlotItemList items = grafica->itemList(QwtPlotItem::Rtti_PlotHistogram);
    for ( int i = 0; i < items.size(); i++ )
    {
        if ( i == 0 )
        {
            QwtLegendItem *legendItem = (QwtLegendItem *)legend->find(items[i]);
            if ( legendItem )
                legendItem->setChecked(true);
            items[i]->setVisible(true);
        }
        else
            items[i]->setVisible(false);
    }

    grafica->setAutoReplot(true);

}




void WidgetEstadisticasCompras::graficaLineas(int tipo)
{
    QSqlQuery meses,meses2;

    double x[12]={0,1,2,3,4,5,6,7,8,9,10,11};

    double valores[]= {0,0,0,0,0,0,0,0,0,0,0,0};
    double valores2[] = {0,0,0,0,0,0,0,0,0,0,0,0};

    int i = 0;
    double max = 0;

    //Numeros de items del eje x
    grafica->setAxisScale(grafica->xBottom,0,11,1);

    //Establecemos la escala del eje y para que no sea autoescalada
    //grafica->setAxisScale(grafica->yLeft,0,300,100);

    //Nombres del eje x
    grafica->setAxisScaleDraw(QwtPlot::xBottom,new EscalarCurva());

    grafica->setLineWidth(5);

    m_curve = new QwtPlotCurve(year1);
    m_curve2 = new QwtPlotCurve(year2);

    //Margenes
    grafica->plotLayout()->setCanvasMargin(0,QwtPlot::yRight);
    grafica->plotLayout()->setCanvasMargin(5,QwtPlot::yLeft);
    grafica->plotLayout()->setCanvasMargin(4,QwtPlot::xBottom);
    grafica->plotLayout()->setCanvasMargin(6,QwtPlot::xTop);



    //Tipo de linea
    if(tipo == -2){

        //Estilo de linea
        m_curve->setSymbol(new QwtSymbol(QwtSymbol::Diamond, Qt::red, QPen(Qt::red), QSize(10, 10) ) );
        m_curve->setPen(QColor(Qt::red));
        m_curve->setStyle(QwtPlotCurve::Lines);

        //Estilo de linea
        m_curve2->setSymbol(new QwtSymbol(QwtSymbol::Diamond, Qt::blue, QPen(Qt::blue), QSize(10, 10) ) );
        m_curve2->setPen(QColor(Qt::blue));
        m_curve2->setStyle(QwtPlotCurve::Lines);

    }else if(tipo == -3)
    {
        //Estilo de la linea
        m_curve->setSymbol(new QwtSymbol(QwtSymbol::Ellipse,Qt::red,QPen(Qt::black),QSize(10, 10)));
        m_curve->setStyle(QwtPlotCurve::Sticks);
        //Color y grosor de la linea
        m_curve->setPen(QPen(Qt::red,2));

        //Estilo de la linea
        m_curve2->setSymbol(new QwtSymbol(QwtSymbol::Ellipse,Qt::blue,QPen(Qt::black),QSize(10, 10)));
        m_curve2->setStyle(QwtPlotCurve::Sticks);
        //Color y grosor de la linea
        m_curve2->setPen(QPen(Qt::blue,2));

    }else if(tipo == -4)
    {
        //Otro tipo
        m_curve->setPen(QPen(Qt::red,3));
        m_curve->setStyle(QwtPlotCurve::Steps);

        //Otro tipo
        m_curve2->setPen(QPen(Qt::blue,3));
        m_curve2->setStyle(QwtPlotCurve::Steps);

    }else if(tipo == -5)
    {
        //Otro tipo de linea, sin suavizado, eliminar el Fitted
        m_curve->setPen(QPen(Qt::red,3));
        m_curve->setStyle(QwtPlotCurve::Lines);
        m_curve->setRenderHint(QwtPlotItem::RenderAntialiased);

        //Otro tipo de linea, sin suavizado, eliminar el Fitted
        m_curve2->setPen(QPen(Qt::blue,3));
        m_curve2->setStyle(QwtPlotCurve::Lines);
        m_curve2->setRenderHint(QwtPlotItem::RenderAntialiased);

    }else if(tipo == -7)
    {
        //Otro tipo
        m_curve->setSymbol(new QwtSymbol(QwtSymbol::XCross, Qt::NoBrush, QPen(Qt::red,2), QSize(5, 5) ) );
        m_curve->setStyle(QwtPlotCurve::NoCurve);

        //Otro tipo
        m_curve2->setSymbol(new QwtSymbol(QwtSymbol::XCross, Qt::NoBrush, QPen(Qt::blue,2), QSize(5, 5) ) );
        m_curve2->setStyle(QwtPlotCurve::NoCurve);
    }


    //Sin suavizado
    m_curve->setRenderHint(QwtPlotItem::RenderAntialiased);
    m_curve2->setRenderHint(QwtPlotItem::RenderAntialiased);


    if(temaGraf == -2)
    {
        if(year1 == year2)
        {

            meses.exec("SELECT MONTH(fecha), sum((precio + (precio * (iva/100)))*cantidad) FROM compraproductos WHERE YEAR(fecha) = '"+year1+"' GROUP BY MONTH(fecha)");

            while(meses.next())
                valores[(meses.value(0).toInt() - 1)] = meses.value(1).toDouble();

            m_curve->setSamples(x,valores,12);

            //Metemos la curva en la grafica
            m_curve->attach(grafica);


        }else{

            meses.exec("SELECT MONTH(fecha), sum((precio + (precio * (iva/100)))*cantidad) FROM compraproductos WHERE YEAR(fecha) = '"+year1+"' GROUP BY MONTH(fecha)");

            while(meses.next())
                valores[(meses.value(0).toInt() - 1)] = meses.value(1).toDouble();

            meses2.exec("SELECT MONTH(fecha), sum((precio + (precio * (iva/100)))*cantidad) FROM compraproductos WHERE YEAR(fecha) = '"+year2+"' GROUP BY MONTH(fecha)");

            while(meses2.next())
                valores2[(meses2.value(0).toInt() - 1)] = meses2.value(1).toDouble();

            //Rellenamos los datos
            m_curve->setSamples(x,valores,12);
            m_curve2->setSamples(x,valores2,12);

            //Metemos la curva en la grafica
            m_curve->attach(grafica);
            m_curve2->attach(grafica);
        }

    }else if(temaGraf == -3){

        if(year1 == year2)
        {
            meses.exec("SELECT MONTH(fecha), sum(cantidad) FROM compraproductos WHERE YEAR(fecha) = '"+year1+"' GROUP BY MONTH(fecha)");

            while(meses.next())
                valores[(meses.value(0).toInt() - 1)] = meses.value(1).toDouble();


            //Rellenamos los datos
            m_curve->setSamples(x,valores,12);

            //Metemos la curva en la grafica
            m_curve->attach(grafica);


        }else{

            meses.exec("SELECT MONTH(fecha), sum(cantidad) FROM compraproductos WHERE YEAR(fecha) = '"+year2+"' GROUP BY MONTH(fecha)");

            while(meses.next())
                valores[(meses.value(0).toInt() - 1)] = meses.value(1).toDouble();

            meses2.exec("SELECT MONTH(fecha), sum(precio + (precio * (iva/100))) FROM compraproductos WHERE YEAR(fecha) = '"+year2+"' GROUP BY MONTH(fecha)");

            while(meses2.next())
                valores2[(meses2.value(0).toInt() - 1)] = meses2.value(1).toDouble();


            //Rellenamos los datos
            m_curve->setSamples(x,valores,12);
            m_curve2->setSamples(x,valores2,12);

            //Metemos la curva en la grafica
            m_curve->attach(grafica);
            m_curve2->attach(grafica);
        }

    }else if(temaGraf == -4){

        if(year1 == year2)
        {
            meses.exec("SELECT MONTH(fecha), sum(cantidad) FROM salidasarticulos WHERE YEAR(fecha) = '"+year1+"' GROUP BY MONTH(fecha)");

            while(meses.next())
                valores[(meses.value(0).toInt() - 1)] = meses.value(1).toDouble();



            //Rellenamos los datos
            m_curve->setSamples(x,valores,12);

            //Metemos la curva en la grafica
            m_curve->attach(grafica);


        }else{

            meses.exec("SELECT MONTH(fecha), sum(cantidad) FROM salidasarticulos WHERE YEAR(fecha) = '"+year1+"' GROUP BY MONTH(fecha)");

            while(meses.next())
                valores[(meses.value(0).toInt() - 1)] = meses.value(1).toDouble();

            meses2.exec("SELECT MONTH(fecha), sum(cantidad) FROM salidasarticulos WHERE YEAR(fecha) = '"+year2+"' GROUP BY MONTH(fecha)");

            while(meses2.next())
                valores2[(meses2.value(0).toInt() - 1)] = meses2.value(1).toDouble();


            //Rellenamos los datos
            m_curve->setSamples(x,valores,12);
            m_curve2->setSamples(x,valores2,12);

            //Metemos la curva en la grafica
            m_curve->attach(grafica);
            m_curve2->attach(grafica);
        }

    }


    //Buscamos el maximo, y el indice de ese maximo
    while(i < 12)
    {
        if(max < valores[i]){
            max = valores[i];
            indiceMax = i;
        }

        if(max < valores2[i]){
            max = valores2[i];
            indiceMax = i;
        }

        i++;
    }


    //Establecemos la escala del eje y para que no sea autoescalada
    grafica->setAxisScale(grafica->yLeft,0,max,max/10);


    //Leyendas
    QwtLegend *legend = new QwtLegend;
    legend->setItemMode(QwtLegend::CheckableItem);
    grafica->insertLegend(legend, QwtPlot::RightLegend);

    //Para poder hacer aparecer y desaparecer la curva
    connect(grafica, SIGNAL(legendChecked(QwtPlotItem *, bool)),
        SLOT(showItem(QwtPlotItem *, bool)));

    //Crea los legend items
    grafica->replot();

    QwtPlotItemList items = grafica->itemList(QwtPlotItem::Rtti_PlotCurve);
    qDebug() << items.size();
    for ( int i = 0; i < items.size(); i++ )
    {
        if ( i == 0 )
        {
            QwtLegendItem *legendItem = (QwtLegendItem *)legend->find(items[i]);
            if (legendItem)
                legendItem->setChecked(true);
            items[i]->setVisible(true);
        }
        else
            items[i]->setVisible(false);
    }

    grafica->setAutoReplot(true);
    //Fin de hacer aparecer y desaparecer la curva


    ui->leResultado->setText(QString::number(max));

    //Coloca el mes en el lineEdit
    colocaMes(indiceMax);
}


void WidgetEstadisticasCompras::colocaMes(int indiceMax)
{
    if(indiceMax == 0)
        ui->leMayor->setText(tr("Enero"));
    else if(indiceMax == 1)
        ui->leMayor->setText(tr("Febrero"));
    else if(indiceMax == 2)
        ui->leMayor->setText(tr("Marzo"));
    else if(indiceMax == 3)
        ui->leMayor->setText(tr("Abril"));
    else if(indiceMax == 4)
        ui->leMayor->setText(tr("Mayo"));
    else if(indiceMax == 5)
        ui->leMayor->setText(tr("Junio"));
    else if(indiceMax == 6)
        ui->leMayor->setText(tr("Julio"));
    else if(indiceMax == 7)
        ui->leMayor->setText(tr("Agosto"));
    else if(indiceMax == 8)
        ui->leMayor->setText(tr("Septiembre"));
    else if(indiceMax == 9)
        ui->leMayor->setText(tr("Octubre"));
    else if(indiceMax == 10)
        ui->leMayor->setText(tr("Noviembre"));
    else if(indiceMax == 11)
        ui->leMayor->setText(tr("Diciembre"));
}

void WidgetEstadisticasCompras::on_pbImprimir_clicked()
{
    QPrinter printer(QPrinter::HighResolution);

    QString docName = "nombre";
    if ( !docName.isEmpty() )
    {
        docName.replace (QRegExp (QString::fromLatin1 ("\n")), tr (" -- "));
        printer.setDocName (docName);
    }

    printer.setCreator(tr("Gráfica"));
    printer.setOrientation(QPrinter::Landscape);

    QPrintDialog dialog(&printer);
    if ( dialog.exec() )
    {
        QwtPlotRenderer renderer;

        if ( printer.colorMode() == QPrinter::GrayScale )
        {
            renderer.setDiscardFlag(QwtPlotRenderer::DiscardCanvasBackground);
            renderer.setLayoutFlag(QwtPlotRenderer::FrameWithScales);
        }

        renderer.renderTo(grafica, printer);
    }
}


void WidgetEstadisticasCompras::on_pbExport_clicked()
{
    QString fileName = tr("Grafica.pdf");

#ifndef QT_NO_FILEDIALOG
    const QList<QByteArray> imageFormats =
        QImageWriter::supportedImageFormats();

    QStringList filter;
    filter += tr("PDF Documentos (*.pdf)");

#ifndef QWT_NO_SVG
    filter += tr("SVG Documentos (*.svg)");
#endif
    filter += tr("Postscript Documentos (*.ps)");

    if ( imageFormats.size() > 0 )
    {
        QString imageFilter(tr("Imagenes ("));
        for ( int i = 0; i < imageFormats.size(); i++ )
        {
            if ( i > 0 )
                imageFilter += " ";
            imageFilter += "*.";
            imageFilter += imageFormats[i];
        }
        imageFilter += ")";

        filter += imageFilter;
    }

    fileName = QFileDialog::getSaveFileName(
        this, tr("Guardar archivo"), fileName,
        filter.join(";;"), NULL, QFileDialog::DontConfirmOverwrite);
#endif
    if ( !fileName.isEmpty() )
    {
        QwtPlotRenderer renderer;
        renderer.renderDocument(grafica, fileName, QSizeF(300, 200), 85);
    }

}
