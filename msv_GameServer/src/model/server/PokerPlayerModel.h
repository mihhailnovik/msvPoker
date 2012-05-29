#ifndef POKERPLAYERMODEL_H
#define POKERPLAYERMODEL_H
#include <QString>
#include <QTcpSocket>
#include <QObject>
#include <QMutex>
#include <QList>
#include "src/model/server/MessagePool.h"
#include "src/model/server/MsvClientMessage.h"

class PokerPlayerModel:public QObject {
	Q_OBJECT
public:
	 PokerPlayerModel(QObject *parent = 0);
	~PokerPlayerModel();
	 void setSocket(QTcpSocket* socket);
	 QTcpSocket* getSocket() const;
	 QString* getName() const;
	 void setName(QString* name);
	 void setMoney(quint16 money);
	 quint16 getMoney() const;
	 bool takeMoney(quint16 money); // takes money from player, returns true if player have enough money, otherwise returns false
	 void lock();
	 void unlock();
	 void addMessage(MsvClientMessage* message);
	 QList<MsvClientMessage*>* getMessagePool() const;
private:
	QTcpSocket* qTcpSocket;
	QString* name;
	QMutex mutex;
	quint16 money;
	QList<MsvClientMessage*>* messagePool;
};
#endif
