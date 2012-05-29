#include "src/model/ServerInfoModel.h"

ServerInfoModel::ServerInfoModel(QObject *parent)
    : QObject(parent)
{

}

void ServerInfoModel::setRoomList(QList<PokerRoomModel*>* roomList){
	this->roomList = roomList;
}

QList<PokerRoomModel*>* ServerInfoModel::getRoomList() const {
	return roomList;
}
