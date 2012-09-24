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


#ifndef WINDOWPANTALLAOPCIONESUSUARIO_H
#define WINDOWPANTALLAOPCIONESUSUARIO_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPushButton>
#include <QUrl>
#include <QDebug>
#include <QDesktopServices>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QBuffer>
#include <QTimer>
#include <QShowEvent>
#include <QMdiSubWindow>
#include <QSize>
#include <QMdiArea>
#include <QTranslator>
#include <QLabel>


#include "NCReport/ncreport.h"
#include "NCReport/ncreportoutput.h"
#include "NCReport/ncreportpreviewoutput.h"
#include "NCReport/ncreportpreviewwindow.h"

#include "windowverarticulos.h"
#include "windowcargardatos.h"
#include "widgetnuevoproveedor.h"
#include "dialognuevoarticulo.h"
#include "dialogcambiarcontrasenia.h"
#include "widgetmodificarempresa.h"
#include "widgetverproveedores.h"
#include "widgetcopiaseguridad.h"
#include "widgetrestaurarcopiaseguridad.h"
#include "widgetverusuarios.h"
#include "widgetverproveedores.h"
#include "widgetarticulosproveedores.h"
#include "widgetaltausuario.h"
#include "widgetactividadusuario.h"
#include "widgetestadisticascompras.h"
#include "qwt_analog_clock.h"
#include "widgetnuevotipoproducto.h"
#include "widgetconexiones.h"
#include "mdiarea.h"
#include "widgetintroducircompra.h"
#include "widgetproveedoresmascomprados.h"
#include "widgetarticulomascomprado.h"
#include "widgetsalidasarticulos.h"
#include "dialogtipografica.h"
#include "widgetvertipoproductos.h"
#include "dialogacercagestistock.h"


class DialogTipoGrafica;
class WindowCargarDatos;
class WindoWindowPantallaOpcionesUsuario;
class WidgetVerArticulos;
class DialogCrearProveedor;
class DialogNuevoArticulo;
class DialogCambiarContrasenia;
class DialogModificarEmpresa;
class WidgetVerProveedores;
class WidgetHistograma;
class WidgetCopiaSeguridad;
class WidgetRestaurarCopiaSeguridad;
class WidgetAltaUsuario;
class WidgetActividadUsuario;
class WidgetEstadisticasCompras;
class WindowVerArticulos;
class WidgetIntroducirCompra;
class WidgetArticuloMasComprado;
class WidgetSalidasArticulos;


namespace Ui {
    class WindowPantallaOpcionesUsuario;
}

/**
 * @brief Ventana principal de la aplicación
 *
 */
class WindowPantallaOpcionesUsuario : public QMainWindow
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
     * @brief Constructor de la ventana principal.
     *
     * @param locale Idioma de la aplicación
     * @param userActivo Usuario activo en la aplicación
     * @param wcd Puntero a la pantalla inicial
     * @param parent Puntero a la ventana padre
     */
    explicit WindowPantallaOpcionesUsuario(QString locale, QString userActivo, WindowCargarDatos *wcd, QWidget *parent = 0);
    /**
     * @brief Carga el lenguaje de la aplicación.
     *
     * @param locale Idioma de la aplicación
     */
    void cargarLenguaje(const QString locale);
    /**
     * @brief Destructor de la ventana.
     *
     */
    ~WindowPantallaOpcionesUsuario();
    /**
     * @brief Actualiza el idioma de la statusBar de la ventana principal.
     *
     * @param idioma Idioma actual de la aplicación
     */
    void actualizarStatus(QString idioma);

    bool confirmarCierre; /**< TODO */

    /**
     * @brief Comprueba los privilegios de los usuarios, bloqueándoles las funciones determinadas si no tienen privilegios de administrador.
     *
     */
    void comprobarPrivilegios();
    /**
     * @brief Actualiza la fecha de salida del usuario del sistema en conexiones.
     *
     */
    void cerrarSesion();

private slots:
    /**
     * @brief Slot que activa la pantalla de almacén.
     *
     */
    void on_actionAlmac_n_activated();

    /**
     * @brief Slot que activa la pantalla que muestra los usuarios.
     *
     */
    void on_actionUsuarios_activated();

    /**
     * @brief Slot muestra un mensaje en pantalla para pedir confirmación sobre el cierre, y cierra la ventana.
     *
     */
    void on_actionSalir_activated();

    /**
     * @brief Slot que activa la pantalla de las gráficas.
     *
     */
    void on_actionEstad_sticas_activated();

    /**
     * @brief Slot que muestra en ".pdf" la lista de la compra.
     *
     */
    void on_actionLista_de_Compra_activated();

    /**
     * @brief Slot que activa la pantalla de modificar el usuario.
     *
     */
    void on_actionOpciones_Usuario_activated();

    /**
     * @brief Slot que activa la pantalla donde se muestran los proveedores.
     *
     */
    void on_actionProveedores_activated();

    /**
     * @brief Slot que activa la pantalla de cambio de contraseña.
     *
     */
    void on_actionCambiar_Contrase_a_activated();

    /**
     * @brief Slot que activa la pantalla de copia de seguridad.
     *
     */
    void on_actionCopia_de_Seguridad_activated();

    /**
     * @brief Slot que activa la pantalla de nuevo proveedor.
     *
     */
    void on_actionNuevo_Proveedor_activated();

    /**
     * @brief Slot que activa la pantalla de modificar los datos de la empresa.
     *
     */
    void on_actionModificar_Datos_activated();

    /**
     * @brief Slot que activa la pantalla de los artículos del almacén.
     *
     */
    void on_actionVer_Art_culos_activated();

    /**
     * @brief Slot que genera en ".pdf" la lista de la compra.
     *
     */
    void on_actionCompra_Autom_tica_activated();

    /**
     * @brief Slot que activa la pantallade cambio de contraseña.
     *
     */
    void on_actionCambiar_Contrase_a_2_activated();

    /**
     * @brief Slot que activa la pantalla de restaurar la copia de seguridad.
     *
     */
    void on_actionRestaurar_Copia_de_Seguridad_activated();

    /**
     * @brief Slot que activa la pantalla de artículos de proveedor.
     *
     */
    void on_actionArt_culos_de_Proveedor_activated();

    /**
     * @brief Slot que activa la pantalla de nuevo usuario.
     *
     */
    void on_actionA_adir_Nuevo_Usuario_activated();

    /**
     * @brief Slot que activa la pantalla de actividad de usuarios.
     *
     */
    void on_actionActividad_Usuario_activated();

    /**
     * @brief Slot que activa la pantalla de nuevo tipo de artículo.
     *
     */
    void on_actionNuevo_Tipo_de_Producto_activated();

    /**
     * @brief Slot que activa la pantalla de las conexiones.
     *
     */
    void on_actionConexiones_activated();

    /**
     * @brief Slot que cambia a español el idioma de la aplicación.
     *
     */
    void on_actionEspa_ol_activated();

    /**
     * @brief Slot que cambia a inglés el idioma de la aplicación.
     *
     */
    void on_actionIngl_s_activated();

    /**
     * @brief Slot que activa la pantalla de las gráficas.
     *
     */
    void on_actionEstad_sticas_2_activated();

    /**
     * @brief Slot que activa la pantalla de introducir las compras.
     *
     */
    void on_actionIntroducir_Compra_activated();

    /**
     * @brief Slot que activa la pantalla de mostrar los proveedores más comprados.
     *
     */
    void on_actionTOP_proveedores_activated();

    /**
     * @brief Slot que activa la pantalla de los artículos más comprados.
     *
     */
    void on_actionTOP_Art_culos_activated();

    /**
     * @brief Slot que activa la pantalla de salida de artículos.
     *
     */
    void on_actionSalida_de_Art_culos_activated();

    /**
     * @brief Slot que activa la pantalla de resumen de Qt Creator.
     *
     */
    void on_actionQt_Creator_activated();

    /**
     * @brief Slot que activa la pantalla de tipos de articulos.
     *
     */
    void on_actionTipos_de_art_culos_activated();

    /**
     * @brief Slot que activa la pantalla decopia de seguridad.
     *
     */
    void on_actionCopia_de_Seguridad_2_activated();

    /**
     * @brief Slot que activa la pantalla de resumen de GestiStock Software.
     *
     */
    void on_actionAcerca_de_GestiStock_Software_activated();

    /**
     * @brief Slot que activa la pantalla de proveedores.
     *
     */
    void on_actionMostrar_proveedores_activated();

    /**
     * @brief Slot que activa la pantalla de mostrar los usuarios.
     *
     */
    void on_actionMostrar_usuarios_activated();

public slots:
    /**
     * @brief Captura el evento de cierre.
     *
     * @param ev Evento de cierre
     */
    void closeEvent(QCloseEvent *ev);
    /**
     * @brief Coloca la hora en la statusBar.
     *
     */
    void hora();


private:
    Ui::WindowPantallaOpcionesUsuario *ui; /**< TODO */
    /**
     * @brief Determina el color del tema para la pantalla.
     *
     * @return QPalette Contiene el grupo de colores
     */
    QPalette colorTema() const;
    WindowVerArticulos *va; /**< TODO */
    WindowCargarDatos *pwcd; /**< TODO */
    WidgetNuevoProveedor *wnp; /**< TODO */
    DialogCambiarContrasenia *dcc; /**< TODO */
    WidgetModificarEmpresa *wme; /**< TODO */
    WidgetVerProveedores *wvp; /**< TODO */
    WidgetCopiaSeguridad *wcs; /**< TODO */
    WidgetRestaurarCopiaSeguridad *wrc; /**< TODO */
    WidgetVerUsuarios *wvu; /**< TODO */
    WidgetArticulosProveedores *wap; /**< TODO */
    WidgetActividadUsuario *wact; /**< TODO */
    WidgetEstadisticasCompras *westc; /**< TODO */
    QwtAnalogClock *clock; /**< TODO */
    QMdiSubWindow *subWin; /**< TODO */
    QSqlQuery *cnslt; /**< TODO */
    QString dateTimeInicio; /**< TODO */
    WidgetAltaUsuario *wau; /**< TODO */
    WidgetNuevoTipoProducto *wtp; /**< TODO */
    WidgetConexiones *wcx; /**< TODO */
    MdiArea *mdiArea; /**< TODO */
    QTranslator translator; /**< TODO */
    QLabel *etiquetaFecha; /**< TODO */
    QLabel *etiquetaHora; /**< TODO */
    QTimer *timer; /**< TODO */
    QLabel *etiquetaIdioma; /**< TODO */
    QLabel *etiquetaNombre; /**< TODO */
    WidgetIntroducirCompra *wic; /**< TODO */
    QString usuarioActivo; /**< TODO */
    QString locale; /**< TODO */
    WidgetProveedoresMasComprados *wpmc; /**< TODO */
    WidgetArticuloMasComprado *wamc; /**< TODO */
    WidgetSalidasArticulos *wsa; /**< TODO */
    QString nombreHost; /**< TODO */
    DialogTipoGrafica *dtg; /**< TODO */
    DialogModificarUsuario *dmu; /**< TODO */
    WidgetVerTipoProductos *wvt; /**< TODO */
    QSqlDatabase dbReport; /**< TODO */
    NCReport *report; /**< TODO */
    DialogAcercaGestiStock *dag; /**< TODO */
};

#endif // WINDOWPANTALLAOPCIONESUSUARIO_H
