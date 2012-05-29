#ifndef JOINTABLEINFOMODEL_H
#define JOINTABLEINFOMODEL_H
#include <QObject>
#include "src/model/game_engine/PokerRoomModel.h"
class JoinTableInfoModel : public QObject {
	Q_OBJECT
public:
	JoinTableInfoModel(QObject *parent = 0);
	~JoinTableInfoModel();
	void setPokerRoomModel(PokerRoomModel* model);
	PokerRoomModel* getPokerRoomModel() const;
private:
	PokerRoomModel* joinedRoom;
};
#endif
