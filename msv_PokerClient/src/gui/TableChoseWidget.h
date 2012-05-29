#ifndef TABLECHOSEWIDGET_H
#define TABLECHOSEWIDGET_H
#include <QWidget>
#include <QLabel>
#include "src/model/MsvEnvironment.h"
#include "src/service/ServerInfoService.h"
#include "src/model/ServerInfoModel.h"
#include "src/gui/TableListWidget.h"
#include "src/gui/elements/MsvQPushButton.h"

class TableChoseWidget : public QWidget
{
	Q_OBJECT
public:
	TableChoseWidget(MsvEnvironment* environment = 0);
private:
	MsvEnvironment* environment;
	ServerInfoService* serverInfoService;
	ServerInfoModel* serverInfoModel;
	// gui
	QLabel* nameLabel;
	QLabel* moneyLabel;

	TableListWidget* tableListWidget;
	void init(); // when this method called tableListwidget should be initialized

	MsvQPushButton* button1;
private slots:
	void serverInfoReceived(ServerInfoModel* serverInfo);
	void joinTable(int id);
	void pokerRoomJoined(PokerRoomModel* room1);
};
#endif
