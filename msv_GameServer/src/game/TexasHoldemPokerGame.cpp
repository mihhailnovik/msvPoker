#include "src/game/TexasHoldemPokerGame.h"
#include "src/utils/MessageBuilder.h"
#include "src/utils/MessageSenderUtil.h"
#include "src/utils/PokerGameHelper.h"
#include "src/model/game_engine/GamePlayerModel.h"
#include "src/model/game_engine/SimpleFiftyTwoCardsDeckModel.h"
#include "src/model/game_engine/GameBankModel.h"
#include "src/game/AuctionAction.h"
#include <QMap>
#include <QMapIterator>
#include <QList>
#include <QWaitCondition>
#include <QMutex>

TexasHoldemPokerGame::TexasHoldemPokerGame(PokerRoomModel* room) : AbstractPokerGame() {
	this->room = room;
	running = false;
	dilerNr = 0;
}

TexasHoldemPokerGame::~TexasHoldemPokerGame(){

}

void TexasHoldemPokerGame::run(){
	pause(5000);
	running = true;
	qDebug() << "TexasHoldemPokerGame::startGame# Round " << roundCounter << " started" << endl;
	roundCounter++;
	/************************************************************************
	 * 						Init round data									*
	 ***********************************************************************/
	QMap<quint16, GamePlayerModel*>* gamePlayersMap = new QMap<quint16, GamePlayerModel*>();
	QMapIterator<quint16, PokerPlayerModel*> i(*(room->getChairPlayerMap()));
	qDebug() << "TexasHoldemPokerGame::run# making gameplayer models " << endl;
	while (i.hasNext()) {
	   i.next();
	   if (i.value() != NULL){
		   qDebug() << "TexasHoldemPokerGame::run# GamplayerAdded [key = ]"<<i.key()<<endl;
		   gamePlayersMap->insert(i.key(),new GamePlayerModel(i.value()));
	   }
	}
	SimpleFiftyTwoCardsDeckModel cardDeck;
	GameBankModel* bank = new GameBankModel();
	QList<CardModel> cardsInTable;
	/****************************************************************************
	 * 									Preflop                  				*
	 ***************************************************************************/
	qDebug() << "TexasHoldemPokerGame::run# Preflop in pokerroom " << *(room->getName()) << endl;
	dilerNr = PokerGameHelper::getNextSit(*(gamePlayersMap),dilerNr);
	gamePlayersMap->value(dilerNr)->setDiler(true);
	qDebug() << "TexasHoldemPokerGame::run# diler is " << dilerNr << endl;

	quint16 smallBlindPlayer = PokerGameHelper::getNextSit(*(gamePlayersMap),dilerNr);
	qDebug() << "TexasHoldemPokerGame::run# Small blind player chair =  " << smallBlindPlayer << "(small blind = "<<room->getBetModel()->getSmallBlind()<<")"<<endl;
	quint16 bigBlindPlayer = PokerGameHelper::getNextSit(*(gamePlayersMap),smallBlindPlayer);
	qDebug() << "TexasHoldemPokerGame::run# Big blind player chair =  " << bigBlindPlayer << "(big blind = "<<room->getBetModel()->getBigBlind()<<")"<<endl;
	// Small blind
	if (gamePlayersMap->value(smallBlindPlayer)->getPlayerModel()->takeMoney(room->getBetModel()->getSmallBlind())){
		gamePlayersMap->value(smallBlindPlayer)->addRoundMoney(room->getBetModel()->getSmallBlind());
		bank->add(room->getBetModel()->getSmallBlind());
	} else {qDebug() << "TexasHoldemPokerGame::run# WARNING!  player do not have enough money " << *(gamePlayersMap->value(smallBlindPlayer)->getPlayerModel()->getName())<< endl;}
	// big blind
	if (gamePlayersMap->value(bigBlindPlayer)->getPlayerModel()->takeMoney(room->getBetModel()->getBigBlind())){
		gamePlayersMap->value(bigBlindPlayer)->addRoundMoney(room->getBetModel()->getBigBlind());
		bank->add(room->getBetModel()->getBigBlind());
	} else {qDebug() << "TexasHoldemPokerGame::run# WARNING!  player do not have enough money " << *(gamePlayersMap->value(bigBlindPlayer)->getPlayerModel()->getName())<< endl;}
	QMapIterator<quint16, GamePlayerModel*> i2(*(gamePlayersMap));
	// Card distribution
	while (i2.hasNext()) {
	   i2.next();
	   i2.value()->addCard(cardDeck.getRandomCard());
	   i2.value()->addCard(cardDeck.getRandomCard());
	   qDebug() << "TexasHoldemPokerGame::run# card Destination "
			   << *(i2.value()->getPlayerModel()->getName())
			   << " -> " << i2.value()->getCards()[0].toString() << " "
			   << i2.value()->getCards()[1].toString() << endl;
	}
	sendMessage(*(gamePlayersMap),bank,cardsInTable);
	/****************************************************************************
	 * 									Auction                  				*
	 ***************************************************************************/
	doAuction(gamePlayersMap,bank,cardsInTable);
	if (getPlayersWithCardCount(gamePlayersMap) == 1) {
		GamePlayerModel* winner = getWinner(gamePlayersMap);
		QString moneyWon;
		moneyWon.setNum(bank->getMoney());
		winner->setLastActionName("I won "+moneyWon+"$");
		winner->foldCards();
		qDebug() << "TexasHoldemPokerGame::run# i said we got a winner !!!"<< moneyWon<< "$ " << *(winner->getPlayerModel()->getName());
		winner->addMoney(bank->getMoney());
		sendMessage(*(gamePlayersMap),bank,cardsInTable);
		pause(5000);
		running = false;
		emit gameEnded();
		return;
	}
	/****************************************************************************
	 * 									Flop                  					*
	 ***************************************************************************/
	cardsInTable.append(cardDeck.getRandomCard());
	cardsInTable.append(cardDeck.getRandomCard());
	cardsInTable.append(cardDeck.getRandomCard());
	sendMessage(*(gamePlayersMap),bank,cardsInTable);
	doAuction(gamePlayersMap,bank,cardsInTable);
	if (getPlayersWithCardCount(gamePlayersMap) == 1) {
		GamePlayerModel* winner = getWinner(gamePlayersMap);
		QString moneyWon;
		moneyWon.setNum(bank->getMoney());
		winner->setLastActionName("I won "+moneyWon+"$");
		winner->foldCards();
		qDebug() << "TexasHoldemPokerGame::run# i said we got a winner !!!"<< moneyWon<< "$ " << *(winner->getPlayerModel()->getName());
		winner->addMoney(bank->getMoney());
		sendMessage(*(gamePlayersMap),bank,cardsInTable);
		pause(5000);
		running = false;
		emit gameEnded();
		return;
	}
	/****************************************************************************
	 * 									Turn                  					*
	 ***************************************************************************/
	cardsInTable.append(cardDeck.getRandomCard());
	sendMessage(*(gamePlayersMap),bank,cardsInTable);
	doAuction(gamePlayersMap,bank,cardsInTable);
	if (getPlayersWithCardCount(gamePlayersMap) == 1) {
		GamePlayerModel* winner = getWinner(gamePlayersMap);
		QString moneyWon;
		moneyWon.setNum(bank->getMoney());
		winner->setLastActionName("I won "+moneyWon+"$");
		winner->foldCards();
		qDebug() << "TexasHoldemPokerGame::run# i said we got a winner !!!"<< moneyWon<< "$ " << *(winner->getPlayerModel()->getName());
		winner->addMoney(bank->getMoney());
		sendMessage(*(gamePlayersMap),bank,cardsInTable);
		pause(5000);
		running = false;
		emit gameEnded();
		return;
	}
	/****************************************************************************
	 * 									River                  					*
	 ***************************************************************************/
	cardsInTable.append(cardDeck.getRandomCard());
	sendMessage(*(gamePlayersMap),bank,cardsInTable);
	doAuction(gamePlayersMap,bank,cardsInTable);
	if (getPlayersWithCardCount(gamePlayersMap) == 1) {
		GamePlayerModel* winner = getWinner(gamePlayersMap);
		QString moneyWon;
		moneyWon.setNum(bank->getMoney());
		winner->setLastActionName("I won "+moneyWon+"$");
		winner->foldCards();
		qDebug() << "TexasHoldemPokerGame::run# i said we got a winner !!!"<< moneyWon<< "$ " << *(winner->getPlayerModel()->getName());
		winner->addMoney(bank->getMoney());
		sendMessage(*(gamePlayersMap),bank,cardsInTable);
		pause(5000);
		running = false;
		emit gameEnded();
		return;
	}
	/****************************************************************************
	 * 									detect winner                  			*
	 ***************************************************************************/
	qDebug() << " game finished ";
	detectWinner(gamePlayersMap,cardsInTable);
	sendMessage(*(gamePlayersMap),bank,cardsInTable);
	pause(5000);
	if (getPlayersWithCardCount(gamePlayersMap) == 1) {
			GamePlayerModel* winner = getWinner(gamePlayersMap);
			QString moneyWon;
			moneyWon.setNum(bank->getMoney());
			winner->setLastActionName("I won "+moneyWon+"$");
			winner->foldCards();
			qDebug() << "TexasHoldemPokerGame::run# i said we got a winner !!!"<< moneyWon<< "$ " << *(winner->getPlayerModel()->getName());
			winner->addMoney(bank->getMoney());
			sendMessage(*(gamePlayersMap),bank,cardsInTable);
			pause(5000);
			running = false;
			emit gameEnded();
			return;
	}
	running = false;
	emit gameEnded();
}

void TexasHoldemPokerGame::detectWinner(QMap<quint16, GamePlayerModel*>* gamePlayersMap,QList<CardModel> cardsInTable){
	quint16 winnerChair;
	int winnerPoints = 0;
	QMapIterator<quint16, GamePlayerModel*> i(*(gamePlayersMap));
	while (i.hasNext()) {
		   i.next();
		   QList<CardModel> list;
		   list.append(i.value()->getCards()[0]);
		   list.append(i.value()->getCards()[1]);
		   for (int i2=0;i2<cardsInTable.size();i2++){
			   list.append(cardsInTable.at(i2));
		   }

		   int currentPoints = PokerGameHelper::getCardRank(list);
		   if (currentPoints > winnerPoints){
			   winnerPoints = currentPoints;
			   winnerChair = i.key();
			   qDebug() << "TexasHoldemPokerGame::detectWinner Current winner is " << winnerChair;
		   }
	}

	QMapIterator<quint16, GamePlayerModel*> i3(*(gamePlayersMap));
	while (i3.hasNext()) {
		i3.next();
	   if (i3.key() != winnerChair){
		   i3.value()->foldCards();
		   qDebug() << "TexasHoldemPokerGame::detectWinner fold " << *(i3.value()->getPlayerModel()->getName());
	   }
	}
}

GamePlayerModel* TexasHoldemPokerGame::getWinner(QMap<quint16, GamePlayerModel*>* gamePlayersMap){
	QMapIterator<quint16, GamePlayerModel*> i(*(gamePlayersMap));
	while (i.hasNext()) {
		i.next();
		if (i.value()->getCards().size() != 0){
			return i.value();
		}
	}
	qDebug() << "TexasHoldemPokerGame::getWinner# Impossible situation ";
	return NULL;
}

int TexasHoldemPokerGame::getPlayersWithCardCount(QMap<quint16, GamePlayerModel*>* gamePlayersMap){
	int result = 0;
	QMapIterator<quint16, GamePlayerModel*> i(*(gamePlayersMap));
	while (i.hasNext()) {
		i.next();
		if (i.value()->getCards().size() != 0){
			result++;
		}
	}
	return result;
}

void TexasHoldemPokerGame::sendMessage(QMap<quint16, GamePlayerModel*> gamePlayers,GameBankModel* bank,QList<CardModel> list) {
	QList<GamePlayerModel*> players = gamePlayers.values();
	for (int i=0;i<players.size();i++){
		emitSendMessage(MessageBuilder::buildGameMessage(gamePlayers,players.at(i)->getPlayerModel(),list,bank->getMoney(),room->getMaxPlayers()),players.at(i)->getPlayerModel());
	}
}

void TexasHoldemPokerGame::doAuction(QMap<quint16, GamePlayerModel*>* players,GameBankModel* bank,QList<CardModel> cardsInTable) {
	AuctionAction auction(players,this,bank,cardsInTable);
	auction.doAuction();
}

void TexasHoldemPokerGame::emitSendMessage(QString* message, PokerPlayerModel* player) {
	emit sendMessage(message,player);
}

void TexasHoldemPokerGame::pause(quint16 milisec) {
	QMutex* mutex = new QMutex();
	QWaitCondition cond;
	mutex->lock();
	cond.wait(mutex,milisec);
	mutex->unlock();
	delete mutex;
}
