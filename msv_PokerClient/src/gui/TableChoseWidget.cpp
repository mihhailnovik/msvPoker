#include "src/gui/TableChoseWidget.h"
#include "src/gui/WidgetHelper.h"
#include "src/model/game_engine/PokerRoomModel.h"
#include "src/gui/GameMainWidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QBrush>
#include <QPixmap>
#include <QLabel>
#include <QPoint>
#include <QList>

TableChoseWidget::TableChoseWidget(MsvEnvironment* environment)
     : QWidget()
{
	this->environment = environment;
	serverInfoService = environment->getServiceHolder()->getServerInfoService();
	connect(serverInfoService,SIGNAL(serverInfoReceived(ServerInfoModel*)),this,SLOT(serverInfoReceived(ServerInfoModel*)));
	connect(serverInfoService,SIGNAL(pokerRoomJoined(PokerRoomModel*)),this,SLOT(pokerRoomJoined(PokerRoomModel*)));
	serverInfoService->getServerInfo();
	init();
}

void TableChoseWidget::init(){
	QPalette pall;
	pall.setBrush(this->backgroundRole(),QBrush(QPixmap(":/img/tableChose.jpg")));
	this->setPalette(pall);
	setFixedSize(625, 500);
	setMinimumSize(625, 500);
	setMaximumSize(625, 500);
	nameLabel = WidgetHelper::getLabel(this,QString("Name   : ")+ *(environment->getAuthenticatedPlayer()->getName()),Qt::white);
	nameLabel->move(350,26);
	QString money;
	money.setNum(environment->getAuthenticatedPlayer()->getMoney());
	moneyLabel = WidgetHelper::getLabel(this,QString("Money : ")+ money + QString(" $"),Qt::white);
	moneyLabel->move(350,56);
}

void TableChoseWidget::serverInfoReceived(ServerInfoModel* serverInfoModel) {
	qDebug() << "TableChoseWidget::serverInfoReceived# building table info..." << endl;
	this->serverInfoModel = serverInfoModel;
	QList<PokerRoomModel*>* roomList = serverInfoModel->getRoomList();
	QString roomSize;
	roomSize.setNum(roomList->size());
	qDebug() << "TableChoseWidget::serverInfoReceived# we have " <<roomSize << " rooms"<< endl;

	TableListWidget* tableList = new TableListWidget(this,serverInfoModel->getRoomList());
	QList<TableRowWidget*>* rows = tableList->getRowList();

	for (int i=0;i<rows->size();i++){
		connect(rows->at(i)->getButton(),SIGNAL(clicked(int)),this,SLOT(joinTable(int)));
	}
	tableList->move(0,205);
	tableList->setVisible(true);
}

void TableChoseWidget::joinTable(int id) {
	qDebug()<< "TableChoseWidget::joinTable Join table action performed for button " << id << endl;
	serverInfoService->joinTable(id);
}

void TableChoseWidget::pokerRoomJoined(PokerRoomModel* room1) {
	qDebug()<< "TableChoseWidget::pokerRoomJoined join to table " << *(room1->getName()) << " succesfull " << endl;
	GameMainWidget* gameWidget = new GameMainWidget(environment,room1);
	gameWidget->show();
    this->hide();
}
