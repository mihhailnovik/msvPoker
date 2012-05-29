#include "src/gui/TableRowWidget.h"
#include "src/model/game_engine/PokerRoomModel.h"
#include <QDebug>

 TableRowWidget::TableRowWidget(QWidget *parent,PokerRoomModel* room)
     : QWidget(parent)
 {
	 this->room = room;
	 init();
 }

 void TableRowWidget::init(){
	QString id;
	id.setNum(room->getId());
	qDebug() << "TableRowWidget::init# building TableRow id = "<<id << endl;
	tableLabel = new QLabel(id,this);
	tableLabel->move(7,30);
	roomLabel = new QLabel(*(room->getName()),this);
	roomLabel->move(56,30);
	rates = new QLabel("100/200",this);
	rates->move(203,30);
	QString playersCount;
	playersCount.setNum(room->getMaxPlayers() - room->getFreeChairs().size());
	playersCount.append("/");
	QString maxPlayers;
	maxPlayers.setNum(room->getMaxPlayers());
	playersCount.append(maxPlayers);
	players = new QLabel(playersCount,this);
	players->move(333,30);
	moneyInGame = new QLabel("500/2000",this);
	moneyInGame->move(395,30);
	button = new MsvQPushButton("Join table",room->getId(),this);
	button->move(480,26);
 }

 MsvQPushButton* TableRowWidget::getButton() const{
	 return button;
 }
