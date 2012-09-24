#include "dialogtipografica.h"
#include "ui_dialogtipografica.h"

DialogTipoGrafica::DialogTipoGrafica(MdiArea *mdi, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTipoGrafica)
{
    ui->setupUi(this);


    //Titulo de la ventana
    this->setWindowTitle(tr("Tipo de gráfica"));
    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logoSolo.png"));
    //Desactivamos boton ayuda
    this->setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    //Ventana modal
    this->setModal(true);

    mdiArea = mdi;


    ui->rbCompras->setChecked(true);
    ui->rbGrafica1->setChecked(true);

    this->on_rbCompras_clicked();

}


void DialogTipoGrafica::on_pbAceptar_clicked()
{
    /*
       Empieza siempre en el -2, ya que el -1
       es que no hay nada marcado
      -2 -5
      -3 -6
      -4 -7
    */

    QMdiSubWindow *subWin;

    if(ui->cbAnio->currentText() != "" || ui->cbAnio2->currentText() != "")
    {
        //Reserva de memoria
        westc = new WidgetEstadisticasCompras(ui->buttonGroup->checkedId(), ui->buttonGroup_2->checkedId(),ui->cbAnio->currentText(),ui->cbAnio2->currentText(), mdiArea);

        //Cerramos todas las ventanas
        mdiArea->closeAllSubWindows();

        //Metemos la ventana dentro del mdiArea
        //mdiArea->addSubWindow(westc)->move((mdiArea->size().width() - westc->size().width())/2,0);

        //mdiArea->addSubWindow(westc)->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, westc->size(), qApp->desktop()->availableGeometry()));

        subWin =  mdiArea->addSubWindow(westc);

        subWin->setFixedHeight(mdiArea->size().height());
        subWin->setMinimumSize(subWin->size());
        subWin->setFixedWidth(subWin->size().width());

        subWin->setWindowFlags(subWin->windowFlags() & ~Qt::WindowMaximizeButtonHint);

        subWin->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter, subWin->size(), qApp->desktop()->availableGeometry()));

        //Mostramos la ventana
        subWin->show();

        this->close();

    }else
        QMessageBox::warning(this,tr("Aviso"),tr("No hay datos"),tr("Aceptar"));

}

void DialogTipoGrafica::on_rbCompras_clicked()
{
    QSqlQuery compras;
    QStringList anios;

    //Limpiamos
    ui->cbAnio->clear();
    ui->cbAnio2->clear();

    //Rellenamos el combo
    compras.exec("SELECT DISTINCT YEAR(fecha) FROM compraproductos ORDER BY YEAR(fecha) desc");
    while(compras.next())
        anios.append(compras.value(0).toString());

    ui->cbAnio->addItems(anios);
    ui->cbAnio2->addItems(anios);
}

void DialogTipoGrafica::on_rbSalidas_clicked()
{
    QSqlQuery compras;
    QStringList anios;

    //Limpiamos
    ui->cbAnio->clear();
    ui->cbAnio2->clear();

    //Rellenamos el combo
    compras.exec("SELECT DISTINCT YEAR(fecha) FROM salidasarticulos ORDER BY YEAR(fecha) desc");
    while(compras.next())
        anios.append(compras.value(0).toString());

    ui->cbAnio->addItems(anios);
    ui->cbAnio2->addItems(anios);
}


void DialogTipoGrafica::on_rbComprasCant_clicked()
{
    QSqlQuery compras;
    QStringList anios;

    //Limpiamos
    ui->cbAnio->clear();
    ui->cbAnio2->clear();

    //Rellenamos el combo
    compras.exec("SELECT DISTINCT YEAR(fecha) FROM compraproductos ORDER BY YEAR(fecha) desc");
    while(compras.next())
        anios.append(compras.value(0).toString());

    ui->cbAnio->addItems(anios);
    ui->cbAnio2->addItems(anios);
}

void DialogTipoGrafica::changeEvent(QEvent* event)
{

    if(event != NULL)
    {
        if(event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    }

    QDialog::changeEvent(event);
}


DialogTipoGrafica::~DialogTipoGrafica()
{
    delete ui;
}
