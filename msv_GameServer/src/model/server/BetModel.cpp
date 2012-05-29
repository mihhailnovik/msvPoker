#include "src/model/server/BetModel.h"

BetModel::BetModel(QObject* parent): QObject(parent) {

}

BetModel::~BetModel() {

}

quint16 BetModel::getBuyInMin() const{
	return buyInMin;
}
quint16 BetModel::getBuyInMax() const{
	return buyInMax;
}
quint16 BetModel::getBigBlind() const{
	return bigBlind;
}
quint16 BetModel::getSmallBlind() const{
	return smallBlind;
}
quint16 BetModel::getMinRaisePercent() const{
	return minRaisePercent;
}
quint16 BetModel::getMaxRaisePercent() const{
	return maxRaisePercent;
}
void BetModel::setBuyInMin(quint16 buyInMin) {
	this->buyInMin = buyInMin;
}
void BetModel::setBuyInMax(quint16 buyInMax) {
	this->buyInMax = buyInMax;
}
void BetModel::setBigBlind(quint16 bigBlind) {
	this->bigBlind = bigBlind;
}
void BetModel::setSmallBlind(quint16 smallBlind) {
	this->smallBlind = smallBlind;
}
void BetModel::setMinRaisePercent(quint16 minRaisePercent) {
	this->minRaisePercent = minRaisePercent;
}
void BetModel::setMaxRaisePercent(quint16 maxRaisePercent) {
	this->maxRaisePercent = maxRaisePercent;
}
