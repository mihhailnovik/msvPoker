#ifndef SINGLETHREADSERVER_H
#define SINGLETHREADSERVER_H
#include "src/server/AbstractServer.h"

/**
 * @author rdir52_msv team
 * Simple Abstract server implementation, all data received and sent in one thread
 */
class SingleThreadServer : public AbstractServer
 {
     Q_OBJECT
 public:
     SingleThreadServer(QObject *parent = 0);
	 void readData(QTcpSocket* pClientSocket);// emit DataReaded();
	 void sendData(QTcpSocket* pSocket, const QString &fortune);
 private:
	 quint16 m_nNextBlockSize;
 };
#endif
