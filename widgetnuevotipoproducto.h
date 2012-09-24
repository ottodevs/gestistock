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


#ifndef WIDGETNUEVOTIPOPRODUCTO_H
#define WIDGETNUEVOTIPOPRODUCTO_H

#include <QWidget>
#include <QMdiArea>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QTranslator>

namespace Ui {
class WidgetNuevoTipoProducto;
}

/**
 * @brief Widget que permite crear un nuevo tipo de artículo.
 *
 */
class WidgetNuevoTipoProducto : public QWidget
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
     * @param mdiArea Puntero al QMdiArea de la pantalla principal
     * @param parent Puntero a la ventana padre
     */
    explicit WidgetNuevoTipoProducto(QMdiArea *mdiArea, QWidget *parent=0);
    /**
     * @brief Destructor del Widget.
     *
     */
    ~WidgetNuevoTipoProducto();
    
private slots:
    /**
     * @brief Slot que cierra el Widget.
     *
     */
    void on_pbCancelar_clicked();
    /**
     * @brief Slot que guarda el tipo en el sistema.
     *
     */
    void on_pbGuardar_clicked();
    /**
     * @brief Slot que se activa cuando el texto de su textEdit ha sido modificado.
     *
     */
    void on_teComentario_textChanged();

private:
    Ui::WidgetNuevoTipoProducto *ui; /**< TODO */
    QMdiArea *mdi; /**< TODO */
    QSqlQuery *insertarTipo; /**< TODO */
    QSqlQuery *comprobar; /**< TODO */
    QTranslator translator; /**< TODO */
};

#endif // WidgetNuevoTipoProducto_H
