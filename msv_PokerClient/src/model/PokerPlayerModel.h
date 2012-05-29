#ifndef POKERPLAYERMODEL_H
#define POKERPLAYERMODEL_H
#include <QObject>
#include <QString>
#include <QList>
#include "src/model/game_engine/CardModel.h"

class PokerPlayerModel : public QObject
{
	Q_OBJECT
public:
	PokerPlayerModel(QObject *parent = 0);
	PokerPlayerModel(const PokerPlayerModel&);
	void setName(QString* name);
	QString* getName() const;
	void setMoney(quint16 money);
	quint16 getMoney() const;
	QString getMoneyStr() const;

	quint16 getChairId() const;
	void setChairId(quint16 chairId);

	void setRoundMoney(quint16 money);
	quint16 getRoundMoney() const;

	void setAvatarPic(QString avatarPic);
	QString getAvatarPic() const;

	void setCardList(QList<CardModel> cardList);
	QList<CardModel> getCardList() const;

	void setDiler(bool diler);
	bool getDiler() const;

	void setLastAction(QString action);
	QString getAction() const;

private:
	QString avatarPic;
	QString* name;
	QString lastAction;
	quint16 money;
	quint16 chairId; // XXX this variable shouldn't be here, but... i suck :(
	quint16 roundMoney;
	QList<CardModel> cardList;
	bool diler;
};
#endif
