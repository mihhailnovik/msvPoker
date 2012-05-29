#include "src/model/PokerPlayerModel.h"
#include "src/utils/StringUtil.h"

PokerPlayerModel::PokerPlayerModel(const PokerPlayerModel&){

} // i do not need this, do not use it

PokerPlayerModel::PokerPlayerModel(QObject *parent)
    : QObject(parent)
{
	this->roundMoney = 0;
	lastAction = " Hello !";
}

void PokerPlayerModel::setName(QString* name){
	this->name = name;
}

QString* PokerPlayerModel::getName() const {
	return name;
}

void PokerPlayerModel::setMoney(quint16 money) {
	this->money = money;
}

quint16 PokerPlayerModel::getMoney() const {
	return money;
}

QString PokerPlayerModel::getMoneyStr() const{
	QString moneyStr;
	moneyStr.setNum(money);
	return moneyStr;
}

quint16 PokerPlayerModel::getChairId() const{
	return this->chairId;
}

void PokerPlayerModel::setChairId(quint16 chairId){
	this->chairId = chairId;
}

void PokerPlayerModel::setRoundMoney(quint16 money){
	this->roundMoney = money;
}

quint16 PokerPlayerModel::getRoundMoney() const{
	return roundMoney;
}

void PokerPlayerModel::setAvatarPic(QString avatarPic){
	this->avatarPic = avatarPic;
}

QString PokerPlayerModel::getAvatarPic() const{
	if (StringUtil::isEquals(*(getName()),"mi1")) {
		return "1";
	}
	if (StringUtil::isEquals(*(getName()),"Viktor")) {
		return "2";
	}
	if (StringUtil::isEquals(*(getName()),"s1aY")) {
		return "3";
	}
	if (StringUtil::isEquals(*(getName()),"roma")) {
		return "4";
	}
	return "1";
}

void PokerPlayerModel::setCardList(QList<CardModel> cardList){
	this->cardList = cardList;
}

QList<CardModel> PokerPlayerModel::getCardList() const{
	return cardList;
}

void PokerPlayerModel::setDiler(bool diler){
	this->diler = diler;
}

bool PokerPlayerModel::getDiler() const{
	return diler;
}

void PokerPlayerModel::setLastAction(QString action){
	this->lastAction = action;
}

QString PokerPlayerModel::getAction() const {
	return lastAction;
}
