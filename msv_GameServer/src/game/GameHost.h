#ifndef GAMEHOST_H
#define GAMEHOST_H
#include "src/server/AbstractServer.h"
#include "src/model/server/PokerHostModel.h"
#include "src/model/server/PokerPlayerModel.h"
#include "src/model/server/PokerRoomModel.h"
#include "src/service/AuthenticationService.h"
#include <QMap>
#include <QObject>
#include <QString>
#include <QTcpSocket>

/**
 * @author rdir52_msv team
 * Class receives processes and sends messages to clients.
 */

class GameHost : public QObject {
Q_OBJECT
public:
	GameHost(QObject *parent = 0);
	~GameHost();
private: 
	AuthenticationService* authService;
	AbstractServer* server;
	QMap<quint16,PokerPlayerModel*> *playersMap; // key is socket descriptor, if PokerPlaerModel is null, it means client isn't authenticated yet
	QMap<quint16,PokerRoomModel*> *pokerRoomMap; // key is pokerRoom id
	PokerHostModel* pokerHostModel; // host configuration data

	void init(); // this method calls when host object is created, it should load all configs, and start server
	void startServer(); // runs server
	void joinTable(quint16 tableId, PokerPlayerModel* player);
	void sendUnknowMessageFormatError(QTcpSocket* socket);
private slots:
	// this method should process only "server" request, if client join some pokerroom then this slot should'nt be notifed when client sends something related with game
     void dataReaded(const QString* message,QTcpSocket* socket);
};
#endif
