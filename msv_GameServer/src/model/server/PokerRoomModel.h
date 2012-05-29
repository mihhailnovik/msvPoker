#ifndef POKERROOMMODEL_H
#define POKERROOMMODEL_H
#include <QString>
#include <QMap>
#include <QObject>
#include <QList>
#include <QMutex>
#include "src/model/server/PokerPlayerModel.h"
#include "src/model/server/BetModel.h"
#include "src/model/game_engine/CardModel.h"

class PokerRoomModel : public QObject {
	Q_OBJECT
public:
	PokerRoomModel(QObject *parent = 0, quint16 maxPlayers = 0);
	~PokerRoomModel();
	const quint16 getId() const;
	void setId(quint16 id);
	const QString* getName() const;
	void setName(QString* name) ;
	const QString* getType() const;
	void setType(QString* type) ;
	const quint16 getMaxPlayers() const;
	void setMaxPlayers(quint16 mpl);
	const BetModel* getBetModel() const;
	void setBetModel(BetModel* model) ;
	const bool isChairFree(quint16 chairId) const;
	const bool isReady(); // return true if room have enough players to play
	void joinTable(quint16 chairId,PokerPlayerModel* player); // join player to current room
	const QList<quint16> getFreeChairs();
	QMap<quint16,PokerPlayerModel*>* getChairPlayerMap() const;
	void addPlayer(PokerPlayerModel* player);
	QList<PokerPlayerModel*>* getPlayerList() const;
	void addCard(CardModel model);
signals:
	void playerJoined(PokerPlayerModel* player);
	void ready();
private:
	QString* name;
	QString* type;
	quint16 maxPlayers;
	BetModel* betModel;
	QMutex mutex;
	QList<PokerPlayerModel*>* playerList; // players connected to this table
	QMap<quint16,PokerPlayerModel*>* chairMap; // players by chairs
	QList<CardModel> cards;
	quint16 id;
};
#endif
