#include "src/model/server/PokerPlayerModel.h"
#include <QMutexLocker>

// XXX this object shoudld by synchoronised QMutexLocker locker(&mutex);
PokerPlayerModel::PokerPlayerModel(QObject *parent) : QObject(parent){
	messagePool = new QList<MsvClientMessage*>();
}

PokerPlayerModel::~PokerPlayerModel(){
}

void PokerPlayerModel::setSocket(QTcpSocket* socket){
	qTcpSocket = socket;
}

QTcpSocket* PokerPlayerModel::getSocket() const{
	return qTcpSocket;
}

QString* PokerPlayerModel::getName() const{
	return name;
}

void PokerPlayerModel::setName(QString* name){
	this->name = name;
}

void PokerPlayerModel::setMoney(quint16 money){
	this->money = money;
}
quint16 PokerPlayerModel::getMoney() const {
	return money;
}

bool PokerPlayerModel::takeMoney(quint16 money){
	QMutexLocker locker(&mutex);
	if (money > this->money){
		return false;
	}
	this->money -=  money;
	return true;
}

void PokerPlayerModel::lock(){
	mutex.lock();
}

void PokerPlayerModel::unlock(){
	mutex.unlock();
}

void PokerPlayerModel::addMessage(MsvClientMessage* message) {
	mutex.lock();
	messagePool->append(message);
	mutex.unlock();
}

QList<MsvClientMessage*>* PokerPlayerModel::getMessagePool() const {
	return messagePool;
}
