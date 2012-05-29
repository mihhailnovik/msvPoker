#include "src/model/game_engine/PokerRoomModel.h"
#include <QDebug>

PokerRoomModel::PokerRoomModel(QObject *parent, quint16 maxPlayers) : QObject(parent){
	this->maxPlayers = maxPlayers;
	chairMap = new QMap<quint16,PokerPlayerModel*>();
	for (quint16 i = 0;i<maxPlayers;i++) {
		chairMap->insert(i,NULL);
	}
	cards = new QList<CardModel*>();
	money = 0;
}

PokerRoomModel::~PokerRoomModel(){
	delete name;
	delete type;
	delete chairMap;
}

const QString* PokerRoomModel::getName() const {
	return name;
}
void PokerRoomModel::setName(QString* name) {
	this->name = name;
}
const QString* PokerRoomModel::getType() const {
	return type;
}
void PokerRoomModel::setType(QString* type){
	this->type = type;
}
const quint16 PokerRoomModel::getMaxPlayers() const {
	return maxPlayers;
}

const bool PokerRoomModel::isChairFree(quint16 chairId) const {
	return (chairMap != 0 && chairMap->value(chairId) == 0);
}

void PokerRoomModel::setMaxPlayers(quint16 mpl){
	this->maxPlayers = mpl;
	for (quint16 i = 0;i<maxPlayers;i++) {
		chairMap->insert(i,NULL);
	}
}

const QList<quint16> PokerRoomModel::getFreeChairs() const {
	QList<quint16> freeChairs;
	for (quint16 i = 0;i<maxPlayers;i++) {
		if (chairMap->value(i) == NULL){
			freeChairs << i;
		}
	}
	return freeChairs;
}

void PokerRoomModel::takeSeat(PokerPlayerModel* model, quint16 chairId) {
	if (chairMap->value(chairId) != NULL || chairId < 0 || chairId > maxPlayers || model == NULL) {
		qDebug() << "PokerRoomModel::takeSeat# ERROR, logic is broken " << endl;
		if (chairMap->value(chairId) != NULL){
			qDebug() << "PokerRoomModel::takeSeat# ERROR = there is already on player" << endl;
		}
		if (chairId < 0 || chairId > maxPlayers){
			qDebug() << "PokerRoomModel::takeSeat# chairId < 0 || chaiId > maxPlayers, chairId = " << chairId << " maxPlayers=" << maxPlayers<< endl;
		}
		if (model == NULL) {
			qDebug() << "PokerRoomModel::takeSeat# model == NULL" << endl;
		}
	}
	chairMap->insert(model->getChairId(),model);
}

const quint16 PokerRoomModel::getId() const {
	return id;
}

void PokerRoomModel::setId(quint16 id){
	this->id = id;
}

void PokerRoomModel::lock() {
	mutex.lock();
}
void PokerRoomModel::unlock(){
	mutex.unlock();
}

QList<CardModel*>* PokerRoomModel::getCards() const{
	return cards;
}

void PokerRoomModel::setCards(QList<CardModel*>*){
	this->cards = cards;
}

void PokerRoomModel::addCard(CardModel* model){
	cards->append(model);
}

void PokerRoomModel::setMoney(quint16 money){
	this->money = money;
}

quint16 PokerRoomModel::getMoney() const{
	return money;
}

QMap<quint16,PokerPlayerModel*>* PokerRoomModel::getChairMap() const {
	return chairMap;
}
void PokerRoomModel::setChairMap(QMap<quint16,PokerPlayerModel*>*) {
	this->chairMap = chairMap;
}
