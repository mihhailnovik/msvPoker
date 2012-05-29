#ifndef POKERROOMMODEL_H
#define POKERROOMMODEL_H
#include <QString>
#include <QMap>
#include <QObject>
#include <QList>
#include <QMutex>
#include "src/model/PokerPlayerModel.h"
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

	const bool isChairFree(quint16 chairId) const;
	const QList<quint16> getFreeChairs() const;

	void takeSeat(PokerPlayerModel* model, quint16 chairId);

	void lock();
	void unlock();

	void setMoney(quint16 money);
	quint16 getMoney() const;

	QList<CardModel*>* getCards() const;
	void setCards(QList<CardModel*>*);
	void addCard(CardModel* model);

	QMap<quint16,PokerPlayerModel*>* getChairMap() const;
	void setChairMap(QMap<quint16,PokerPlayerModel*>*);

private:
	quint16 money;
	quint16 id;
	QString* name;
	QString* type;
	quint16 maxPlayers;
	QMap<quint16,PokerPlayerModel*>* chairMap;
	QMutex mutex;
	QList<CardModel*>* cards;
};
#endif
