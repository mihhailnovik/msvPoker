#include "src/utils/ServiceHolder.h"

ServiceHolder::ServiceHolder(SocketHolder* socketHolder)
{
	this->socketHolder = socketHolder;
	loginService = new LoginService(socketHolder);
	serverInfoService = new ServerInfoService(socketHolder);
	gameService = new GameService(socketHolder);
	connect(socketHolder, SIGNAL(dataReaded(MsvServerMessage*)), this,SLOT(dataReaded(MsvServerMessage*)));
	qDebug() << "ServiceHolder::ServiceHolder# Service holder listening socketHolder " << endl;
}

LoginService* ServiceHolder::getLoginService() {
		return loginService;
}

ServerInfoService* ServiceHolder::getServerInfoService(){
	return serverInfoService;
}

GameService* ServiceHolder::getGameService() {
	return gameService;
}

void ServiceHolder::dataReaded(MsvServerMessage* message){
	qDebug() << "ServiceHolder::dataReaded#" <<*(message->getType()) << endl;
	if (message == NULL){
		qDebug() << "ServiceHolder::dataReaded# WARNING! message is null" << endl;
		return;
	}
	if (message->isAuthentication()){
		qDebug() << "ServiceHolder::dataReaded# Authentication service called" << endl;
		loginService->authetication(message);
		return;
	}
	if (message->isAuthFailed()){
		qDebug() << "ServiceHolder::dataReaded# Authentication service called" << endl;
		loginService->authetication(message);
		return;
	}
	if (message->isServerInfo()) {
		qDebug() << "ServiceHolder::dataReaded# ServerInfo service called" << endl;
		serverInfoService->serverInfo(message->getServerInfoModel());
		return;
	}
	if (message->isJoinTable()){
		qDebug() << "ServiceHolder::dataReaded# Join Table" << endl;
		serverInfoService->roomJoined(message->getJoinTableInfoModel()->getPokerRoomModel());
		return;
	}

	if (message->isPlayerJoinChair()) {
		qDebug() << "ServiceHolder::dataReaded# Join Chair " << *(message->getPlayerJoinChairModel()->getPokerPlayerModel()->getName()) << endl;
		gameService->playerJoinedChair(message->getPlayerJoinChairModel()->getPokerPlayerModel(),message->getPlayerJoinChairModel()->getChairId());
		return;
	}

	if (message->isGameAction()) {
		qDebug() << "ServiceHolder::dataReaded# game action " << endl;
		gameService->pokerRoomUpdated(message->getPokerRoomModel());
		return;
	}

	if (message->isYourTurn()) {
		gameService->yourTurnEvent();
		return;
	}

	qDebug() << "ServiceHolder::dataReaded# Warning message received but not processed !" << endl;
}
