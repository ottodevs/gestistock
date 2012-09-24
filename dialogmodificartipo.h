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

        Copyright (C) 2012 Manuel Trinidad Garc�a
*/


#ifndef DIALOGMODIFICARTIPO_H
#define DIALOGMODIFICARTIPO_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

#include "qsqlquerytipos.h"




namespace Ui {
class DialogModificarTipo;
}

/**
 * @brief Di�logo que permite modificar un tipo.
 *
 */
class DialogModificarTipo : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor del di�logo.
     *
     * @param nombre Nombre del tipo
     * @param consulta Consulta del model tipo de art�culos
     * @param modelTipos Model tipo de art�culos
     * @param parent Puntero a la ventana padre
     */
    explicit DialogModificarTipo(QString nombre, QString consulta, QSqlQueryTipos *modelTipos, QWidget *parent = 0);
    /**
     * @brief Destructor del di�logo.
     *
     */
    ~DialogModificarTipo();

protected:
    /**
     * @brief Evento que se activa al cambiar el idioma de la aplicaci�n, o del sistema, procede a la traducci�n de todos los elementos.
     *
     * @param event Evento del sistema
     */
    void changeEvent(QEvent* event);
    
private slots:
    /**
     * @brief Slot que cierra el di�logo.
     *
     */
    void on_pbCancelar_clicked();

    /**
     * @brief Slot que guarda las modificaciones.
     *
     */
    void on_pbGuardar_clicked();

    /**
     * @brief Slot que elimina el tipo.
     *
     */
    void on_pbEliminar_clicked();

    /**
     * @brief Slot que detecta si se ha cambiado el textEdit
     *
     */
    void on_teComentario_textChanged();

private:
    Ui::DialogModificarTipo *ui; /**< TODO */
    QString consultaActiva; /**< TODO */
    QSqlQueryTipos *model; /**< TODO */
    QString nombreTipo; /**< TODO */
    QSqlQuery *queryTipos; /**< TODO */
};

#endif // DIALOGMODIFICARTIPO_H
