#include "src/utils/SocketHolder.h"
#include "src/model/MsvServerMessage.h"
#include "src/utils/MessageTransformer.h"
#include <QDebug>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QDataStream>
#include <QString>
#include <QDebug>
#include <QIODevice>

SocketHolder::SocketHolder(QObject *parent)
    : QObject(parent)
{
	m_nNextBlockSize = 0;
	socket = new QTcpSocket();
}

void SocketHolder::connectToHost(const QHostAddress & address, quint16 port){
	socket->connectToHost(address,port);
	connect(socket, SIGNAL(connected()), SLOT(slotConnected()));
	connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
	            this,         SLOT(slotError(QAbstractSocket::SocketError))
	       );
}

QTcpSocket* SocketHolder::getSocket(){
	if (socket == NULL) {
		qDebug() << "SocketHolder::getSocket# WARNING !!! socket is null " << endl;
	}

	if (socket->state() != QAbstractSocket::ConnectedState){
		qDebug() << "SocketHolder::getSocket# WARNING !!! socket state is " << socket->state() << endl;
	}
	return socket;
}

void SocketHolder::slotConnected(){

}

void SocketHolder::slotReadyRead(){
	 QDataStream in(socket);
	 in.setVersion(QDataStream::Qt_4_2);
	 for (;;) {
	    if (!m_nNextBlockSize) {
	       if (socket->bytesAvailable() < sizeof(quint16)) {
	          break;
	       }
	           in >> m_nNextBlockSize;
	    }

        if (socket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QString str;
        in >> str;
        qDebug() << "SocketHolder::slotReadyRead# Readed data " << str << endl;
        m_nNextBlockSize = 0;
        MsvServerMessage* message = MessageTransformer::transformServerMessage(&str);
        qDebug() << "SocketHolder::slotReadyRead# Signal dataReaded(message) emited " << endl;
        emit dataReaded(message);
    }
}

void SocketHolder::slotError(QAbstractSocket::SocketError){

}

void SocketHolder::sendData(const QString &data){
		qDebug() << "SocketHolder::slotReadyRead# Sending " << data << endl;
		QByteArray  arrBlock;
	    QDataStream out(&arrBlock, QIODevice::WriteOnly);
	    out.setVersion(QDataStream::Qt_4_2);
	    out << quint16(0) << data;
	    out.device()->seek(0);
	    out << quint16(arrBlock.size() - sizeof(quint16));
	    socket->write(arrBlock);
}
