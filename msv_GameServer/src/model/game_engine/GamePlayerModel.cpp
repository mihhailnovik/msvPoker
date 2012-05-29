#include "src/model/game_engine/GamePlayerModel.h"

GamePlayerModel::GamePlayerModel(PokerPlayerModel* player) {
	this->player = player;
	lastActionName = "Hello !";
	roundMoney = 0;
	diler = false;
}

GamePlayerModel::~GamePlayerModel(){
}


void GamePlayerModel::addCard(CardModel card){
	cardList.append(card);
}

QList<CardModel> GamePlayerModel::getCards() const {
	return cardList;
}

PokerPlayerModel* GamePlayerModel::getPlayerModel() const{
	return player;
}

void GamePlayerModel::addRoundMoney(quint16 addedMoney){
	roundMoney += addedMoney;
}

void GamePlayerModel::addMoney(quint16 money) {
	this->getPlayerModel()->setMoney(getPlayerModel()->getMoney()+money);
}

quint16 GamePlayerModel::getRoundMoney(){
	return roundMoney;
}

void GamePlayerModel::setRoundMoney(quint16 money){
	this->roundMoney = money;
}

void GamePlayerModel::setDiler(bool diler) {
	this->diler = diler;
}

bool GamePlayerModel::getDiler() const {
	return diler;
}

void GamePlayerModel::foldCards() {
	cardList.clear();
}

void GamePlayerModel::setLastActionName(QString lastActionName){
	this->lastActionName = lastActionName;
}

QString GamePlayerModel::getLastActionName(){
	return lastActionName;
}
