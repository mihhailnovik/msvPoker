#ifndef TEXASHOLDEMPOKERGAME_H
#define TEXASHOLDEMPOKERGAME_H
#include <QMap>
#include <QString>
#include "src/game/AbstractPokerGame.h"
#include "src/model/server/PokerPlayerModel.h"
#include "src/model/game_engine/GamePlayerModel.h"
#include "src/model/game_engine/GameBankModel.h"
/**
 * @author rdir52_msv team
 * Texas holdem game logic
 */

class TexasHoldemPokerGame : public AbstractPokerGame {
	Q_OBJECT
public:
	TexasHoldemPokerGame(PokerRoomModel* room);
	~TexasHoldemPokerGame();
	void run();
	bool isRunning();
	void sendMessage(QMap<quint16, GamePlayerModel*> gamePlayers,GameBankModel* bank,QList<CardModel> list);
	void emitSendMessage(QString* message, PokerPlayerModel* player);
private:
	void doAuction(QMap<quint16, GamePlayerModel*>* players,GameBankModel* bank,QList<CardModel> cardsInTable);
	quint16 dilerNr;
	void pause(quint16 milisec);
	int getPlayersWithCardCount(QMap<quint16, GamePlayerModel*>* gamePlayersMap);
	GamePlayerModel* getWinner(QMap<quint16, GamePlayerModel*>* gamePlayersMap);
	void detectWinner(QMap<quint16, GamePlayerModel*>* gamePlayersMap,QList<CardModel> cardsInTable);
signals:
	void sendMessage(QString* message, PokerPlayerModel* player);
	void gameEnded();
};
#endif
