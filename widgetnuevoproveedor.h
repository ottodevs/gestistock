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


#ifndef WIDGETNUEVOPROVEEDOR_H
#define WIDGETNUEVOPROVEEDOR_H

#include <QWidget>
#include <QTranslator>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QBuffer>
#include <QSqlError>

#include "mdiarea.h"

namespace Ui {
class WidgetNuevoProveedor;
}

/**
 * @brief Widget que permite la creación de un nuevo proveedor.
 *
 */
class WidgetNuevoProveedor : public QWidget
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
     * @param mdi Puntero al QMdiArea de la pantalla principal
     * @param parent Puntero a la ventana padre
     */
    explicit WidgetNuevoProveedor(MdiArea *mdi, QWidget *parent = 0);
    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetNuevoProveedor();
    
private slots:
    /**
     * @brief Slot que guarda el nuevo proveedor en el sistema.
     *
     */
    void on_pbGuardar_clicked();

    /**
     * @brief Slot que permite la selección de una imagen y la coloca en un QLabel.
     *
     */
    void on_pbExaminar_clicked();

    /**
     * @brief Slot que cierra el Widget.
     *
     */
    void on_pbCancelar_clicked();

private:
    Ui::WidgetNuevoProveedor *ui; /**< TODO */
    QTranslator translator; /**< TODO */
    QPixmap *imagenArticulo; /**< TODO */
    bool fotoCargada; /**< TODO */
    QString rutaImagen; /**< TODO */
    MdiArea *mdiArea; /**< TODO */
};

#endif // WIDGETNUEVOPROVEEDOR_H
