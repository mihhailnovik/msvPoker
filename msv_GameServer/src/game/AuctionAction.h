#ifndef AUCTIONACTION_H
#define AUCTIONACTION_H
#include <QObject>
#include <QMap>
#include <QList>
#include "src/model/game_engine/GamePlayerModel.h"
#include "src/model/game_engine/AuctionPlayerModel.h"
#include "src/model/server/MsvClientMessage.h"
#include "src/game/TexasHoldemPokerGame.h"
#include "src/model/game_engine/GameBankModel.h"
#include "src/model/game_engine/CardModel.h"

class AuctionAction : public QObject {
Q_OBJECT
public:
	AuctionAction(QMap<quint16, GamePlayerModel*>* players,TexasHoldemPokerGame* game,GameBankModel* bank,QList<CardModel> cardsInTable);
	~AuctionAction();
	void doAuction();
private:
	TexasHoldemPokerGame* game; // i need this only for sending message
	QMap<quint16, GamePlayerModel*>* players;
	QMap<quint16, AuctionPlayerModel*> auctionPlayers;
	quint16 dilerChair;
	quint16 auctionBank; // current auction summ
	quint16 getDilerChair(QMap<quint16, GamePlayerModel*> players);
	quint16 getCurrentAuctionTop(QMap<quint16, AuctionPlayerModel*> players);
	AuctionPlayerModel* getCurrentBetPlayer();
	MsvClientMessage* getPlayerMessage(AuctionPlayerModel* resultPlayer);
	void processAuctionMessage(MsvClientMessage* message,AuctionPlayerModel* player);

	GameBankModel* bank;
	QList<CardModel> cardsInTable;
};
#endif
