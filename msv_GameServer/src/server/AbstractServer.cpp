#include "src/server/AbstractServer.h"

AbstractServer::AbstractServer(QObject *parent)
     : QTcpServer(parent)

 {
     qDebug() << tr("AbstractServer::AbstractServer# Server created ") << endl;
	 connect(this, SIGNAL(newConnection()), 
            this,         SLOT(slotNewConnection()));
 }

/**
 runs, when signal newConnection received, connects
 socket.disconnected -> socket.deleteLater
 socket.readyRead ->  slotReadClient()
*/
void AbstractServer::slotNewConnection() {
    QTcpSocket* pClientSocket = this->nextPendingConnection();
	qDebug() << tr("AbstractServer::slotNewConnection()# New client connected, socket descriptor = ") << pClientSocket->socketDescriptor() << endl;
	connectSignal(pClientSocket);
}
/**
 runs every time when one of connected clients, send new data
*/
void AbstractServer::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
	readData(pClientSocket);
}

void AbstractServer::slotClientDisconnect() {
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    qDebug() << tr("AbstractServer::slotClientDisconnect()# client  ") << pClientSocket->socketDescriptor();
    emit clientDisconnect(pClientSocket->socketDescriptor());	
}

void AbstractServer::disconnectSignal(QTcpSocket* pClientSocket){
	qDebug() << "AbstractServer::disconnectSignal# disconnect socket" << pClientSocket->socketDescriptor();
	disconnect(pClientSocket, SIGNAL(disconnected()),
			this, SLOT(slotClientDisconnect())
           );
	disconnect(pClientSocket, SIGNAL(readyRead()),
            this,          SLOT(slotReadClient())
           );
}

void AbstractServer::connectSignal(QTcpSocket* pClientSocket){
	 connect(pClientSocket, SIGNAL(disconnected()),
	            this, SLOT(slotClientDisconnect())
	           );
	 connect(pClientSocket, SIGNAL(readyRead()),
	            this, SLOT(slotReadClient())
	           );
}
