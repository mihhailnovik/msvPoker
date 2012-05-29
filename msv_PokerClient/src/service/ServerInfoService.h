#ifndef SERVERINFOSERVICE_H
#define SERVERINFOSERVICE_H
#include "src/utils/SocketHolder.h"
#include "src/model/ServerInfoModel.h"
#include "src/model/game_engine/PokerRoomModel.h"
#include <QObject>

class ServerInfoService : public QObject
{
	Q_OBJECT
public:
	ServerInfoService(SocketHolder* holder);
	void getServerInfo();
	void serverInfo(ServerInfoModel* serverInfo);
	void joinTable(quint16 tableId);
	void roomJoined(PokerRoomModel* serverInfo);
	void takeSeat(quint16 chairId);

signals:
	void serverInfoReceived(ServerInfoModel* serverInfo);
	void pokerRoomJoined(PokerRoomModel* serverInfo);
private:
	SocketHolder* holder;
};
#endif
