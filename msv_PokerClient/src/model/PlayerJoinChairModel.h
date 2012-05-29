#ifndef PLAYERJOINCHAIRMODEL_H
#define PLAYERJOINCHAIRMODEL_H
#include <QObject>
#include "src/model/PlayerJoinChairModel.h"
#include "src/model/PokerPlayerModel.h"
class PlayerJoinChairModel : public QObject {
	Q_OBJECT
public:
	PlayerJoinChairModel(QObject *parent = 0);
	~PlayerJoinChairModel();
	void setChairId(quint16 chairId);
	quint16 getChairId() const;
	void setPokerPlayerModel(PokerPlayerModel* player);
	PokerPlayerModel* getPokerPlayerModel() const;
private:
	PokerPlayerModel* player;
	quint16 chairId;
};
#endif
