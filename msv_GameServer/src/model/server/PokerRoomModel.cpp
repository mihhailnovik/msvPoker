#include "src/model/server/PokerRoomModel.h"
#include <QMutexLocker>

PokerRoomModel::PokerRoomModel(QObject *parent, quint16 maxPlayers) : QObject(parent){
	this->maxPlayers = maxPlayers;
	chairMap = new QMap<quint16,PokerPlayerModel*>();
	playerList = new QList<PokerPlayerModel*>();
	for (quint16 i = 0;i<maxPlayers;i++) {
		chairMap->insert(i,NULL);
	}

	// FIXME hardcoded hack, actualy this object should be loadeed from config file
	BetModel* model = new BetModel();
	model->setSmallBlind(50);
	model->setBigBlind(100);
	model->setBuyInMin(1000);
	model->setBuyInMax(10000);
	model->setMaxRaisePercent(100);
	model->setMinRaisePercent(33);
	this->betModel = model;
}

PokerRoomModel::~PokerRoomModel(){
	delete name;
	delete type;
	delete betModel;
	delete chairMap;
}

const quint16 PokerRoomModel::getId() const {
	return id;
}

void PokerRoomModel::setId(quint16 id) {
	this->id = id;
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

const BetModel* PokerRoomModel::getBetModel() const {
	return betModel;
}
void PokerRoomModel::setBetModel(BetModel* model){
	this->betModel = model;
}

const bool PokerRoomModel::isChairFree(quint16 chairId) const {
	return (chairMap != 0 && chairMap->value(chairId) == 0);
}

const bool PokerRoomModel::isReady() {
	return getFreeChairs().size() <= maxPlayers - 2;
}

void PokerRoomModel::addPlayer(PokerPlayerModel* player){
	mutex.lock();
	playerList->append(player);
	mutex.unlock();
	qDebug() << "PokerRoomModel::addPlayer# signal playerJoined emited " << endl;
	emit playerJoined(player);
}

void PokerRoomModel::addCard(CardModel model){
	cards.append(model);
}

void PokerRoomModel::joinTable(quint16 chairId, PokerPlayerModel* player){
	if (isChairFree(chairId)) {
		mutex.lock();
		chairMap->insert(chairId,player);
		mutex.unlock();
		qDebug() << "PokerRoomModel::joinTable# Player " << *(player->getName()) << " joined table " << *(getName()) << " chair = " << chairId << endl;
		qDebug() << "PokerRoomModel::joinTable# is ready ? " << endl;
		if (isReady()){
			qDebug() << "PokerRoomModel::joinTable# Yes !" << endl;
			emit ready();
			return;
		}
		qDebug() << "PokerRoomModel::joinTable# No !" << endl;
	} else {
		qDebug() << "PokerRoomModel::joinTable# WARNING! Failed to join table !!!" << endl;
	}
}

void PokerRoomModel::setMaxPlayers(quint16 mpl){
	this->maxPlayers = mpl;
}

const QList<quint16> PokerRoomModel::getFreeChairs() {
	QMutexLocker locker(&mutex);
	QList<quint16> freeChairs;
	for (quint16 i = 0;i<maxPlayers;i++) {
		if (chairMap->value(i) == 0){
			freeChairs << i;
		}
	}
	QString size;
	size.setNum(freeChairs.size());
	qDebug() << "PokerRoomModel::getFreeChairs# free places" << size << endl;
	return freeChairs;
}

QMap<quint16,PokerPlayerModel*>* PokerRoomModel::getChairPlayerMap() const {
	return chairMap;
}

QList<PokerPlayerModel*>* PokerRoomModel::getPlayerList() const{
	return playerList;
}
