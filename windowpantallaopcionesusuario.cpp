#include "windowpantallaopcionesusuario.h"
#include "ui_windowpantallaopcionesusuario.h"


WindowPantallaOpcionesUsuario::WindowPantallaOpcionesUsuario(QString local,const QString userActivo, WindowCargarDatos *wcd, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowPantallaOpcionesUsuario)
{
    ui->setupUi(this);

    //Titulo
    this->setWindowTitle(tr("Inicio"));
    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logoSolo.png"));

    mdiArea = new MdiArea(QImage(":/imagenes/logo.png"),Qt::lightGray);
    //Qt::darkGray

    usuarioActivo = userActivo;

    nombreHost = QSqlDatabase::database().hostName();

    //Si estamos conectado a un servidor, desactivamos la posibilidad de hacer copias de seguridad
    if(nombreHost != "localhost")
    {
        ui->actionCopia_de_Seguridad->setEnabled(false);
        ui->actionCopia_de_Seguridad_2->setEnabled(false);
        ui->actionRestaurar_Copia_de_Seguridad->setEnabled(false);
    }


    subWin = NULL;

    //Guardamos el puntero a la pantalla de inicio
    pwcd = wcd;

    //Colocamos el cierre inicialmente a falso
    confirmarCierre = false;

    //Colocación de statusBar
    etiquetaFecha = new QLabel(this);
    etiquetaHora = new QLabel (this);
    etiquetaIdioma = new QLabel(this);
    etiquetaNombre = new QLabel(this);


    etiquetaIdioma->setAlignment(Qt::AlignCenter);
    etiquetaIdioma->setMinimumWidth(200);
    //etiquetaIdioma->setText("Español(ES)");


    //Actualizamos la fecha para ponerla en la statusBar
    this->actualizarStatus(locale);

    etiquetaHora->setAlignment(Qt::AlignCenter);
    etiquetaHora->setMinimumWidth(50);


    etiquetaNombre->setAlignment(Qt::AlignCenter);
    etiquetaNombre->setMinimumWidth(200);
    etiquetaNombre->setText("GestiStock Software 2012");


    //Activamos
    this->hora();

    timer = new QTimer(this);
    connect (timer, SIGNAL(timeout()), this, SLOT(hora()));
    timer->start(1000);

    ui->statusBar->addPermanentWidget(etiquetaNombre,1);
    ui->statusBar->addPermanentWidget(etiquetaIdioma,0);
    ui->statusBar->addPermanentWidget(etiquetaFecha,0);
    ui->statusBar->addPermanentWidget(etiquetaHora,0);


    //Reservamos memoria
    cnslt = new QSqlQuery;

    QSqlQuery consulta;
    consulta.exec("SELECT dni FROM usuarios WHERE nombreusuario = '"+this->usuarioActivo+"' ");
    consulta.first();

    //Guardamos la hora actual que marcaremos como entrada
    dateTimeInicio = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    cnslt->exec("INSERT INTO conexiones VALUES('"+dateTimeInicio+"', '"+consulta.value(0).toString()+"', '"+dateTimeInicio+"') ");

    //colocarReloj();

    //Ajustar la MdiArea al tamano de la pantalla.
    this->setCentralWidget(mdiArea);

    locale = local;

    qDebug() << locale;

    if(locale == "es")
        ui->actionEspa_ol->setChecked(true);
    else
        ui->actionIngl_s->setChecked(true);

    actualizarStatus(locale);


    //Comprobamos privilegios de usuario
    comprobarPrivilegios();


    qDebug() << mdiArea->size();

}

void WindowPantallaOpcionesUsuario::comprobarPrivilegios()
{
    QSqlQuery comprobar;
    comprobar.exec("SELECT superusuario FROM usuarios WHERE nombreusuario = '"+usuarioActivo+"' ");
    comprobar.first();

    //Si no es superusuario...
    if(comprobar.value(0).toInt() == 0)
    {
        ui->actionConexiones->setEnabled(false);
        ui->actionCopia_de_Seguridad->setEnabled(false);
        ui->actionCopia_de_Seguridad_2->setEnabled(false);
        ui->actionRestaurar_Copia_de_Seguridad->setEnabled(false);
        ui->actionActividad_Usuario->setEnabled(false);
        ui->actionMostrar_usuarios->setEnabled(false);
        ui->actionUsuarios->setEnabled(false);
        ui->actionModificar_Datos->setEnabled(false);

    }

}

void WindowPantallaOpcionesUsuario::hora()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");

    etiquetaHora->setText("  " + text + "  ");
}



//Si cerramos la ventana...
void WindowPantallaOpcionesUsuario::closeEvent(QCloseEvent *ev)
{
    QMessageBox msgBox(this);

    msgBox.setWindowTitle(tr("Cerrar"));
    msgBox.setText(tr("Cerrar Sesión                                               "));
    msgBox.setInformativeText(tr("¿Está seguro de abandonar la sesión?"));
    msgBox.setIcon(QMessageBox::Question);
    msgBox.addButton(tr("Si"),QMessageBox::AcceptRole);

    //Guardamos el boton en una variable para despues hacerlo por defecto
    QPushButton *pb = msgBox.addButton(tr("No"),QMessageBox::RejectRole);

    //Por defecto el boton que saldra sombreado
    msgBox.setDefaultButton(pb);


    if(!confirmarCierre)
    {
        //Si la respuesta es no...
        if(msgBox.exec())
            ev->ignore();
        else{
            cerrarSesion();
            pwcd->consultarIdioma();
            pwcd->show();
        }

    }else{
        pwcd->consultarIdioma();
        pwcd->show();
    }
}

void WindowPantallaOpcionesUsuario::cerrarSesion()
{
    //Limpiamos la consulta
    cnslt->clear();
    //Guardamos la hora de salida del programa
    //Para trabajar la consulta de QDateTime con mysql tenemos que hacerlo asi para que funcione
    cnslt->exec("UPDATE conexiones SET fechasalida= '"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"' WHERE fechaentrada= '"+this->dateTimeInicio+"' ");

    //Guardamos el idioma a la salida
    cnslt->clear();
    cnslt->exec("UPDATE `configuracion` SET `idioma` = '"+locale+"' ");
}


void WindowPantallaOpcionesUsuario::on_actionSalir_activated()
{
    //Llamamos al evento de cierre
    this->close();
}


void WindowPantallaOpcionesUsuario::on_actionAlmac_n_activated()
{
    //Reserva de memoria
    va = new WindowVerArticulos(usuarioActivo,mdiArea);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    //centramos en el QMdiArea
    //mdiArea->addSubWindow(va)->move((mdiArea->size().width() - va->size().width())/2,0);

    //mdiArea->addSubWindow(va)->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, va->size(), qApp->desktop()->availableGeometry()));


    //mdiArea->addSubWindow(wtp);//->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, wtp->size(), qApp->desktop()->availableGeometry()));
   subWin = mdiArea->addSubWindow(va);

   //Movemos la ventana
   subWin->move((mdiArea->size().width() - va->size().width())/2,0);

   //Bloquea el boton de maximizar en la subventana
   //subWin->setWindowFlags(subWin->windowFlags() & ~Qt::WindowMaximizeButtonHint);

   //subWin->setFixedSize(subWin->size());

   subWin->setFixedHeight(mdiArea->size().height());
   subWin->setMinimumSize(subWin->size());

   subWin->show();

   //Mostramos la ventana
   //va->show();

}

void WindowPantallaOpcionesUsuario::on_actionOpciones_Usuario_activated()
{
    //Cerramos las ventanas del mdiArea
    mdiArea->closeAllSubWindows();

    //Reserva de memoria, y pasamos al constructor la clave primaria
    dmu = new DialogModificarUsuario(usuarioActivo,this);

    //Mostramos la ventana
    dmu->setVisible(true);

}

void WindowPantallaOpcionesUsuario::on_actionProveedores_activated()
{
    QSqlQuery comprobarProveedores;

    comprobarProveedores.exec("SELECT * FROM proveedores");
    comprobarProveedores.first();

    if(comprobarProveedores.isValid())
    {
        //Reserva de memoria
        wvp = new WidgetVerProveedores(mdiArea,this);

        //Cerramos todas las ventanas
        mdiArea->closeAllSubWindows();

        //Metemos la ventana dentro del mdiArea, y la colocamos en la posicion deseada.
        //mdiArea->addSubWindow(wvp)->move((mdiArea->size().width() - wvp->size().width())/2,0);

        subWin =  mdiArea->addSubWindow(wvp);

        subWin->setFixedHeight(mdiArea->size().height());
        subWin->setMinimumSize(subWin->size());
        //subWin->setFixedWidth(subWin->size().width());

        //subWin->setWindowFlags(subWin->windowFlags() & ~Qt::WindowMaximizeButtonHint);
        //subWin->setWindowFlags(subWin->windowFlags() & ~Qt::WindowMinimizeButtonHint);

        subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, subWin->size(), qApp->desktop()->availableGeometry()));

        //Mostramos la ventana
        subWin->show();

    }else
        QMessageBox::warning(this, "Warning", "No hay ningún proveedor registrado","Aceptar");

}

void WindowPantallaOpcionesUsuario::on_actionCambiar_Contrase_a_activated()
{
    //Cerramos las ventanas del mdiArea
    mdiArea->closeAllSubWindows();

    //Reserva de memoria
    dcc = new DialogCambiarContrasenia(usuarioActivo,mdiArea);

    //Mostramos la ventana
    dcc->show();

}

void WindowPantallaOpcionesUsuario::on_actionCopia_de_Seguridad_activated()
{
    //Reserva de memoria
    wcs = new WidgetCopiaSeguridad(mdiArea);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    //Guardamos un puntero a la QMdiSubWindow, ahora  es una ventana nueva controlada por mdiArea
    subWin = mdiArea->addSubWindow(wcs);   

    subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, subWin->size(), qApp->desktop()->availableGeometry()));

    //Bloquea el boton de maximizar en la subventana
    subWin->setWindowFlags(subWin->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    subWin->setFixedSize(subWin->size());

    subWin->show();
}


void WindowPantallaOpcionesUsuario::on_actionNuevo_Proveedor_activated()
{
    //Reserva de memoria
    wnp = new WidgetNuevoProveedor(mdiArea,this);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    //Metemos la ventana dentro del mdiArea y la mostramos
    //mdiArea->addSubWindow(wnp)->move((mdiArea->size().width() - wnp->size().width())/2,0);

    //mdiArea->addSubWindow(wnp)->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, wnp->size(), qApp->desktop()->availableGeometry()));

    //wnp->show();

    subWin = mdiArea->addSubWindow(wnp);

    //Movemos la ventana
    subWin->move((mdiArea->size().width() - wnp->size().width())/2,0);

    //Bloquea el boton de maximizar en la subventana
    //subWin->setWindowFlags(subWin->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    //subWin->setFixedSize(subWin->size());

    subWin->setFixedHeight(mdiArea->size().height());
    subWin->setMinimumSize(subWin->size());



    subWin->show();
}



void WindowPantallaOpcionesUsuario::on_actionModificar_Datos_activated()
{
    //Reserva de memoria
    wme = new WidgetModificarEmpresa(mdiArea,this);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    subWin = mdiArea->addSubWindow(wme);

    subWin->setFixedHeight(mdiArea->size().height());
    subWin->setMinimumSize(subWin->size());

    subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, subWin->size(), qApp->desktop()->availableGeometry()));

    //Mostramos la ventana
    subWin->show();
}



void WindowPantallaOpcionesUsuario::on_actionRestaurar_Copia_de_Seguridad_activated()
{
    //Reserva de memoria
    wrc = new WidgetRestaurarCopiaSeguridad(this,mdiArea);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    //Guardamos un puntero a la QMdiSubWindow, ahora  es una ventana nueva controlada por mdiArea
    subWin = mdiArea->addSubWindow(wrc);

    subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, subWin->size(), qApp->desktop()->availableGeometry()));

    //Bloquea el boton de maximizar en la subventana
    subWin->setWindowFlags(subWin->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    subWin->setFixedSize(subWin->size());

    subWin->show();
}


void WindowPantallaOpcionesUsuario::on_actionArt_culos_de_Proveedor_activated()
{
    //Reserva de memoria
    wap = new WidgetArticulosProveedores(usuarioActivo,mdiArea,this);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    subWin = mdiArea->addSubWindow(wap);

    subWin->setFixedHeight(mdiArea->size().height());
    subWin->setMinimumSize(subWin->size());

    subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, subWin->size(), qApp->desktop()->availableGeometry()));

    //Mostramos la ventana
    subWin->show();
}

void WindowPantallaOpcionesUsuario::on_actionA_adir_Nuevo_Usuario_activated()
{

    //Reserva de memoria
    wau = new WidgetAltaUsuario(mdiArea,this);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    subWin = mdiArea->addSubWindow(wau);

    subWin->setFixedHeight(mdiArea->size().height());
    subWin->setMinimumSize(subWin->size());

    subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, subWin->size(), qApp->desktop()->availableGeometry()));

    //Mostramos la ventana
    subWin->show();
}



void WindowPantallaOpcionesUsuario::on_actionActividad_Usuario_activated()
{
    //Reserva de memoria
    wact = new WidgetActividadUsuario(mdiArea, this);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    //Metemos la ventana dentro del mdiArea
    //mdiArea->addSubWindow(wact)->move((mdiArea->size().width() - wact->size().width())/3,0);

    //mdiArea->addSubWindow(wact)->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, wact->size(), qApp->desktop()->availableGeometry()));

    subWin = mdiArea->addSubWindow(wact);

    subWin->setFixedHeight(mdiArea->size().height());
    subWin->setMinimumSize(subWin->size());

    subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, subWin->size(), qApp->desktop()->availableGeometry()));

    //Mostramos la ventana
    subWin->show();
}

void WindowPantallaOpcionesUsuario::on_actionEstad_sticas_activated()
{
    //Reserva de memoria
    dtg = new DialogTipoGrafica(mdiArea,this);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    //Metemos la ventana dentro del mdiArea
    //mdiArea->addSubWindow(westc)->move((mdiArea->size().width() - westc->size().width())/2,0);

    //Mostramos la ventana
    dtg->show();

}


QPalette WindowPantallaOpcionesUsuario::colorTema() const
{
    QPalette palette;
    for ( int i = 0; i < QPalette::NColorGroups; i++ )
    {
        QPalette::ColorGroup cg = (QPalette::ColorGroup)i;

        palette.setColor(cg, QPalette::Base, Qt::gray);
        palette.setColor(cg, QPalette::Text, Qt::black);
        //palette.setColor(cg, QPalette::Window, Qt::gray);
        //palette.setColor(cg, QPalette::Mid, Qt::red);
        //palette.setColor(cg, QPalette::Light, Qt::gray);
        //palette.setColor(cg, QPalette::Dark, Qt::black);
        //palette.setColor(cg, QPalette::WindowText, Qt::white);

    }

    return palette;
}


/*
void WindowPantallaOpcionesUsuario::colocarReloj()
{


    clock = new QwtAnalogClock;

    setPalette(colorTema());

    clock->setLineWidth(6);
    clock->setFrameShadow(QwtDial::Plain);
    clock->setTime();

    const QColor knobColor = QColor(Qt::black).light(100);

    for ( int i = 0; i < QwtAnalogClock::NHands; i++)
    {
        QColor handColor = QColor(Qt::black);
        int width = 8;

        if ( i == QwtAnalogClock::SecondHand )
        {
            handColor = Qt::red;
            width = 5;
        }

        QwtDialSimpleNeedle *hand = new QwtDialSimpleNeedle(
        QwtDialSimpleNeedle::Arrow, true, handColor, knobColor);

        hand->setWidth(width);

        clock->setHand((QwtAnalogClock::Hand)i, hand);
    }

    QTimer *timer = new QTimer(clock);
    timer->connect(timer, SIGNAL(timeout()),
        clock, SLOT(setCurrentTime()));
    timer->start(1000);


    ui->rejillaCentral->addWidget(clock);
}
*/



void WindowPantallaOpcionesUsuario::on_actionLista_de_Compra_activated()
{
    QSqlQuery query, queryArticulos;

    query.exec("SELECT * FROM artprov");
    query.first();

    //Si hay relacion articulos proveedor...
    if(query.size() > 0)
    {
        queryArticulos.exec("select proveedores.nombreproveedor, articulos.descripcion, (articulos.stockoptimo - articulos.cantidad) as CantidadCompra, ROUND(artprov.precio,3) as PrecioUd,ROUND((articulos.iva/100 * artprov.precio + artprov.precio),3) as PrecioIVA,ROUND(artprov.precio * (articulos.stockoptimo - articulos.cantidad),3) as Importe,ROUND((articulos.iva/100 * artprov.precio + artprov.precio) * (articulos.stockoptimo - articulos.cantidad),3) as ImporteIVA from artprov,proveedores,articulos WHERE articulos.cantidad < articulos.stockminimo and artprov.precio in(select min(artprov.precio) from artprov, proveedores,articulos WHERE artprov.proveedor = proveedores.cif and articulos.cantidad < 2 group by artprov.codigoean) and articulos.codigoean = artprov.codigoean and proveedores.cif = artprov.proveedor");
        queryArticulos.first();

        if(queryArticulos.size() > 0)
        {

            report = new NCReport();

            report->reset(true);

            //Eliminamos el archivo si existiese...
            QFile f("./imagenes/report.pdf");
            f.remove();

            report->setReportFile("./imagenes/report.xml");
            report->runReportToPDF("./imagenes/report.pdf");

            //Direccion absoluta del path
            QDir direc;
            QString fil = direc.absoluteFilePath("./imagenes/report.pdf");

            //Abrimos el PDF
            bool chivato = QDesktopServices::openUrl(QUrl(fil, QUrl::TolerantMode));

            //Si falla la apertura del pdf...
            if(!chivato)
                report->runReportToQtPreview();


            //Para pasarle algún parametro, le pasamos el DNI, y hacemos la búsqueda según el DNI...
            //report->addParameter("id","'"+identificador+"'");

        }else
            QMessageBox::warning(this,tr("Aviso"),tr("No hay compras que realizar"),tr("Aceptar"));

    }else
        QMessageBox::warning(this,tr("Aviso"),tr("Los proveedores no tienen artículos asociados"),tr("Aceptar"));



}


void WindowPantallaOpcionesUsuario::on_actionUsuarios_activated()
{
    //Reserva de memoria
    wvu = new WidgetVerUsuarios(usuarioActivo,mdiArea,this);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    subWin = mdiArea->addSubWindow(wvu);

    //Bloquea el boton de maximizar en la subventana
    subWin->setWindowFlags(subWin->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    subWin->setMinimumSize(subWin->size());
    subWin->setFixedWidth(subWin->size().width());

    //Movemos la ventana
    subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter,subWin->size(), qApp->desktop()->availableGeometry()));

    subWin->show();
}

void WindowPantallaOpcionesUsuario::on_actionVer_Art_culos_activated()
{
    on_actionAlmac_n_activated();
}



void WindowPantallaOpcionesUsuario::on_actionCompra_Autom_tica_activated()
{
    on_actionLista_de_Compra_activated();
}


void WindowPantallaOpcionesUsuario::on_actionCambiar_Contrase_a_2_activated()
{
    on_actionCambiar_Contrase_a_activated();
}


void WindowPantallaOpcionesUsuario::on_actionNuevo_Tipo_de_Producto_activated()
{
    //Reserva de memoria
    wtp = new WidgetNuevoTipoProducto(mdiArea);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    subWin = mdiArea->addSubWindow(wtp);

    subWin->setFixedSize(subWin->size());

    subWin->setWindowFlags(subWin->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, subWin->size(), qApp->desktop()->availableGeometry()));

    //Mostramos la ventana
    subWin->show();
}


void WindowPantallaOpcionesUsuario::on_actionConexiones_activated()
{
    //Reserva de memoria
    wcx = new WidgetConexiones(mdiArea,this);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    subWin = mdiArea->addSubWindow(wcx);

    //Bloquea el boton de maximizar en la subventana
    subWin->setWindowFlags(subWin->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    subWin->setFixedSize(subWin->size());

    subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, subWin->size(), qApp->desktop()->availableGeometry()));

    subWin->show();

}

WindowPantallaOpcionesUsuario::~WindowPantallaOpcionesUsuario()
{
    delete ui;
}

void WindowPantallaOpcionesUsuario::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
        {
            ui->retranslateUi(this);
        }
        else if(event->type() == QEvent::LocaleChange)
        {
            QString newlocale = QLocale::system().name();
            newlocale.truncate(newlocale.lastIndexOf('_'));

            if(newlocale == "es")
            {
                ui->actionIngl_s->setChecked(false);
                ui->actionEspa_ol->setChecked(true);
                actualizarStatus(newlocale);
            }
            else{

                newlocale = "en";

                ui->actionEspa_ol->setChecked(false);
                ui->actionIngl_s->setChecked(true);
                actualizarStatus(newlocale);
            }

            //Guardamos el idioma actual de la aplicacion
            locale = newlocale;

            actualizarStatus(locale);
            cargarLenguaje(locale);
        }
    }

    QMainWindow::changeEvent(event);
}

void WindowPantallaOpcionesUsuario::cargarLenguaje(const QString locale)
{
    //Cerramos todas las ventanas del mdiArea
    mdiArea->closeAllSubWindows();

    if(locale == "es")
    {
        translator.load("gestiStock_" + locale);
        qApp->installTranslator(&translator);

    //Para cualquier otro caso lo ponemos en ingles
    }else{

        translator.load("gestiStock_en");
        qApp->installTranslator(&translator);

    }
}

void WindowPantallaOpcionesUsuario::actualizarStatus(QString idioma)
{
    QLocale newlocale;

    if(idioma == "es")
    {
        etiquetaIdioma->setText("Español(ES)");
        newlocale = QLocale::Spanish;

    }else{
        etiquetaIdioma->setText("English(EN)");
        newlocale = QLocale::English;
    }


    QString fecha = newlocale.toString(QDate::currentDate(),"dddd, dd 'de' MMMM 'de' yyyy");

    etiquetaFecha->setAlignment(Qt::AlignCenter);
    etiquetaFecha->setFixedWidth(200);
    etiquetaFecha->setText(fecha);

}



void WindowPantallaOpcionesUsuario::on_actionEspa_ol_activated()
{
    if(mdiArea != NULL)
        mdiArea->closeAllSubWindows();

    //Ponemos el otro indicador a falso
    ui->actionIngl_s->setChecked(false);

    //Tenemos el boton activado
    ui->actionEspa_ol->setChecked(true);

    locale = "es";

    actualizarStatus(locale);
    cargarLenguaje(locale);


}

void WindowPantallaOpcionesUsuario::on_actionIngl_s_activated()
{
    if(mdiArea != NULL)
        mdiArea->closeAllSubWindows();

    //Ponemos el otro indicador a falso
    ui->actionEspa_ol->setChecked(false);

    //Tenemos el boton activado
    ui->actionIngl_s->setChecked(true);

    locale = "en";

    actualizarStatus(locale);
    cargarLenguaje(locale);

}

void WindowPantallaOpcionesUsuario::on_actionEstad_sticas_2_activated()
{
    //Reserva de memoria
    dtg = new DialogTipoGrafica(mdiArea,this);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    //Metemos la ventana dentro del mdiArea
    //mdiArea->addSubWindow(westc)->move((mdiArea->size().width() - westc->size().width())/2,0);

    //Mostramos la ventana
    dtg->show();
}

void WindowPantallaOpcionesUsuario::on_actionIntroducir_Compra_activated()
{
    wic = new WidgetIntroducirCompra(&locale,usuarioActivo,mdiArea);
    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    subWin = mdiArea->addSubWindow(wic);

    subWin->setFixedHeight(mdiArea->size().height());
    subWin->setMinimumSize(subWin->size());

    //Bloquea el boton de maximizar en la subventana
    //subWin->setWindowFlags(subWin->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, subWin->size(), qApp->desktop()->availableGeometry()));

    subWin->show();
}

void WindowPantallaOpcionesUsuario::on_actionTOP_proveedores_activated()
{
    wpmc = new WidgetProveedoresMasComprados(mdiArea);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    //Metemos dentro del mdiArea la ventana a abrir
    //mdiArea->addSubWindow(wic)->move((mdiArea->size().width() - wic->size().width())/2,(mdiArea->size().height() - wic->size().height())/2);

    //mdiArea->addSubWindow(wpmc)->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, wpmc->size(), qApp->desktop()->availableGeometry()));

    //mdiArea->addSubWindow(wtp);//->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, wtp->size(), qApp->desktop()->availableGeometry()));
    subWin = mdiArea->addSubWindow(wpmc);

    subWin->setFixedSize(subWin->size());

    subWin->setWindowFlags(subWin->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, subWin->size(), qApp->desktop()->availableGeometry()));

    //Mostramos la ventana
    subWin->show();

}

void WindowPantallaOpcionesUsuario::on_actionTOP_Art_culos_activated()
{
    wamc = new WidgetArticuloMasComprado(mdiArea);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    subWin = mdiArea->addSubWindow(wamc);

    subWin->setFixedSize(subWin->size());

    subWin->setWindowFlags(subWin->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, subWin->size(), qApp->desktop()->availableGeometry()));

    //Mostramos la ventana
    subWin->show();

}



void WindowPantallaOpcionesUsuario::on_actionSalida_de_Art_culos_activated()
{
    wsa = new WidgetSalidasArticulos(usuarioActivo,&locale,mdiArea);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    subWin = mdiArea->addSubWindow(wsa);

    subWin->setFixedHeight(mdiArea->size().height());
    subWin->setMinimumSize(subWin->size());

    subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, subWin->size(), qApp->desktop()->availableGeometry()));

    subWin->show();
}

void WindowPantallaOpcionesUsuario::on_actionQt_Creator_activated()
{
    //Mostramos el dialogo acerca de...
    qApp->aboutQt();
}

void WindowPantallaOpcionesUsuario::on_actionTipos_de_art_culos_activated()
{
    //Reserva de memoria
    wvt = new WidgetVerTipoProductos(this);

    //Cerramos todas las ventanas
    mdiArea->closeAllSubWindows();

    subWin = mdiArea->addSubWindow(wvt);

    subWin->setFixedSize(subWin->size());

    subWin->setWindowFlags(subWin->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, subWin->size(), qApp->desktop()->availableGeometry()));

    //Mostramos la ventana
    subWin->show();
}

/*
void WindowPantallaOpcionesUsuario::on_actionVer_Proveedores_activated()
{
    on_actionProveedores_activated();
}
*/

/*
void WindowPantallaOpcionesUsuario::on_actionMostrar_proveedores_activated()
{
    on_actionProveedores_activated();
}*/

void WindowPantallaOpcionesUsuario::on_actionCopia_de_Seguridad_2_activated()
{
    on_actionCopia_de_Seguridad_activated();
}

void WindowPantallaOpcionesUsuario::on_actionAcerca_de_GestiStock_Software_activated()
{
    dag = new DialogAcercaGestiStock(this);
    dag->show();
}

void WindowPantallaOpcionesUsuario::on_actionMostrar_proveedores_activated()
{
    on_actionProveedores_activated();
}

void WindowPantallaOpcionesUsuario::on_actionMostrar_usuarios_activated()
{
    on_actionUsuarios_activated();
}



