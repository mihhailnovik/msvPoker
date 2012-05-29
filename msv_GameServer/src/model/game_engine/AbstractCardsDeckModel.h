#ifndef ABSTRACTCARDSDECKMODEL_H
#define ABSTRACTCARDSDECKMODEL_H
#include <QObject>
#include <QList>
#include "src/model/game_engine/CardModel.h"
/**
 * @author rdir52_msv team
 */

class AbstractCardsDeckModel: public QObject {
	Q_OBJECT
public:
	AbstractCardsDeckModel();
	~AbstractCardsDeckModel();
	virtual QList<CardModel> getRandomCards(quint16 count) = 0;
	virtual CardModel getRandomCard() = 0;
	virtual void shuffle() = 0; // renew card deck and mix cards (actualy mixing isn't necceseary because all cards taken by random, but anyway..

protected:
	QList<CardModel> cardDeck;
};
#endif
