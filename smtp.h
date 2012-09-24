#ifndef SMTP_H
#define SMTP_H

#include <QApplication>
#include <QTcpSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QAbstractSocket>
#include <QDateTime>
#include <QDate>
#include <QLocale>
#include <QMessageBox>

#include "tools.h"

/*
      USO:
      Smtp *newMail  = new Smtp("remoteserver","username","pass");
      newMail->Send("from@address.com","to@address.com"," Your Subject","My body text");
      class emit ErrorCloseAll() / SuccessQuit()   or get QStringList ErrorMSG; to read error and data....

*/

/**
 * @brief Clase que crea una conexi�n con un servidor SMTP para el env�o de correos.
 *
 */
class Smtp : public QObject
{
    Q_OBJECT

public:
/**
 * @brief Constructor de la clase.
 *
 * @param smtphost Host del SMTP
 * @param smtpusername Usuario del SMTP
 * @param smtppass Contrase�a del SMTP
 */
    Smtp(QString smtphost, QString smtpusername, QString smtppass);
    /**
     * @brief Destructor de la clase.
     *
     */
    ~Smtp();
    /**
     * @brief Configuraci�n de la conexi�n.
     *
     * @param smtphost Host del SMTP
     * @param smtpusername Usuario del SMTP
     * @param smtppass Contrase�a del SMTP
     */
    void SetConfig(QString smtphost, QString smtpusername, QString smtppass);
    /**
     * @brief Clase que se encarga del env�o.
     *
     * @param from Quien manda el correo
     * @param to A quien se le manda el correo
     * @param subject Asunto del correo
     * @param body Cuerpo del mensaje
     */
    void Send( const QString &from, const QString &to,const QString &subject, const QString &body );
    int linesend; /**< TODO */
    QStringList ErrorMSG; /**< TODO */
    /**
     * @brief Devuelve una lista de errores.
     *
     * @return QStringList Lista de errores devuelta
     */
    QStringList GetErrorlist();

signals:
    /**
     * @brief Se�al emitida con el estado del env�o.
     *
     * @param Par�metro recibido para determinar el estado del env�o
     */
    void status( const QString &);
    /**
     * @brief Se�al emitida cuando se la conexi�n con el servidor es satisfactoria.
     *
     */
    void ConnectorSuccess();
    /**
     * @brief Se�al emitida cuando se env�a una linea
     *
     */
    void SendLine();
    /**
     * @brief Se�al emitida que aborta el env�o.
     *
     */
    void ErrorCloseAll();
    /**
     * @brief Se�al emitida cuando todo ha terminado con �xito.
     *
     */
    void SuccessQuit();

private slots:
    /**
     * @brief Slot que desconecta del SMTP.
     *
     */
    void disconnected();
    /**
     * @brief Slot que conecta al SMTP.
     *
     */
    void connected();
    /**
     * @brief Slot que lee una l�nea
     *
     */
    void ReadLiner();
    /**
     * @brief Slot que prepara para el env�o de una linea.
     *
     */
    void PutSendLine();
    /**
     * @brief Slot emitido cuando el mensaje se ha enviado.
     *
     */
    void smsEnviado();
    /**
     * @brief Slot emitido cuando el mensaje ha fallado.
     *
     */
    void smsFallido();

private:
    bool isconnect; /**< TODO */
    QString smtphost; /**< TODO */
    QString smtpusername; /**< TODO */
    QString smtppass; /**< TODO */
    QString message; /**< TODO */
    QString output; /**< TODO */
    QString RemoteServerName; /**< TODO */
    QString mailstatus; /**< TODO */
    QTextStream *t; /**< TODO */
    QTcpSocket *smtpsocket; /**< TODO */
    QString from; /**< TODO */
    QString rcpt; /**< TODO */
    QString response; /**< TODO */
    /**
     * @brief Env�a y recibe datos.
     *
     * @param senddata Datos para enviar
     * @return QString Cadena recibida
     */
    QString SendLineAndGrab(QString senddata);
    int Timeout; /**< TODO */
    /**
     * @brief Codifica en Base64
     *
     * @param xml Texto a partir del que codifica.
     * @return QString Texto codificado.
     */
    QString encodeBase64( QString xml );
    /**
     * @brief Decodifica en Base64
     *
     * @param xml Texto a partir del que decodifica.
     * @return QString Texto decodificado.
     */
    QString decodeBase64( QString xml );

};

#endif
