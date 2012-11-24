#include "windowcargardatos.h"
#include "ui_windowcargardatos.h"

WindowCargarDatos::WindowCargarDatos(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowCargarDatos)
{
    ui->setupUi(this);

    //Titulo...
    this->setWindowTitle(tr("GestiStock Software"));

    //Icono
    this->setWindowIcon(QIcon(":/imagenes/logoSolo.png"));

    //Colocamos la ventana como modal
    this->setWindowModality(Qt::WindowModal);

    //Esto seria para bloquear el boton de maximizar
    //this->setWindowFlags((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);

    //Eliminamos la redimension y la minimizacion
    this->setWindowFlags((windowFlags() | Qt::CustomizeWindowHint) & Qt::WindowMaximizeButtonHint);


    //comprobacion de conexion con la BD
    if(!existeUsuarioBD())
    {
        //Lo utilizamos para poder pasarle como padre al QMessage el escritorio, y asi situarlo en el centro
        d = QApplication::desktop();

        QMessageBox::critical(d,tr("Error"),tr("No se ha podido abrir la base de datos"),tr("Aceptar"));

        //Cerramos la aplicacion, si tuviesemos problemas
        exit(1);

    }
    else if(!existeBD())
    {   //Lo utilizamos para poder pasarle como padre al QMessage el escritorio, y asi situarlo en el centro
        d = QApplication::desktop();

        QMessageBox::information(d,tr("Información"),tr("Primera ejecución de la aplicación"),tr("Aceptar"));

        crearBD();

    }else
        conectBD();


    //Reservamos memoria despues de establecer la conexion con la BD, para que funcione
    consulta = new QSqlQuery;

    //Para bloquear el boton de nueva empresa si ya existiese una
    comprobarAccion();

    //Consultamos y establecemos el idioma guardado en la aplicacion
    consultarIdioma();

    botonDesconectar();
}


void WindowCargarDatos::botonDesconectar()
{
    if(bd.hostName() != "localhost")
        ui->actionDesconectar_BD_Remota->setEnabled(true);
    else
        ui->actionDesconectar_BD_Remota->setEnabled(false);
}

//Con esto probamos que el usuario de MYSQL exista y sea valido.
bool WindowCargarDatos::existeUsuarioBD()
{
    //Cargamos el driver de QMYSQL, si esta disponible...
    if (QSqlDatabase::isDriverAvailable("QMYSQL"))
    {   //Creamos la conexión...
        bd = QSqlDatabase::addDatabase("QMYSQL","PruebaConnect");
        //Nombre del host
        bd.setHostName("localhost");
        //Nombre de la base de datos que trae mysql
        bd.setDatabaseName("mysql");
        //Nombre de usuario, para mysql
        bd.setUserName("usergestistock");
        //Contraseña para conectarse a mysql
        bd.setPassword("1234");

        //Si la apertura es correcta...verdadero
        if (bd.open())
            return true;
        else
            return false;
    }else
        return false;

}

//Aqui­ comprobamos si nuestra base de datos del programa ya ha sido creada...
bool WindowCargarDatos::existeBD()
{
    QSqlQuery existe(bd);

    //Preparamos para la ejecucion...
    existe.prepare("show databases LIKE 'bdgestistock'");
    //Ejecuta la consulta...
    existe.exec();

    if(existe.size() > 0)
        return true;

return false;
}


//Creamos la base de datos en el primer uso del programa...
void WindowCargarDatos::crearBD()
{
    //Creamos el query con la base de datos creada
    QSqlQuery nuevaBD(bd);

    //Creamos la base de datos
    nuevaBD.exec("CREATE DATABASE bdgestistock");
    //Cerramos la base de datos
    bd.close();

    //Cargamos el driver para MYSQL
    bd = QSqlDatabase::addDatabase("QMYSQL");

    //Maquina
    bd.setHostName("localhost");

    //Nombre de base de datos
    bd.setDatabaseName("bdgestistock");
    //Usuario
    bd.setUserName("usergestistock");
    //Contraseña
    bd.setPassword("1234");

    //Abrimos la base de datos
    bd.open();

    crearTablasBD();

}



bool WindowCargarDatos::conectBD()
{
    //Cerramos la base de datos, por si estuviese abierta
    bd.close();

    //Abro la base de datos comprobando si estan disponibles sus respectivos drivers
    if (QSqlDatabase::isDriverAvailable("QMYSQL"))
    {
         //BD Localhost
         bd = QSqlDatabase::addDatabase("QMYSQL");
         bd.setHostName("localhost");
         bd.setDatabaseName("bdgestistock");
         bd.setUserName("usergestistock");
         bd.setPassword("1234");

         if(bd.open())
             return true;
         else
             return false;

    }
    else
        return false;
}



//Se encarga de crear las tablas...
void WindowCargarDatos::crearTablasBD()
{
    QSqlQuery crearTablaConexiones;
    QSqlQuery crearTablaUsuarios;
    QSqlQuery crearTablaActividad;
    QSqlQuery crearTablaEmpresa;
    QSqlQuery crearTablaDirecciones;
    QSqlQuery crearTablaArticulos;
    QSqlQuery crearTablaArtProv;
    QSqlQuery crearTablaProveedores;
    QSqlQuery crearTablaTipoProducto;
    QSqlQuery crearTablaSalidasArticulos;
    QSqlQuery crearTablaCompraProductos;
    QSqlQuery crearTablaConfiguracion;
    QSqlQuery crearTablaTipoMovimientos;

    //Para inserciones
    QSqlQuery datosIniciales;


    //crearTablaDirecciones.exec("CREATE TABLE direcciones(`cp` int(6) unsigned NOT NULL,`dir` varchar(105) NOT NULL,`localidad` varchar(55) NOT NULL,`provincia` varchar(55) NOT NULL,PRIMARY KEY(cp,dir))");
    crearTablaEmpresa.exec("CREATE TABLE empresa(`cifnif` varchar(19) NOT NULL, `nombre` varchar(55) NOT NULL,`codpostal` int(6) unsigned NOT NULL,`direccion` varchar(105) NOT NULL, `localidad` varchar(55) NOT NULL,`provincia` varchar(55) NOT NULL, `telefono1` varchar(10) NOT NULL, `telefono2` varchar(10) NOT NULL, `correo` varchar(105) NOT NULL, `imagen` longblob DEFAULT NULL, PRIMARY KEY(cifnif))");
    crearTablaUsuarios.exec("CREATE TABLE usuarios(`nombreusuario` varbinary(40) unique NOT NULL,`superusuario` tinyint(1) NOT NULL, `refempresa` varchar(19) NOT NULL, `correo` varchar(105) NOT NULL,`dni` varchar(10) NOT NULL,`password` BLOB NOT NULL,`nombre` varchar(55) NOT NULL,`apellido1` varchar(55) NOT NULL,`apellido2` varchar(55) NOT NULL,`fechaalta` date NOT NULL, `novisible` tinyint(1) DEFAULT 0, `imagen` longblob DEFAULT NULL, PRIMARY KEY(dni))");
    crearTablaConexiones.exec("CREATE TABLE conexiones(`fechaentrada` datetime NOT NULL,`usuario` varchar(10) NOT NULL,`fechasalida` datetime NOT NULL,PRIMARY KEY(fechaentrada), FOREIGN KEY(usuario) REFERENCES usuarios(dni))");
    crearTablaTipoProducto.exec("CREATE TABLE tipoproducto (`nombretipo` varchar(55) NOT NULL,`descripcion` varchar(255) DEFAULT NULL,PRIMARY KEY  (nombretipo))");
    crearTablaArticulos.exec("CREATE TABLE articulos(`codigoean` varchar(25) NOT NULL,`cantidad` FLOAT(11) unsigned NOT NULL,`descripcion` varchar(205) unique NOT NULL,`iva` int(4) unsigned NOT NULL,`tipoproducto` varchar(55) DEFAULT 'Otros',`comentario` varchar(255) DEFAULT NULL,`stockminimo` FLOAT(11) unsigned DEFAULT 2,`stockoptimo` FLOAT(11) unsigned DEFAULT 5,`imagen` longblob DEFAULT NULL, PRIMARY KEY  (codigoean), FOREIGN KEY (tipoproducto) REFERENCES tipoproducto(nombretipo))");
    crearTablaTipoMovimientos.exec("CREATE TABLE tipomovimientos(`nombremovimiento` varchar(55) NOT NULL,`comentario` varchar(255) DEFAULT NULL, PRIMARY KEY(nombremovimiento))");
    crearTablaActividad.exec("CREATE TABLE actividad(`id_actividad` int(11) unsigned auto_increment NOT NULL, `fechamov` datetime NOT NULL,`articulo` varchar(25) NOT NULL,`usuario` varchar(10) NOT NULL, `tipomovimiento` varchar(55) NOT NULL, `cantidad` FLOAT(11) unsigned NOT NULL,  PRIMARY KEY(id_actividad), FOREIGN KEY (articulo) REFERENCES articulos(codigoean), FOREIGN KEY (articulo) REFERENCES articulos(codigoean),FOREIGN KEY (usuario) REFERENCES usuarios(dni),FOREIGN KEY (tipomovimiento) REFERENCES tipomovimientos(nombremovimiento))");
    crearTablaProveedores.exec("CREATE TABLE proveedores (`cif` varchar(19) NOT NULL, `nombreproveedor` varchar(55) unique NOT NULL,`codpostal` int(6) unsigned NOT NULL,`direccion` varchar(105) NOT NULL,`localidad` varchar(55) NOT NULL,`provincia` varchar(55) NOT NULL, `telefono1` varchar(10) DEFAULT NULL, `telefono2` varchar(10) DEFAULT NULL, `correo` varchar(105) DEFAULT NULL,`imagen` longblob DEFAULT NULL, PRIMARY KEY  (cif))");
    crearTablaArtProv.exec("CREATE TABLE artprov(`proveedor` varchar(19) NOT NULL,`codigoean` varchar(25) NOT NULL, `precio` FLOAT(11) unsigned NOT NULL, PRIMARY KEY  (proveedor, codigoean), FOREIGN KEY (proveedor) REFERENCES proveedores(cif), FOREIGN KEY(codigoean) REFERENCES articulos(codigoean))");
    crearTablaSalidasArticulos.exec("CREATE TABLE salidasarticulos(`id_salida` int(11) unsigned auto_increment NOT NULL,`fecha` date NOT NULL,`articulo` varchar(25) NOT NULL,`cantidad` FLOAT(11) unsigned NOT NULL, PRIMARY KEY(id_salida),FOREIGN KEY(articulo) REFERENCES articulos(codigoean))");
    crearTablaCompraProductos.exec("CREATE TABLE compraproductos (`proveedor` varchar(19) NOT NULL, `fecha` date NOT NULL,`articulo` varchar(25) NOT NULL,`precio` FLOAT(11) unsigned NOT NULL,`cantidad` FLOAT(11) unsigned NOT NULL,`iva` int(4) unsigned NOT NULL, PRIMARY KEY(proveedor, fecha, articulo),FOREIGN KEY(proveedor) REFERENCES proveedores(cif),FOREIGN KEY(articulo) REFERENCES articulos(codigoean))");
    crearTablaConfiguracion.exec("CREATE TABLE configuracion (`idioma` varchar(55) NOT NULL, PRIMARY KEY  (idioma))");



    //Insertamos los datos por defecto de la base de datos
    datosIniciales.clear();
    datosIniciales.exec("INSERT INTO tipomovimientos (nombremovimiento) VALUES ('Insertar')");

    datosIniciales.clear();
    datosIniciales.exec("INSERT INTO tipomovimientos (nombremovimiento) VALUES ('Eliminar')");

    datosIniciales.exec();
    datosIniciales.exec("INSERT INTO tipoproducto (nombretipo) VALUES ('Otros')");

    //Introducimos el idioma en el que estara inicialmente el programa
    QString locale = QLocale::system().name();
    locale.truncate(locale.lastIndexOf('_'));

    //Limpiamos la consulta
    datosIniciales.clear();

    //En el caso de que este en español lo ponemos, para cualquier otro idioma ingles
    if(locale == "es")
        datosIniciales.exec("INSERT INTO configuracion (idioma) VALUES ('"+locale+"')");
    else{
        locale = "en";
        datosIniciales.exec("INSERT INTO configuracion (idioma) VALUES ('"+locale+"')");
    }
}

void WindowCargarDatos::consultarIdioma()
{
    //Si hay alguno marcado lo desactivamos
    ui->actionEspa_ol->setChecked(false);
    ui->actionIngl_s->setChecked(false);

    consulta->exec("SELECT * FROM configuracion");
    consulta->first();

    locale = consulta->value(0).toString();

    if(locale == "es")
        ui->actionEspa_ol->setChecked(true);
    else
        ui->actionIngl_s->setChecked(true);

    //Cargamos lenguaje
    cargarLenguaje(locale);
}


void WindowCargarDatos::comprobarAccion()
{
   consulta->exec("SELECT cifnif FROM empresa");

   if(consulta->size() > 0)
      ui->actionNueva_Empresa->setEnabled(false);
}

WindowCargarDatos::~WindowCargarDatos()
{
    delete ui;
}


/*
//Si cerramos la ventana...
void WindowCargarDatos::closeEvent(QCloseEvent *ev)
{
    //Si el usuario ha cerrado la ventana...
    if(ev->isAccepted())
    {
        this->resetearVentana();
        //Activamo la ventana padre anterior de nuevo
        this->parentWidget()->setEnabled(true);

    }

}
*/


void WindowCargarDatos::on_pbLimpiar_clicked()
{
    //Limpiamos los campos
    ui->leUser->clear();
    ui->lePass->clear();

}


void WindowCargarDatos::on_pbAceptar_clicked()
{
    //Primer campo es la clave a encriptar o desencriptar, y el segundola semilla a partir de cual hacerlo:
    //AES_ENCRYPT(str,key_str) , AES_DECRYPT(crypt_str,key_str)

    QSqlQuery consult;

    //Consultamos desencriptando la clave
    consult.exec("SELECT AES_DECRYPT(password,'MyPasswordEncrypt') FROM usuarios WHERE nombreusuario = '"+ui->leUser->text()+"' and novisible = '0' ");

        if(consult.first())
        {
            //Si coinciden las claves, cerramos la ventana
            if(consult.value(0).toString() == ui->lePass->text())
            {
                    pu = new WindowPantallaOpcionesUsuario(locale,ui->leUser->text(),this);
                    //Limpiamos los campos
                    this->on_pbLimpiar_clicked();
                    //Cerramos ventana principal
                    this->close();
                    //Visualizamos la siguiente
                    pu->showMaximized();
            }else
                QMessageBox::critical(this,tr("Error"),tr("Contraseña incorrecta"),tr("Aceptar"));

        }else
            QMessageBox::critical(this,tr("Error"),tr("El usuario no existe"),tr("Aceptar"));

}


void WindowCargarDatos::on_actionNueva_Empresa_activated()
{
    //Reserva de memoria
    Wne = new WindowNuevaEmpresa(this,this);

    //Tamaño de la ventana
    QSize size = Wne->size();
        //Par sacar el tamaño del escritorio
        QDesktopWidget *d = QApplication::desktop();

        int ancho = (d->width()/2) - (size.width()/2);
        int alto = (d->height()/2) - (size.height()/2);

        //Movemos al centro
        Wne->move(ancho,alto);

    //La hacemos visible
    Wne->show();
}

void WindowCargarDatos::on_actionSalir_activated()
{
    this->close();
}

void WindowCargarDatos::on_actionRecuperar_Contrase_a_2_activated()
{
    //Reservamos memoria
    drp = new DialogRecuperarPass(this);

    //Mostramos la ventana
    drp->show();
}


void WindowCargarDatos::on_actionEspa_ol_activated()
{
    //Ponemos el otro indicador a falso
    ui->actionIngl_s->setChecked(false);

    //Tenemos el boton activado
    ui->actionEspa_ol->setChecked(true);

    consulta->clear();
    consulta->exec("UPDATE `configuracion` SET `idioma` = 'es' WHERE `idioma` = '"+locale+"' ");

    locale = "es";
    cargarLenguaje(locale);

}

void WindowCargarDatos::on_actionIngl_s_activated()
{
    //Ponemos el otro indicador a falso
    ui->actionEspa_ol->setChecked(false);

    //Tenemos el boton activado
    ui->actionIngl_s->setChecked(true);

    consulta->clear();
    consulta->exec("UPDATE `configuracion` SET `idioma` = 'en' WHERE `idioma` = '"+locale+"' ");

    locale = "en";
    cargarLenguaje(locale);

}

void WindowCargarDatos::changeEvent(QEvent* event)
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

            if(newlocale != "es")
                newlocale = "en";

            //Limpiamos la consulta
            consulta->clear();
            //Ejecutamos la consulta
            consulta->exec("UPDATE `configuracion` SET `idioma` = '"+newlocale+"' WHERE `idioma` = '"+locale+"' ");

            locale = newlocale;
            cargarLenguaje(locale);
        }
    }

    QMainWindow::changeEvent(event);
}

void WindowCargarDatos::cargarLenguaje(const QString idioma)
{
    if(idioma == "es")
    {
        translator.load("gestiStock_" + idioma);
        qApp->installTranslator(&translator);

    //Para cualquier otro caso lo ponemos en ingles
    }else{

        translator.load("gestiStock_" + locale);
        qApp->installTranslator(&translator);

    }
}


void WindowCargarDatos::on_actionBD_Remota_activated()
{
    dcr = new DialogConexionRemota(&bd,this,this);
    dcr->show();
}

void WindowCargarDatos::on_actionAcerca_de_Qt_activated()
{
    //Ventana sobre Qt
    qApp->aboutQt();
}

void WindowCargarDatos::on_actionDesconectar_BD_Remota_activated()
{
    QMessageBox msgBox(this);
    QMessageBox msg(this);

    //Cerramos por si estan abiertas
    bd.close();

    msgBox.setWindowTitle(tr("Conectando al servidor local..."));
    msgBox.setText(tr("Realizando conexión...                     "));
    msgBox.setInformativeText(tr("Espere..."));
    msgBox.setIcon(QMessageBox::Information);

    //Sin botones
    msgBox.setStandardButtons(0);
    msgBox.setModal(true);
    msgBox.setWindowModality(Qt::WindowModal);
    msgBox.setWindowFlags(Qt::Tool | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    //Mostramos el mensaje
    msgBox.show();

    //Seguimos procesando los eventos de la aplicacion
    qApp->processEvents();
    qApp->sendPostedEvents();


    //Cerramos el mensaje anterior
    msgBox.setVisible(false);

    bd.setHostName("localhost");
    bd.setDatabaseName("bdgestistock");
    bd.setPort(3306);
    bd.setUserName("usergestistock");
    bd.setPassword("1234");

    if(bd.open())
    {
        msg.setWindowTitle(tr("Conectado"));
        msg.setText(tr("Se ha reconectado con el servidor local              "));
        msg.setInformativeText(tr("Reconectado a localhost"));
        msg.setIcon(QMessageBox::Information);
        msg.addButton(tr("Aceptar"),QMessageBox::AcceptRole);

        //Ejecutamos el mensaje esta vez con exec para parar los eventos posteriores
        msg.exec();

        ui->actionDesconectar_BD_Remota->setEnabled(false);
        consultarIdioma();

    }else{

        msg.setWindowTitle(tr("Error"));
        msg.setText(tr("La reconexión al servidor no ha sido posible              "));
        msg.setInformativeText(tr("Desconectado, reinicie la aplicación"));
        msg.setIcon(QMessageBox::Critical);
        msg.addButton(tr("Aceptar"),QMessageBox::AcceptRole);

        //Ejecutamos el mensaje bloqueando los eventos posteriores
        msg.exec();
    }

}

void WindowCargarDatos::on_actionAcerca_de_GestiStock_Software_activated()
{
    dag = new DialogAcercaGestiStock(this);
    dag->show();
}
