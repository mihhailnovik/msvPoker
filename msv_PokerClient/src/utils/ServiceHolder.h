#ifndef SERVICEHOLDER_H
#define SERVICEHOLDER_H
#include <QObject>
#include "src/utils/SocketHolder.h"
#include "src/service/LoginService.h"
#include "src/service/ServerInfoService.h"
#include "src/service/GameService.h"
/**
 *	Keep all service classes
 */
class ServiceHolder : public QObject
{
	Q_OBJECT
public:
	ServiceHolder(SocketHolder* socketHolder);
	LoginService* getLoginService();
	ServerInfoService* getServerInfoService();
	GameService* getGameService();
private slots:
	void dataReaded(MsvServerMessage* message);
private:
	quint16 m_nNextBlockSize;
	SocketHolder* socketHolder;
	LoginService* loginService;
	ServerInfoService* serverInfoService;
	GameService* gameService;
};
#endif
