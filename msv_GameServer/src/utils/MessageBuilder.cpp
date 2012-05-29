#include "src/utils/MessageBuilder.h"
#include "src/model/server/PokerPlayerModel.h"
#include "src/utils/StringUtil.h"
#include "src/model/game_engine/CardModel.h"
#include <QList>
#include <QMap>
#include <QMapIterator>

QString* MessageBuilder::buildServerInfoResponse(const PokerHostModel* model){
	if (!model){
		qDebug() << "MessageBuilder::buildServerInfoResponse# model is null !!" << endl;
		return 0;
	}
	QString* message = new QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	message->append("<msvServerMessage>");
		message->append("<type>");
			message->append("server_info");
		message->append("</type>");
		message->append("<serverInfo>");
			message->append("<pokerRooms>");
			if (model->getPokerRoomList() != NULL) {
			QList<PokerRoomModel*>* pokerRooms = model->getPokerRoomList();
			 for (int i = 0; i < pokerRooms->size(); i++) {
				 message->append("<pokerroom>");
				 PokerRoomModel* room = pokerRooms->value(i);
					 message->append("<name>");
						 message->append(*(room->getName()));
					 message->append("</name>");
					 message->append("<type>");
						 message->append(*(room->getType()));
					 message->append("</type>");
					 message->append("<maxPlayers>");
						 QString maxPlayers;
						 maxPlayers.setNum(room->getMaxPlayers());
						 message->append(maxPlayers);
					 message->append("</maxPlayers>");
					 //TODO <bet> .. </bet> isnt necceseary atm
					 message->append("<players>");
					 QMapIterator<quint16,PokerPlayerModel*> iterator(*(room->getChairPlayerMap()));
					 while (iterator.hasNext()) {
						 iterator.next();
					     PokerPlayerModel* value = iterator.value();
					     if (value != 0) {
					    	 message->append("<player>");
								 message->append("<name>");
									 message->append(value->getName());
								 message->append("</name>");
								 message->append("<money>");
									 QString money;
									 money.setNum(value->getMoney());
									 message->append(money);
								 message->append("</money>");
								 message->append("<chair_id>");
									 QString chairId;
									 chairId.setNum(iterator.key());
									 message->append(chairId);
								 message->append("</chair_id>");
							 message->append("</player>");
					     }
					 }
					 message->append("</players>");
					 message->append("</pokerroom>");
				 }
			}
			message->append("</pokerRooms>");
			message->append("</serverInfo>");
		message->append("</msvServerMessage>");
	return message;
}

QString* MessageBuilder::buildAuthenticationOkResponse(const PokerPlayerModel* model){
	QString* message = new QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	message->append("<msvServerMessage>");
		message->append("<type>");
			message->append("authentication_succesfull");
		message->append("</type>");
		message->append("<authInfo>");
			message->append("<player>");
				message->append("<name>");
					message->append(*(model->getName()));
				message->append("</name>");
				message->append("<money>");
					message->append(QString::number(model->getMoney()));
				message->append("</money>");
			message->append("</player>");
		message->append("</authInfo>");
	 message->append("</msvServerMessage>");
	return message;
}

QString* MessageBuilder::buildPlayerJoinedChair(QString chairId, PokerPlayerModel* player){
	QString* message = new QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		message->append("<msvServerMessage>");
			message->append("<type>");
				message->append("player_joined_chair");
			message->append("</type>");

			message->append("<playerJoinedChair>");
				message->append("<player>");
					message->append("<name>");
						message->append(*(player->getName()));
					message->append("</name>");
					message->append("<money>");
						message->append(QString::number(player->getMoney()));
					message->append("</money>");
					message->append("<chair_id>");
						message->append(chairId);
					message->append("</chair_id>");
				message->append("</player>");

				message->append("<chair_id>");
					message->append(chairId);
				message->append("</chair_id>");
			message->append("</playerJoinedChair>");
		message->append("</msvServerMessage>");
	return message;
}

QString* MessageBuilder::buildAuthenticationFailedResponse(const AuthInfoModel* model){
	QString* message = new QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		message->append("<msvServerMessage>");
			message->append("<type>");
				message->append("auth_failed");
			message->append("</type>");
		message->append("</msvServerMessage>");
	return message;
}

QString* MessageBuilder::buildUnknownMessageFormatResponse(){
	return new QString("unknown_format");
}

QString* MessageBuilder::buildTableJoinSuccessfully(const PokerRoomModel* room1) {
	qDebug() << "MessageBuilder::buildTableJoinSuccessfully# starting building message " << endl;
	QString* message = new QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		message->append("<msvServerMessage>");
			message->append("<type>");
				message->append("join_table");
			message->append("</type>");
			message->append("<join_table>");
				message->append("<pokerroom>");
					message->append("<name>");
						message->append(*(room1->getName()));
					message->append("</name>");

					message->append("<type>");
						message->append(*(room1->getType()));
					message->append("</type>");

					message->append("<maxPlayers>");
						QString maxPlayers;
						maxPlayers.setNum(room1->getMaxPlayers());
						message->append(maxPlayers);
					message->append("</maxPlayers>");
					// TODO <bet>

					message->append("<players>");
						QMap<quint16,PokerPlayerModel*>* pokerPlayerMap =  room1->getChairPlayerMap();
						QMapIterator<quint16, PokerPlayerModel*> i(*pokerPlayerMap);
						qDebug() << "MessageBuilder::buildTableJoinSuccessfully# adding players to message" << endl;
							while (i.hasNext()) {
								i.next();
								PokerPlayerModel* player = i.value();
								if (player == NULL) {
									continue;
								}
								message->append("<player>");
									message->append("<name>");
										message->append(*(player->getName()));
									message->append("</name>");
									QString money;
									money.setNum(player->getMoney());
									message->append("<money>");
										message->append(money);
									message->append("</money>");

									QString chair;
									chair.setNum(i.key());
									message->append("<chair_id>");
										message->append(chair);
									message->append("</chair_id>");
								message->append("</player>");
								qDebug() << "MessageBuilder::buildTableJoinSuccessfully#" << *(player->getName()) << "added to message" << endl;
							}
					message->append("</players>");
				message->append("</pokerroom>");
			message->append("</join_table>");
		 message->append("</msvServerMessage>");
		return message;
}

QString* MessageBuilder::buildGameMessage(QMap<quint16, GamePlayerModel*> gamePlayers, PokerPlayerModel* player, QList<CardModel> cards, int money,int roomSize) {
	qDebug() << "MessageBuilder::buildPreflopMessage# starting building message " << endl;
	QString* message = new QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	message->append("<msvServerMessage>");
		message->append("<type>");
			message->append("game_action");
		message->append("</type>");

		message->append("<gameAction>");
			message->append("<maxPlayers>");
				message->append(StringUtil::valueOf(roomSize));
			message->append("</maxPlayers>");

			message->append("<players>");
			 QMapIterator<quint16, GamePlayerModel*> i(gamePlayers);
			 while (i.hasNext()) {
			     i.next();
			     message->append("<player>");
					 message->append("<name>");
						 message->append(*(i.value()->getPlayerModel()->getName()));
					 message->append("</name>");

					 message->append("<money>");
						 message->append(StringUtil::valueOf(i.value()->getPlayerModel()->getMoney()));
					 message->append("</money>");

					 message->append("<chair_id>");
						 message->append(StringUtil::valueOf(i.key()));
					 message->append("</chair_id>");

					 message->append("<diler>");
						 message->append(StringUtil::valueOf(i.value()->getDiler()));
					 message->append("</diler>");

					 message->append("<lastActionName>");
						 message->append(i.value()->getLastActionName());
					 message->append("</lastActionName>");

					 message->append("<currentRoundMoney>");
						 message->append(StringUtil::valueOf(i.value()->getRoundMoney()));
					 message->append("</currentRoundMoney>");

					 QList<CardModel> cards = i.value()->getCards();
					 if (!cards.isEmpty()) {
					 message->append("<cards>");
						 bool isAuthor = i.value()->getPlayerModel()->getSocket()->socketDescriptor() == player->getSocket()->socketDescriptor();
						 for (int i=0;i<cards.size();i++){
							 if (isAuthor) {
								 message->append("<card>");
									 message->append(cards.at(i).toString());
								 message->append("</card>");
							 } else {
								 message->append("<card>");
									 message->append("XX");
								 message->append("</card>");
							 }
						 }
						 message->append("</cards>");
					}
				message->append("</player>");
			 }
			message->append("</players>");

			message->append("<table>");
				message->append("<cards>");
					for (int i=0;i<cards.size();i++){
						message->append("<card>");
							message->append(cards[i].toString());
						message->append("</card>");
					}
				message->append("</cards>");
				message->append("<money>");
					message->append(QString::number(money));
				message->append("</money>");
			message->append("</table>");
		message->append("</gameAction>");
	message->append("</msvServerMessage>");
	return message;
}

QString* MessageBuilder::buildYourTurnMessage(){
	QString* message = new QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	message->append("<msvServerMessage>");
		message->append("<type>");
			message->append("your_turn");
		message->append("</type>");
	message->append("</msvServerMessage>");
	return message;
}
