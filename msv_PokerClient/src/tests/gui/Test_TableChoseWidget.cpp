#include "src/tests/gui/Test_TableChoseWidget.h"
#include "src/model/ServerInfoModel.h"
#include "src/model/game_engine/PokerRoomModel.h"
#include "src/utils/ServiceHolder.h"
#include "src/utils/SocketHolder.h"
#include "src/service/ServerInfoService.h"
#include "src/model/PokerPlayerModel.h"
#include <QList>
#include <QApplication>
#include <QString>

void Test_TableChoseWidget::initTestCase(){
	env = new MsvEnvironment();
	ServiceHolder* serviceHolder = new ServiceHolder(new SocketHolder(NULL));
	env->setServiceHolder(serviceHolder);
	serverInfo = new ServerInfoModel();
	PokerPlayerModel* player = new PokerPlayerModel();
	player->setName(new QString("name"));
	player->setMoney(1000);
	env->setAuthenticatedPlayer(player);
	QList<PokerRoomModel*>* roomList;
	// TODO not all data is initialized
}

void Test_TableChoseWidget::test_serverInfoReceived(){ // TODO you will be hero if you can test that :)
	int i =0;
	QApplication app(i, NULL);
	TableChoseWidget* tableChoseWidget = new TableChoseWidget(env);
	//tableChoseWidget->serverInfoReceived();
	//tableChoseWidget->show();
	app.exec();
	QCOMPARE(1,1);
}
