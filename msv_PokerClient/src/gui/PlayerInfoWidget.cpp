#include "src/gui/PlayerInfoWidget.h"
#include "src/utils/StringUtil.h"
#include "src/utils/CardSuiteUtil.h"
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <QPaintEvent>

 PlayerInfoWidget::PlayerInfoWidget(QWidget *parent,PokerPlayerModel* player,int chairId)
     : QWidget(parent)
 {
	 this->player = player;
	 this->chairId = chairId;
	 joinButton = new MsvQPushButton("",chairId,this);
	 joinButton->setStyleSheet("background-image:url(':/img/joinButton.jpg')");
	 joinButton->setFixedSize(137,50);

	 nameLabel = new QLabel(this);
	 moneyLabel = new QLabel(this);
	 roundMoneyLabel = new QLabel(this);
	 actionLabel = new QLabel(this);
	 nameLabel->move(70,40);
	 moneyLabel->move(70,70);
	 roundMoneyLabel->move(10,13);
	 actionLabel->move(10,90);
	 joinButton->hide();
	 init();
 }

 PlayerInfoWidget::~PlayerInfoWidget(){

 }

 PlayerInfoWidget::PlayerInfoWidget(const PlayerInfoWidget &){

 }

void  PlayerInfoWidget::setPlayer(PokerPlayerModel* model){
	player = model;
	init();
}

PokerPlayerModel*  PlayerInfoWidget::getPokerPlayer() const{
	return player;
}

void PlayerInfoWidget::init(){
	setFixedSize(200, 310);
	dataUpdated();
}

void PlayerInfoWidget::paintEvent(QPaintEvent *event)
{
	if (player != NULL) {
		QPainter painter(this);
		painter.drawPixmap(5,37,QPixmap(":/img/avatar/avat_"+player->getAvatarPic()+".png"));
		painter.drawPixmap(62,31,QPixmap(":/img/playerField.jpg"));

		if (!(player->getCardList().isEmpty())) {
			qDebug() << "PlayerInfoWidget::paintEvent# paint images" << endl;
			if (chairId == 0) {
				painter.drawPixmap(0,110,QPixmap(":/img/cards/"+CardSuiteUtil::toFileName(player->getCardList()[0])));
				painter.drawPixmap(30,110,QPixmap(":/img/cards/"+CardSuiteUtil::toFileName(player->getCardList()[1])));
			} else if (chairId == 1){
				painter.drawPixmap(110,110,QPixmap(":/img/cards/"+CardSuiteUtil::toFileName(player->getCardList()[0])));
				painter.drawPixmap(140,110,QPixmap(":/img/cards/"+CardSuiteUtil::toFileName(player->getCardList()[1])));
			}
			else {
				painter.drawPixmap(70,0,QPixmap(":/img/cards/"+CardSuiteUtil::toFileName(player->getCardList()[0])));
				painter.drawPixmap(100,0,QPixmap(":/img/cards/"+CardSuiteUtil::toFileName(player->getCardList()[1])));
			}
		}
	}
}

// XXX bullshit, this is realy stupid, but FU qt
void PlayerInfoWidget::dataUpdated(){
	if (player) {
		nameLabel->setText("<font size=5 color='white'>"+*(player->getName())+"</font>");
		moneyLabel->setText("<font size=5 color='white'>"+StringUtil::valueOf(player->getMoney())+"$</font>");
		roundMoneyLabel->setText("<font size=5 color='red'>"+StringUtil::wrapWord(5,StringUtil::valueOf(player->getRoundMoney()))+"$</font>");
		actionLabel->setText("<font size=5 color='white'>"+player->getAction()+"</font>");

		roundMoneyLabel->setVisible(true);
		nameLabel->setVisible(true);
		moneyLabel->setVisible(true);
		actionLabel->setVisible(true);

		joinButton->hide();
		paintEvent(NULL);
	} else {
		joinButton->setVisible(true);
		roundMoneyLabel->hide();
		nameLabel->hide();
		moneyLabel->hide();
		actionLabel->hide();
	}
	update();
}

MsvQPushButton* PlayerInfoWidget::getJoinButton() const {
	return joinButton;
}

int PlayerInfoWidget::getChairId() const{
	return chairId;
}
void PlayerInfoWidget::setChairId(int chairId){
	this->chairId = chairId;
}
