#include "src/server/SingleThreadServer.h"
#include "src/utils/MessageSenderUtil.h"
#include <QDataStream>
#include <QDebug>
#include <QTcpSocket>
#include <QIODevice>
#include <QDataStream>
#include <QByteArray>

SingleThreadServer::SingleThreadServer(QObject *parent)
     : AbstractServer(parent)
{
	m_nNextBlockSize = 0;
}

void SingleThreadServer::readData(QTcpSocket* pClientSocket) {
	qDebug() << "SingleThreadServer::readData# Received data from socket " << pClientSocket->socketDescriptor() << endl ;
	QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QString str;
        in >> str;
        m_nNextBlockSize = 0;
		qDebug() << "SingleThreadServer::readData# client " << pClientSocket->socketDescriptor() << ": " << str << endl;
		emit dataReaded(&str,pClientSocket);
    }
}

void SingleThreadServer::sendData(QTcpSocket* pSocket, const QString &data){
	MessageSenderUtil::sendMessage(pSocket,data);
}
