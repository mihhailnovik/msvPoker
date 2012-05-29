#include "src/model/PlayerJoinChairModel.h"

PlayerJoinChairModel::PlayerJoinChairModel(QObject *parent) : QObject(parent)
{
}

PlayerJoinChairModel::~PlayerJoinChairModel()
{

}

void PlayerJoinChairModel::setChairId(quint16 chairId) {
	this->chairId = chairId;
}

quint16 PlayerJoinChairModel::getChairId() const{
	return chairId;
}

void PlayerJoinChairModel::setPokerPlayerModel(PokerPlayerModel* player){
	this->player = player;
}

PokerPlayerModel* PlayerJoinChairModel::getPokerPlayerModel() const{
	return player;
}
