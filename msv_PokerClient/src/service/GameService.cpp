#include "src/service/GameService.h"
#include "src/utils/MessageBuilder.h"
#include <QTimer>

GameService::GameService(SocketHolder* holder)
{
	this->holder = holder;
}


void GameService::takeSeat(quint16 chairId) {
	QString chairStr;
	chairStr.setNum(chairId);
	qDebug() << "ServerInfoService::takeSeat# chaird = " << chairStr << endl;
	holder->sendData(MessageBuilder::buildTakeSeatMessage(chairStr));
}

void GameService::playerJoinedChair(PokerPlayerModel* player,quint16 chairId){
	room->getChairMap()->insert(chairId,player);
	emit contentUpdated();
}

void GameService::setPokerRoom(PokerRoomModel* room){
	this->room = room;
}

PokerRoomModel* GameService::getPokerRoom() const{
	return room;
}

void GameService::pokerRoomUpdated(PokerRoomModel* model){
	room->setMoney(model->getMoney());
	QMap<quint16,PokerPlayerModel*>* chairMap = room->getChairMap();
	QMapIterator<quint16,PokerPlayerModel*> i(*(chairMap));
	while (i.hasNext()) {
		i.next();
		if (i.value() == NULL){
			chairMap->insert(i.key(),model->getChairMap()->value(i.key()));
		}
		else {
			updatePokerPlayer(i.value(),model->getChairMap()->value(i.key()));
		}
	}
	QList<CardModel*>* cardList = model->getCards();

	room->getCards()->clear();
	for (int i=0;i<cardList->size();i++){
		room->addCard(cardList->at(i));
	}

	qDebug() << "GameService::pokerRoomUpdated# have received model cards "
			<< !(model->getCards()->isEmpty()) << " our room ? " << !(room->getCards()->isEmpty());
	emit contentUpdated();
}

void GameService::yourTurnEvent(){
	emit enableBetButtons();
}

void GameService::slotYourTurnEnd(){
	qDebug() << "GameService::slotYourTurnEnd# " << endl;
	emit disableBetButtons();
}

void GameService::updatePokerPlayer(PokerPlayerModel* oldPlayer,PokerPlayerModel* newPlayer){
	oldPlayer->setCardList(newPlayer->getCardList());
	oldPlayer->setDiler(newPlayer->getDiler());
	oldPlayer->setAvatarPic(newPlayer->getAvatarPic());
	oldPlayer->setChairId(newPlayer->getChairId());
	oldPlayer->setLastAction(newPlayer->getAction());
	oldPlayer->setMoney(newPlayer->getMoney());
	oldPlayer->setRoundMoney(newPlayer->getRoundMoney());
}

void GameService::bet(int sum) {
	holder->sendData(MessageBuilder::buildGameAction(sum));
}
