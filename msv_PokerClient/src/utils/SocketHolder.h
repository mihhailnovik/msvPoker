#ifndef SOCKETHOLDER_H
#define SOCKETHOLDER_H
#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QHostAddress>
#include <QAbstractSocket>
#include "src/model/MsvServerMessage.h"

/**
 * connects socket to server and add listener to socket
 */

class SocketHolder : public QObject
{
	Q_OBJECT
public:
	QTcpSocket* socket;
	SocketHolder(QObject *parent = 0);
	void connectToHost(const QHostAddress & address, quint16 port);
	QTcpSocket* getSocket();
	void sendData(const QString &data);
signals:
	void dataReaded(MsvServerMessage* message);
public slots:
	void slotConnected();
	void slotReadyRead();
	void slotError(QAbstractSocket::SocketError);
private:
	quint16 m_nNextBlockSize;
};
#endif
