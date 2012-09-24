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


#ifndef WIDGETMODIFICAREMPRESA_H
#define WIDGETMODIFICAREMPRESA_H

#include <QWidget>
#include <QCloseEvent>
#include <QSqlQuery>
#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>
#include <QMdiArea>
#include <QDebug>
#include <QTranslator>
#include <QSqlError>


namespace Ui {
class WidgetModificarEmpresa;
}

/**
 * @brief Widget que permite la modificación de los datos de una empresa.
 *
 */
class WidgetModificarEmpresa : public QWidget
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
     * @param ma Puntero al QMdiArea de la ventana principal
     * @param parent Puntero al padre del Widget
     */
    explicit WidgetModificarEmpresa(QMdiArea *ma, QWidget *parent=0);
    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetModificarEmpresa();

private slots:

    /**
     * @brief Slot que guarda los datos modificados.
     *
     */
    void on_pbGuardar_clicked();
    /**
     * @brief Slot que permite cambiar la imagen de una empresa.
     *
     */
    void on_pbCambiarImagen_clicked();
    /**
     * @brief Slot que cierra el Widget.
     *
     */
    void on_pbSalir_clicked();
    
private:
    Ui::WidgetModificarEmpresa *ui; /**< TODO */
    QSqlQuery *consultaEmpresa; /**< TODO */
    QSqlQuery *consultaDireccion; /**< TODO */
    QString rutaImagen; /**< TODO */
    bool imagenActualizada; /**< TODO */
    QPixmap *imagenArticulo; /**< TODO */
    QMdiArea *mdi; /**< TODO */
    QTranslator translator; /**< TODO */
    QSqlQuery *queryEmpresa; /**< TODO */
};

#endif // WidgetModificarEmpresa_H
