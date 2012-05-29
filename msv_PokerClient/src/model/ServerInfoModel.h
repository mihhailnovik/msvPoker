#ifndef SERVERINFOMODEL_H
#define SERVERINFOMODEL_H
#include <QObject>
#include <QString>
#include <QList>
#include "src/model/game_engine/PokerRoomModel.h"

class ServerInfoModel : public QObject
{
	Q_OBJECT
public:
	ServerInfoModel(QObject *parent = 0);
	void setRoomList(QList<PokerRoomModel*>* roomList);
	QList<PokerRoomModel*>* getRoomList() const;
private:
	QList<PokerRoomModel*>* roomList;
};
#endif
