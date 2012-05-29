#ifndef POKERROOMLISTENER_H
#define POKERROOMLISTENER_H
#include <QObject>
#include <QString>
#include "src/model/server/PokerRoomModel.h"
#include "src/model/server/PokerPlayerModel.h"
#include "src/server/AbstractServer.h"
#include "src/game/AbstractPokerGame.h"
#include "src/model/server/MsvClientMessage.h"
/**
 * @author rdir52_msv team
 */

class PokerRoomListener : public QObject {
Q_OBJECT
public:
	PokerRoomListener(PokerRoomModel* room);
	~PokerRoomListener();
	void setId(QString id);
	QString getId() const;
private slots:
	void slotReadClient();
	void slotClientDisconnect();
	void roomReady();
	void gameEnded();
	void slotPlayerJoined(PokerPlayerModel*);
	void sendMessage(QString* message, PokerPlayerModel* player);

private: 
	void connectSignal(QTcpSocket* pClientSocket);
	void processMessage(MsvClientMessage* clientMessage,PokerPlayerModel* player);
	PokerPlayerModel* getPlayerBySocket(quint16 socketDesk);
	QString id;
	void init();
	PokerRoomModel* room;
	AbstractPokerGame* game;
    quint16 m_nNextBlockSize;
};
#endif
