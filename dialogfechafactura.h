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


#ifndef DIALOGFECHAFACTURA_H
#define DIALOGFECHAFACTURA_H

#include <QDialog>
#include <QCalendarWidget>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

#include "qsqlquerycompras.h"
#include "qsqlqueryarticulos.h"

namespace Ui {
class DialogFechaFactura;
}

/**
 * @brief Dialog que permite introducir la fecha de la factura de la compra.
 *
 */
class DialogFechaFactura : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor del diálogo.
     *
     * @param usuario Usuario que introduce la factura
     * @param local Para determinar el idioma
     * @param mpArt Model del QTableView almacén
     * @param consultaArt Consulta del model
     * @param mpCompras Model del QTableView compras
     * @param consulta Consulta del model
     * @param parent Punteor a la ventana padre
     */
    explicit DialogFechaFactura(QString usuario, QString local, QSqlQueryArticulos *mpArt, QString consultaArt, QSqlQueryCompras *mpCompras, QString consulta, QWidget *parent=0);
    /**
     * @brief Actualiza el idioma de la fecha.
     *
     * @param idioma Contiene el nombre del idioma
     */
    void actualizarStatus(QString idioma);
    /**
     * @brief Encargada de sombrear en el calendario lo días que ha habido compras.
     *
     */
    void marcarCalendario();
    /**
     * @brief Para procesar las lineas del fichero, ".asc" en este caso, a partir de un QByteArray.
     *
     * @param Parámetro a partir del cual se procesa la linea
     */
    void process_line(const QByteArray &){}
    /**
     * @brief Para procesar las lineas de un fichero a partir de un QString.
     *
     * @param Parámetro a partir del cual se procesa la linea
     */
    void process_line(const QString &){}
    /**
     * @brief Destructor del diálogo.
     *
     */
    ~DialogFechaFactura();

protected:
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicación, o del sistema, procede a la traducción de todos los elementos.
     *
     * @param event Evento del sistema
     */
    void changeEvent(QEvent* event);
    
private slots:
    /**
     * @brief Slot que confirma la fecha de la compra.
     *
     */
    void on_pbAceptar_clicked();

private:
    Ui::DialogFechaFactura *ui; /**< TODO */
    QString locale; /**< TODO */
    QSqlQueryCompras *mp; /**< TODO */
    QTextCharFormat fondoCalendar; /**< TODO */
    QString consultaCompras; /**< TODO */
    QString usuarioActivo; /**< TODO */
    QSqlQueryArticulos *mpArticulos;
    QString consultaArticulos;
};

#endif // DIALOGFECHAFACTURA_H
