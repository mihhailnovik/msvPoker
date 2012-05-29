#include "src/game/AuctionAction.h"
#include "src/utils/PokerGameHelper.h"
#include "src/utils/MessageSenderUtil.h"
#include "src/utils/MessageBuilder.h"
#include "src/game/AbstractPokerGame.h"
#include <QMapIterator>
#include <QList>
#include <QWaitCondition>
#include <QMutex>

AuctionAction::AuctionAction(QMap<quint16, GamePlayerModel*>* players,TexasHoldemPokerGame* game,GameBankModel* bank,QList<CardModel> cardsInTable) {
	this->game = game;
	this->players = players;
	this->bank = bank;
	this->cardsInTable = cardsInTable;

	QMapIterator<quint16, GamePlayerModel*> i(*(players));
	while (i.hasNext()) {
	   i.next();
	   auctionPlayers.insert(i.key(),new AuctionPlayerModel(i.key(),i.value()));
	}
	dilerChair = getDilerChair(*(players));
	auctionBank = getCurrentAuctionTop(auctionPlayers);
}

AuctionAction::~AuctionAction(){

}

MsvClientMessage* AuctionAction::getPlayerMessage(AuctionPlayerModel* resultPlayer) { // returns null if player didnt send anything
	qDebug() << "AuctionAction::doAuction# Waiting " << *(resultPlayer->getGamePlayer()->getPlayerModel()->getName())<< " action..." ;
	QMutex* mutex = new QMutex();
	QWaitCondition cond;
	mutex->lock();
	for (int i = 0;i<20;i++) { // waiting for action 20 seconds
		qDebug() << "...";
		cond.wait(mutex,1000);
		if (!(resultPlayer->getGamePlayer()->getPlayerModel()->getMessagePool()->isEmpty())) {
			qDebug() << endl << "AuctionAction::doAuction# i got action message from " << *(resultPlayer->getGamePlayer()->getPlayerModel()->getName()) << endl;
			MsvClientMessage* returnMessage = resultPlayer->getGamePlayer()->getPlayerModel()->getMessagePool()->last();
			resultPlayer->getGamePlayer()->getPlayerModel()->getMessagePool()->clear();
			return returnMessage;
		}
	}
	mutex->unlock();
	delete mutex;
	return NULL;
}

void AuctionAction::doAuction(){
	qDebug () << "AuctionAction::doAuction# ";
	QMapIterator<quint16, AuctionPlayerModel*> i(auctionPlayers);
		while (i.hasNext()) {
		   i.next();
		   qDebug() << i.key() << " -> " << *(i.value()->getGamePlayer()->getPlayerModel()->getName()) << endl;
		}
	AuctionPlayerModel* resultPlayer = NULL;
	while ((resultPlayer = getCurrentBetPlayer()) != NULL && auctionPlayers.size() > 1) {
		game->emitSendMessage(MessageBuilder::buildYourTurnMessage(),resultPlayer->getGamePlayer()->getPlayerModel());
		MsvClientMessage* message = getPlayerMessage(resultPlayer);
		processAuctionMessage(message,resultPlayer);
		game->sendMessage(*(players),bank,cardsInTable);
	}

	QMapIterator<quint16, AuctionPlayerModel*> i2(auctionPlayers);
	while (i2.hasNext()) {
		i2.next();
		i2.value()->getGamePlayer()->setRoundMoney(0);
	}
	qDebug() << "AuctionAction::doAuction# auction finished" << endl;
}

void AuctionAction::processAuctionMessage(MsvClientMessage* message,AuctionPlayerModel* resultPlayer){
	if (message == NULL){
		message = new MsvClientMessage();
		message->setBet(-1);
	}
	resultPlayer->setWasInAutction(true);// he already was !:)
	if (message->getBet() == -1) { // if fold
		qDebug() << "AuctionAction::processAuctionMessage# It's a fold in chair " << resultPlayer->getChairId() <<
				" name = "<<*(resultPlayer->getGamePlayer()->getPlayerModel()->getName()) <<";*(" << endl;
		auctionPlayers.remove(resultPlayer->getChairId());
		resultPlayer->setFold(true);
		resultPlayer->getGamePlayer()->foldCards();
		resultPlayer->getGamePlayer()->setRoundMoney(0);
		resultPlayer->getGamePlayer()->setLastActionName("Fold");
		return;
	}

	if (message->getBet()+resultPlayer->getGamePlayer()->getRoundMoney() < auctionBank ) {
		qDebug() << "AuctionAction::processAuctionMessage# Yahooo All in!" << endl;
		resultPlayer->setAllIn(true);
		resultPlayer->getGamePlayer()->getPlayerModel()->takeMoney(message->getBet());
		resultPlayer->getGamePlayer()->setLastActionName("All in");
		if (resultPlayer->getGamePlayer()->getPlayerModel()->takeMoney(message->getBet())) {
			resultPlayer->getGamePlayer()->addRoundMoney(message->getBet());
			bank->add(message->getBet());
		}
		auctionPlayers.remove(resultPlayer->getChairId());
		return;
	}

	if (message->getBet()+resultPlayer->getGamePlayer()->getRoundMoney() == auctionBank) {
		qDebug() << "AuctionAction::processAuctionMessage# Call ! " << endl;
		resultPlayer->getGamePlayer()->setLastActionName("Call");
		if (resultPlayer->getGamePlayer()->getPlayerModel()->takeMoney(message->getBet())) {
			resultPlayer->getGamePlayer()->addRoundMoney(message->getBet());
			bank->add(message->getBet());
		}
		else {
			resultPlayer->setFold(true);
			resultPlayer->getGamePlayer()->foldCards();
			resultPlayer->getGamePlayer()->setRoundMoney(0);
			resultPlayer->getGamePlayer()->setLastActionName("Fold");
			return; // TODO if player do not have enough money, then fold it's ofcouse bad, but who cares ?
		}
		return;
	}
	if (message->getBet()+resultPlayer->getGamePlayer()->getRoundMoney() > auctionBank) {
		qDebug() << "AuctionAction::doAuction# Raise ! " << endl;
		resultPlayer->getGamePlayer()->setLastActionName("Raise");
		if (resultPlayer->getGamePlayer()->getPlayerModel()->takeMoney(message->getBet())) {
			resultPlayer->getGamePlayer()->addRoundMoney(message->getBet());
			bank->add(message->getBet());
		} else {
			resultPlayer->setFold(true);
			resultPlayer->getGamePlayer()->foldCards();
			resultPlayer->getGamePlayer()->setRoundMoney(0);
			resultPlayer->getGamePlayer()->setLastActionName("Fold");
			return; // TODO if player do not have enough money, then fold it's ofcouse bad, but who cares ?
		}
	}
}

/**
 * This method should return player who is current bet player
 */
AuctionPlayerModel* AuctionAction::getCurrentBetPlayer(){
	qDebug() << "AuctionAction::getCurrentBetPlayer# start" << endl;
	AuctionPlayerModel* resultPlayer = NULL;
	auctionBank = getCurrentAuctionTop(auctionPlayers);
	QMapIterator<quint16, AuctionPlayerModel*> i(auctionPlayers);
	quint16 chairId;

	// found first player who got current bank top
	while (i.hasNext()) {
	   i.next();
	   if (i.value()->getGamePlayer()->getRoundMoney() == auctionBank) {
		   chairId = i.key();
		   qDebug() << "AuctionAction::getCurrentBetPlayer# top bet found in chair " << chairId<< endl;
		   break;
	   }
	   chairId =i.key();
	}

	int mapSize = auctionPlayers.size();
	// and now we have to foun player who is next after bank, and is not allin is not fold, and his roundmoney should be
	// greater then bank top, unless it's his first step
	for (int i2=0;i2<mapSize;i2++){
		quint16 nextSitChair = PokerGameHelper::getNextSit(auctionPlayers,chairId);
		qDebug() << "AuctionAction::getCurrentBetPlayer# Next chair after chair " << chairId << " is " << nextSitChair << endl;
		if (auctionPlayers.value(nextSitChair)->getGamePlayer()->getRoundMoney() == auctionBank
				|| auctionPlayers.value(nextSitChair)->getAllIn()
				|| auctionPlayers.value(nextSitChair)->isFold()){
			if (!(auctionPlayers.value(nextSitChair)->getWasInAuction())) { // even if his roundmoney is same like bank top, its his turn
				resultPlayer = auctionPlayers.value(nextSitChair);
				return resultPlayer;
			}

			chairId = nextSitChair;
			continue;
		}
		else {
			qDebug() << "AuctionAction::getCurrentBetPlayer# betPlayerFound " << chairId<< "his round money = "<< auctionPlayers.value(PokerGameHelper::getNextSit(auctionPlayers,chairId))->getGamePlayer()->getRoundMoney() << " and  bank is " << auctionBank <<endl;
			resultPlayer = auctionPlayers.value(PokerGameHelper::getNextSit(auctionPlayers,chairId));
			break;
		}
	} // if we didnt find player who is current bet, then bet is over and we return NULL
	return resultPlayer;
}

quint16 AuctionAction::getDilerChair(QMap<quint16, GamePlayerModel*> players){
	QMapIterator<quint16, GamePlayerModel*> i(players);
	while (i.hasNext()) {
	   i.next();
	   if (i.value()->getDiler()) {
		   return i.key();
	   }
	}
	qDebug() << "AuctionAction::getDilerChair# WARNING diler missing !!" << endl;
	return 0;
}

quint16 AuctionAction::getCurrentAuctionTop(QMap<quint16, AuctionPlayerModel*> players){
	quint16 bank = 0;
	QMapIterator<quint16, AuctionPlayerModel*> i(players);
	while (i.hasNext()) {
	   i.next();
	   qDebug() << "AuctionAction::getCurrentAuctionTop# chair " << i.key() << " name " << *(i.value()->getGamePlayer()->getPlayerModel()->getName()) << " round "<<i.value()->getGamePlayer()->getRoundMoney() << " money = " << bank;
	   if (i.value()->getGamePlayer()->getRoundMoney() > bank) {
		   bank = i.value()->getGamePlayer()->getRoundMoney();
	   }
	}
	qDebug() << "AuctionAction::getCurrentAuctionTop# auction top is " << bank << endl;
	return bank;
}
