#include "src/gui/GameMainWidget.h"
#include "src/gui/elements/MsvQPushButton.h"
#include "src/utils/StringUtil.h"
#include "src/utils/CardSuiteUtil.h"
#include <QPalette>
#include <QPixmap>
#include <QPainter>
#include <QMapIterator>
#include <QString>
#include <QMessageBox>
#include <QDebug>

GameMainWidget::GameMainWidget(MsvEnvironment* environment, PokerRoomModel* room)
{
	this->room = room;
	this->environment = environment;
	this->gameService = environment->getServiceHolder()->getGameService();
	systemMessage = new QLabel("<font size=5 color='red'>Welcome to RAGE POKER </font>",this);
	systemMessage->move(225,470);
	chairWidgetMap = new QMap<quint16,PlayerInfoWidget*>();
	gameService->setPokerRoom(room);
	init();
}

void GameMainWidget::init(){
	QPalette pall;
	pall.setBrush(this->backgroundRole(),QBrush(QPixmap(":/img/room.jpg")));
	this->setPalette(pall);
	setFixedSize(625, 575);
	setMinimumSize(625, 575);
	setMaximumSize(625, 575);
	quint16 x = 0;
	quint16 y = 0;
	QMapIterator<quint16,PokerPlayerModel*> i(*(room->getChairMap()));
	while (i.hasNext()) {
	    i.next();
	    PlayerInfoWidget* playerWidget = new PlayerInfoWidget(this,i.value(),i.key());
	    chairWidgetMap->insert(i.key(),playerWidget);
	    switch (i.key()) {
			case 0:x = 30; y=10; break;
			case 1:x = 415; y=10; break;
			case 2:x = 30; y=400; break;
			case 3:x = 415; y=400; break;
	    }
	    playerWidget->move(x,y);
	    if (playerWidget->getJoinButton() != NULL) {
	    	connect(playerWidget->getJoinButton(),SIGNAL(clicked(bool)),this,SLOT(seat(bool)));
	    	qDebug() << "GameMainWidget::drawChairs# Button added chair id = " << i.key() << endl;
	    }
	}
	initButtons();
	connect(gameService,SIGNAL(contentUpdated()),this,SLOT(updateContent()));
	connect(gameService,SIGNAL(disableBetButtons()),this,SLOT(disableBetButtons()));
	connect(gameService,SIGNAL(enableBetButtons()),this,SLOT(enableBetButtons()));
}

void GameMainWidget::seat(bool) {
	MsvQPushButton* button = (MsvQPushButton*)sender();
	QString id;
	id.setNum(button->getId());
	qDebug() << "GameMainWidget::seat# try to seath to id "<< id << endl;
	if (room->isChairFree(button->getId())) {
		gameService->takeSeat(button->getId());
		QMapIterator<quint16,PlayerInfoWidget*> i(*(chairWidgetMap));
		while (i.hasNext()) {
			    i.next();
			    i.value()->getJoinButton()->setEnabled(false);
			    i.value()->getJoinButton()->setVisible(false);
		}
	}
	else {
		QMessageBox::information(this,"You can't seat here","You can't seat here");
	}
}

void GameMainWidget::updateContent() {
	paintEvent(NULL);
	QMapIterator<quint16,PlayerInfoWidget*> i(*(chairWidgetMap));
	while (i.hasNext()) {
	  i.next();
	  i.value()->setPlayer(room->getChairMap()->value(i.key()));
	}
	qDebug() << "GameMainWidget::updateContent() room money = " << room->getMoney();// TODO delte this log
	bankMoney->setText(QString("<font size=5 color='red'> Bank: "+QString::number(room->getMoney()))+"</font>");
	repaint();
}

void GameMainWidget::paintEvent(QPaintEvent *event) {
	  QPainter painter(this);
	  if (room->getCards() != NULL || !(room->getCards()->isEmpty())) {
		  QList<CardModel*>* cards = room->getCards();
		  int x = 180;
		  int y = 200;
		  for (int i =0;i<cards->size();i++){
			  painter.drawPixmap(x,y,QPixmap(":/img/cards/"+CardSuiteUtil::toFileName(*(cards->at(i)))));
			  x += 50;
		  }
	  }
	  painter.end();
	  qDebug() << "GameMainWidget::paintEvent#";
}

void GameMainWidget::enableBetButtons() {
	qDebug() << "GameMainWidget::enableBetButtons# event received" << endl;
	callRaiseButton->setEnabled(true);
	foldButton->setEnabled(true);
	raiseMoneyRange->setEnabled(true);

	int currentRoundMoney = getCurrentRoundMoney();

	if (currentRoundMoney == getYourSelf()->getRoundMoney()){
		checkButton->setEnabled(true);
	}
	raiseMoneyRange->setRange(currentRoundMoney - getYourSelf()->getRoundMoney(),getYourSelf()->getMoney());
	raiseMoneyRange->setValue(currentRoundMoney - getYourSelf()->getRoundMoney());
	systemMessage->setText("<font size=5 color='red'>Your turn !</font>");
}

void GameMainWidget::disableBetButtons() {
	qDebug() << "GameMainWidget::disableBetButtons# event received" << endl;
	callRaiseButton->setEnabled(false);
	foldButton->setEnabled(false);
	checkButton->setEnabled(false);
	raiseMoneyRange->setEnabled(false);
	systemMessage->setText("<font size=5 color='red'>Your move is done !</font>");
}

PokerPlayerModel* GameMainWidget::getYourSelf() const {
	PokerPlayerModel* player = environment->getAuthenticatedPlayer();
	QMapIterator<quint16,PlayerInfoWidget*> i(*(chairWidgetMap));
	while (i.hasNext()) {
	  i.next();
	  if (i.value()->getPokerPlayer() != NULL && StringUtil::isEquals(*(i.value()->getPokerPlayer()->getName()),*(player->getName()))){
		  qDebug() << "GameMainWidget::getYourSelf# your money = " <<i.value()->getPokerPlayer()->getMoney() <<endl;
		  return i.value()->getPokerPlayer();
	  }
	}
	qDebug() << "GameMainWidget::getYourSelf# WARNING game logic error, can't find yourself in table :S" << endl;
	return NULL;
}

int GameMainWidget::getCurrentRoundMoney() {
	int maxMoney = 0;
	QMapIterator<quint16,PlayerInfoWidget*> i(*(chairWidgetMap));
		while (i.hasNext()) {
		  i.next();
		  if (i.value()->getPokerPlayer() != NULL && maxMoney < i.value()->getPokerPlayer()->getRoundMoney()){
			  maxMoney = i.value()->getPokerPlayer()->getRoundMoney();
		  }
		}
	qDebug() << "GameMainWidget::getCurrentRoundMoney# current round money = " << maxMoney << endl;
	return maxMoney;
}

void GameMainWidget::slotRaise(bool){
	disableBetButtons();
	gameService->bet(raiseMoneyRange->value());
	qDebug() << "GameMainWidget::slotRaise " << raiseMoneyRange->value();
}

void GameMainWidget::slotFold(bool){
	disableBetButtons();
	gameService->bet(-1);
	qDebug() << "GameMainWidget::slotFold";
}

void GameMainWidget::slotCheck(bool){
	disableBetButtons();
	gameService->bet(0);
	qDebug() << "GameMainWidget::slotCheck";
}


void GameMainWidget::initButtons(){
		foldButton = new QPushButton("",this);
		checkButton = new QPushButton("", this);
		callRaiseButton = new QPushButton("", this);
		bankMoney = new QLabel("<font size=5 color='red'> Bank: </font> <font size=5 color='green'>______</font>",this);

		foldButton->setFixedSize(137,50);
		checkButton->setFixedSize(137,50);
		callRaiseButton->setFixedSize(137,50);

		raiseMoneyRange = new LCDRange(this);

		raiseMoneyRange->move(460,505);
		callRaiseButton->move(316,513);
		foldButton->move(172,513);
		checkButton->move(27,513);
		bankMoney->move(245,135);

		checkButton->setAutoFillBackground(true);
		callRaiseButton->setAutoFillBackground(true);
		foldButton->setAutoFillBackground(true);

		checkButton->setAutoFillBackground(true);
		callRaiseButton->setAutoFillBackground(true);
		foldButton->setAutoFillBackground(true);

		foldButton->setStyleSheet("background-image:url(':/img/foldButton.jpg')");
		callRaiseButton->setStyleSheet("background-image:url(':/img/callRaiseButton.jpg')");
		checkButton->setStyleSheet("background-image:url(':/img/checkButton.jpg')");


		callRaiseButton->setEnabled(false);
		foldButton->setEnabled(false);
		checkButton->setEnabled(false);
		raiseMoneyRange->setEnabled(false);

		connect(foldButton,SIGNAL(clicked(bool)),this,SLOT(slotFold(bool)));
		connect(callRaiseButton,SIGNAL(clicked(bool)),this,SLOT(slotRaise(bool)));
		connect(checkButton,SIGNAL(clicked(bool)),this,SLOT(slotCheck(bool)));
}
