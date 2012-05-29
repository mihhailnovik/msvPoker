#ifndef ABSTRACTSERVER_H
#define ABSTRACTSERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
//

/**	
	@author rdir52_msv team
	Abstract class provides tcp server interface
*/
 class AbstractServer : public QTcpServer
 {
     Q_OBJECT
 public:
     AbstractServer(QObject *parent = 0);
     void virtual sendData(QTcpSocket* pSocket, const QString &text) = 0; // send data to specified socket
     void virtual readData(QTcpSocket* pClientSocket) = 0; // read data from socket pClientSocket, and emit signal DataReaded(QString* message)
     void disconnectSignal(QTcpSocket* pClientSocket); // calls when we do not want to hear about this signal
     void connectSignal(QTcpSocket* pClientSocket); // start listening signals (readClient.. etc)
 signals:
     void dataReaded(const QString* message,QTcpSocket* socket);
	 void clientDisconnect(quint16 socketId);
 private slots:
	 void slotNewConnection();
	 void slotReadClient();
	 void slotClientDisconnect();
 };
#endif
