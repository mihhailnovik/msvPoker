#ifndef GAME_PLAYER_MODEL_H
#define GAME_PLAYER_MODEL_H
#include <QObject>
#include <QList>
#include "src/model/server/PokerPlayerModel.h"
#include "src/model/game_engine/CardModel.h"

/**
 * @author rdir52_msv team
 */

class GamePlayerModel: public QObject {
	Q_OBJECT
public:
	GamePlayerModel(PokerPlayerModel* player);
	~GamePlayerModel();
	void addCard(CardModel card);
	QList<CardModel> getCards() const;
	void foldCards();
	PokerPlayerModel* getPlayerModel() const;
	void addRoundMoney(quint16 addedeMoney);
	void addMoney(quint16 money);
	quint16 getRoundMoney();
	void setRoundMoney(quint16 money);
	void setDiler(bool);
	bool getDiler() const;

	void setLastActionName(QString string);
	QString getLastActionName();
private:
	PokerPlayerModel* player;
	QString lastActionName;
	QList<CardModel> cardList;
	quint16 roundMoney;
	bool diler;
};
#endif
