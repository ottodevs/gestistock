#-------------------------------------------------
#
# Project created by QtCreator 2012-07-20T17:48:32
#
#-------------------------------------------------

QT       += core gui

QT       +=  sql

QT       += network


TARGET = gestiStock
TEMPLATE = app

#ActiveX
CONFIG += qaxcontainer

INCLUDEPATH += C:\Qwt-6.0.1\include\
               C:\OpenCV2.3\include\
               C:\OpenCV2.3\modules\core\include \
               C:\OpenCV2.3\modules\imgproc\include \
               C:\OpenCV2.3\modules\features2d\include \
               C:\OpenCV2.3\modules\flann\include \
               C:\OpenCV2.3\modules\highgui\include \
               C:\OpenCV2.3\modules\video\include \
               C:\OpenCV2.3\modules\calib3d\include \
               C:\OpenCV2.3\modules\objdetect\include \
               C:\OpenCV2.3\modules\ml\include \
               C:\OpenCV2.3\modules\contrib\include \
               C:\OpenCV2.3\build\include \


LIBS += C:\OpenCV2.3\bin\libopencv_core231.dll \
        C:\OpenCV2.3\bin\libopencv_imgproc231.dll \
        C:\OpenCV2.3\bin\libopencv_highgui231.dll \
        C:\OpenCV2.3\bin\libopencv_video231.dll \
        C:\OpenCV2.3\bin\libopencv_calib3d231.dll \
        C:\OpenCV2.3\bin\libopencv_contrib231.dll \
        C:\OpenCV2.3\bin\libopencv_features2d231.dll \
        C:\OpenCV2.3\bin\libopencv_flann231.dll \
        C:\OpenCV2.3\bin\libopencv_ml231.dll \
        C:\OpenCV2.3\bin\libopencv_objdetect231.dll \




    CONFIG( debug, debug|release ) {
        #Para modo debug
        LIBS += C:\Qwt-6.0.1\lib\qwtd.dll \
                C:\Users\Personal\Desktop\lib\ncreportd2.dll

    } else {
        #Para modo release
        LIBS += C:\Qwt-6.0.1\lib\qwt.dll \
                C:\Users\Personal\Desktop\lib\ncreport2.dll
    }


SOURCES += \
    windowverarticulos.cpp \
    windowpantallaopcionesusuario.cpp \
    windowcargardatos.cpp \
    widgetverusuarios.cpp \
    widgetverproveedores.cpp \
    widgetrestaurarcopiaseguridad.cpp \
    widgetproveedoresmascomprados.cpp \
    widgetnuevotipoproducto.cpp \
    widgetnuevoproveedor.cpp \
    widgetmodificarempresa.cpp \
    widgetestadisticascompras.cpp \
    widgetconexiones.cpp \
    widgetarticulosproveedores.cpp \
    widgetarticulomascomprado.cpp \
    widgetaltausuario.cpp \
    widgetactividadusuario.cpp \
    smtp.cpp \
    qsqlqueryusuarios.cpp \
    qsqlqueryconexiones.cpp \
    qsqlqueryarticulos.cpp \
    qsqlqueryactividad.cpp \
    qprogressdialognew.cpp \
    mdiarea.cpp \
    main.cpp \
    escalarhistograma.cpp \
    dialogwebcam.cpp \
    dialogrecuperarpass.cpp \
    dialognuevoarticulo.cpp \
    dialogmodificarusuario.cpp \
    dialogmodificararticuloproveedor.cpp \
    dialogmodificararticulo.cpp \
    dialogcambiarcontrasenia.cpp \
    delegate.cpp \
    camerawidget.cpp \
    tools.cpp \
    windownuevaempresa.cpp \
    dialogconexionremota.cpp \
    widgetintroducircompra.cpp \
    dialogcompras.cpp \
    qsqlqueryarticulosproveedor.cpp \
    qsqlqueryproveedoresmascomprados.cpp \
    qsqlqueryarticulosmascomprados.cpp \
    qsqlquerycompras.cpp \
    widgetsalidasarticulos.cpp \
    qsqlquerysalidas.cpp \
    dialogsalidaarticulo.cpp \
    dialogtipografica.cpp \
    dialoganyadirarticuloproveedor.cpp \
    dialognuevoarticuloalmacen.cpp \
    dialogfechafactura.cpp \
    escalarcurva.cpp \
    delegatearticulos.cpp \
    widgetvertipoproductos.cpp \
    qsqlquerytipos.cpp \
    dialogacercagestistock.cpp \
    widgetcopiaseguridad.cpp \
    dialogmodificartipo.cpp

HEADERS  += \
    windowverarticulos.h \
    windowpantallaopcionesusuario.h \
    windowcargardatos.h \
    widgetverusuarios.h \
    widgetverproveedores.h \
    widgetrestaurarcopiaseguridad.h \
    widgetproveedoresmascomprados.h \
    widgetnuevotipoproducto.h \
    widgetnuevoproveedor.h \
    widgetmodificarempresa.h \
    widgetestadisticascompras.h \
    widgetconexiones.h \
    widgetarticulosproveedores.h \
    widgetarticulomascomprado.h \
    widgetaltausuario.h \
    widgetactividadusuario.h \
    smtp.h \
    qsqlqueryusuarios.h \
    qsqlqueryconexiones.h \
    qsqlqueryarticulos.h \
    qsqlqueryactividad.h \
    qprogressdialognew.h \
    mdiarea.h \
    escalarhistograma.h \
    dialogwebcam.h \
    dialogrecuperarpass.h \
    dialognuevoarticulo.h \
    dialogmodificarusuario.h \
    dialogmodificararticuloproveedor.h \
    dialogmodificararticulo.h \
    dialogcambiarcontrasenia.h \
    delegate.h \
    camerawidget.h \
    tools.h \
    windownuevaempresa.h \
    dialogconexionremota.h \
    widgetintroducircompra.h \
    dialogcompras.h \
    qsqlqueryarticulosproveedor.h \
    qsqlqueryproveedoresmascomprados.h \
    qsqlqueryarticulosmascomprados.h \
    qsqlquerycompras.h \
    widgetsalidasarticulos.h \
    qsqlquerysalidas.h \
    dialogsalidaarticulo.h \
    dialogtipografica.h \
    dialoganyadirarticuloproveedor.h \
    dialognuevoarticuloalmacen.h \
    dialogfechafactura.h \
    escalarcurva.h \
    delegatearticulos.h \
    widgetvertipoproductos.h \
    qsqlquerytipos.h \
    dialogacercagestistock.h \
    widgetcopiaseguridad.h \
    dialogmodificartipo.h

FORMS    += \
    windowverarticulos.ui \
    windowpantallaopcionesusuario.ui \
    windowcargardatos.ui \
    widgetverusuarios.ui \
    widgetverproveedores.ui \
    widgetrestaurarcopiaseguridad.ui \
    widgetproveedoresmascomprados.ui \
    widgetnuevotipoproducto.ui \
    widgetnuevoproveedor.ui \
    widgetmodificarempresa.ui \
    widgetestadisticascompras.ui \
    widgetconexiones.ui \
    widgetarticulosproveedores.ui \
    widgetarticulomascomprado.ui \
    widgetaltausuario.ui \
    widgetactividadusuario.ui \
    dialogwebcam.ui \
    dialogrecuperarpass.ui \
    dialognuevoarticulo.ui \
    dialogmodificarusuario.ui \
    dialogmodificararticuloproveedor.ui \
    dialogmodificararticulo.ui \
    dialogcambiarcontrasenia.ui \
    windownuevaempresa.ui \
    dialogconexionremota.ui \
    widgetintroducircompra.ui \
    dialogcompras.ui \
    widgetsalidasarticulos.ui \
    dialogsalidaarticulo.ui \
    dialogtipografica.ui \
    dialoganyadirarticuloproveedor.ui \
    dialognuevoarticuloalmacen.ui \
    dialogfechafactura.ui \
    widgetvertipoproductos.ui \
    dialogacercagestistock.ui \
    widgetcopiaseguridad.ui \
    dialogmodificartipo.ui

RESOURCES += \
    fuentes.qrc

TRANSLATIONS = gestiStock_es.ts \
               gestiStock_en.ts

CODECFORTR   = ISO 8859-15
