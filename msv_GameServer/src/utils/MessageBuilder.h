#ifndef MESSAGEBUILDER_H
#define MESSAGEBUILDER_H

#include "src/model/server/JoinTableInfoModel.h"
#include "src/model/server/AuthInfoModel.h"
#include "src/model/server/PokerPlayerModel.h"
#include "src/model/server/PokerHostModel.h"
#include "src/model/game_engine/GamePlayerModel.h"
#include "src/model/game_engine/CardModel.h"
#include <QMap>
#include <QString>

/*
 * @author rdir52_msv team
 * Builds MsvServerMessages objects
 */
class MessageBuilder {

public:
	static QString* buildServerInfoResponse(const PokerHostModel* hostModel); // returns server answer message :)
	static QString* buildAuthenticationOkResponse(const PokerPlayerModel* model);
	static QString* buildAuthenticationFailedResponse(const AuthInfoModel* model);
	static QString* buildUnknownMessageFormatResponse();
	static QString* buildTableJoinSuccessfully(const PokerRoomModel* room);
	static QString* buildPlayerJoinedChair(QString chairId, PokerPlayerModel* player);
	static QString* buildGameMessage(QMap<quint16, GamePlayerModel*> gamePlayers, PokerPlayerModel* player,QList<CardModel> cards, int money,int roomSize);
	static QString* buildYourTurnMessage();
};

#endif
