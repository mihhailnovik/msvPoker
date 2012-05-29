#ifndef GAMEMAINWIDGET_H
#define GAMEMAINWIDGET_H
#include <QWidget>
#include <QMap>
#include <QPaintEvent>
#include <QPushButton>
#include <QLabel>
#include "src/model/PokerPlayerModel.h"
#include "src/model/MsvEnvironment.h"
#include "src/service/GameService.h"
#include "src/service/ServerInfoService.h"
#include "src/gui/elements/MsvQPushButton.h"
#include "src/gui/PlayerInfoWidget.h"
#include "src/gui/elements/LCDRange.h"

class GameMainWidget : public QWidget
{
	Q_OBJECT
public:
	GameMainWidget(MsvEnvironment* env, PokerRoomModel* room);
private:
	MsvEnvironment* environment;
	PokerRoomModel* room;
	GameService* gameService;
	QMap<quint16,PlayerInfoWidget*>* chairWidgetMap;
	QPushButton* foldButton;
	QPushButton* checkButton;
	QPushButton* callRaiseButton;
	LCDRange* raiseMoneyRange;
	QLabel* systemMessage;
	QLabel* bankMoney;

	void init();
	void paintEvent(QPaintEvent *event);
	PokerPlayerModel* getYourSelf() const;
	int getCurrentRoundMoney();
	void initButtons();

private slots:
	void seat(bool); // when player click "take seat"
	void updateContent(); // when new player connected
	void enableBetButtons();
	void disableBetButtons();

	void slotRaise(bool);
	void slotCheck(bool);
	void slotFold(bool);
};
#endif
