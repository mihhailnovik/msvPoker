#include "src/model/JoinTableInfoModel.h"

JoinTableInfoModel::JoinTableInfoModel(QObject *parent) : QObject(parent)
{
}

JoinTableInfoModel::~JoinTableInfoModel()
{

}

void JoinTableInfoModel::setPokerRoomModel(PokerRoomModel* model){
	this->joinedRoom = model;
}

PokerRoomModel* JoinTableInfoModel::getPokerRoomModel() const {
	return joinedRoom;
}
