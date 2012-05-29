#include "src/model/server/PokerHostModel.h"
PokerHostModel::PokerHostModel(QObject *parent) : QObject(parent) {timeout = 10;}

PokerHostModel::~PokerHostModel(){
	delete host;
	delete pokerRoomList;
}
QString* PokerHostModel::getHost() const{
	return host;
}

void PokerHostModel::setHost(QString* host) {
	this->host = host;
}

quint16 PokerHostModel::getPort() const{
	return port;
}

void PokerHostModel::setPort(quint16 port){
	this->port = port;
}

QList<PokerRoomModel*>* PokerHostModel::getPokerRoomList() const {
	return pokerRoomList;
}

void PokerHostModel::setPokerRoomList(QList<PokerRoomModel*>* list) {
	pokerRoomList = list;
}

QString* PokerHostModel::getType() const {
	return type;
}

void PokerHostModel::setType(QString* type){
	this->type = type;
}

quint16 PokerHostModel::getTimeOut(){
	return timeout;
}
void PokerHostModel::setTimeOut(quint16 timeout){
	this->timeout = timeout;
}
