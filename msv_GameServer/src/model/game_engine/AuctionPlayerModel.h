#ifndef AUCTIONPLAYERMODEL_H
#define AUCTIONPLAYERMODEL_H
#include <QObject>
#include "src/model/game_engine/GamePlayerModel.h"
/**
 * @author rdir52_msv team
 */

class AuctionPlayerModel: public QObject {
	Q_OBJECT
public:
	AuctionPlayerModel(quint16 chairId, GamePlayerModel* player);
	~AuctionPlayerModel();
	GamePlayerModel* getGamePlayer() const;
	void setGamePlayer(GamePlayerModel* player);
	bool getAllIn() const;
	void setAllIn(bool);

	quint16 getChairId() const;
	void setChairId(quint16);

	bool isFold() const;
	void setFold(bool);

	quint16 chairId;

	void setWasInAutction(bool);
	bool getWasInAuction();
private:
	bool fold;
	bool allIn;
	bool wasInAuction; // if that player already was in auction
	GamePlayerModel* player;
};
#endif
