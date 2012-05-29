#ifndef GAMESERVICE_H
#define GAMESERVICE_H
#include "src/utils/SocketHolder.h"
#include "src/model/game_engine/PokerRoomModel.h"

#include <QObject>

class GameService : public QObject
{
	Q_OBJECT
public:
	GameService(SocketHolder* holder);
	void setPokerRoom(PokerRoomModel* room);
	PokerRoomModel* getPokerRoom() const;
	void takeSeat(quint16 chairId);
	void playerJoinedChair(PokerPlayerModel* player,quint16 chairId);
	void pokerRoomUpdated(PokerRoomModel* model);
	void updatePokerPlayer(PokerPlayerModel* oldPlayer,PokerPlayerModel* newPlayer);
	void yourTurnEvent();

	/**
	 * Game action (fold, call, check, raise)
	 * if fold then sum = -1
	 * if check then sum = 0
	 * if call then sum = callSum
	 * if raise then sum = raiseSum :)
	 */
	void bet(int sum);
private:
	SocketHolder* holder;
	PokerRoomModel* room;
private slots:
	void slotYourTurnEnd();
signals:
	void contentUpdated();
	void enableBetButtons();
	void disableBetButtons();
};
#endif
