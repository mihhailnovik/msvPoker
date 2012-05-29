#ifndef POKERGAMEHELPER_H
#define POKERGAMEHELPER_H
#include <QMap>
#include <QList>
#include "src/model/server/PokerPlayerModel.h"
#include "src/model/game_engine/GamePlayerModel.h"
#include "src/model/game_engine/AuctionPlayerModel.h"
#include "src/model/game_engine/CardModel.h"
/*
 * @author rdir52_msv team
 */
class PokerGameHelper {
public:
	static quint16 getNextSit(QMap<quint16,GamePlayerModel*> playersMap,quint16 nr);
	static quint16 getNextSit(QMap<quint16, AuctionPlayerModel*> map,quint16 exDiler);

	static int getCardRank(QList<CardModel> cards);
	static bool isContain(QList<CardModel> cards,int suit, int rank);

	static bool isRoyalFlush(QList<CardModel> cards);
	static bool isFour(QList<CardModel> cards);
	static bool isFullHouse(QList<CardModel> cards);
	static bool isFlush(QList<CardModel> cards);
	static bool isStraight(QList<CardModel> cards);
	static bool isThree(QList<CardModel> cards);
	static int getTwoPairPowah(QList<CardModel> cards);
	static int getPairPowah(QList<CardModel> cards);
	static int getKickerPowah(QList<CardModel> cards);

};
#endif
