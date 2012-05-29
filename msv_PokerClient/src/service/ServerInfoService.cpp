#include "src/service/ServerInfoService.h"
#include "src/utils/MessageBuilder.h"
ServerInfoService::ServerInfoService(SocketHolder* holder)
{
	this->holder = holder;
}

void ServerInfoService::getServerInfo() {
	holder->sendData(MessageBuilder::buildGetServerInfoMessage());
}

void ServerInfoService::serverInfo(ServerInfoModel* serverInfo) {
	emit serverInfoReceived(serverInfo);
}

void ServerInfoService::joinTable(quint16 tableId) {
	QString table;
	table.setNum(tableId);
	holder->sendData(MessageBuilder::buildJoinTableMessage(table));
}

void ServerInfoService::roomJoined(PokerRoomModel* pokerRoom) {
	qDebug() << "ServerInfoService::roomJoined# pokerRoomJoined(pokerRoom) emited" << endl;
	emit pokerRoomJoined(pokerRoom);
}
