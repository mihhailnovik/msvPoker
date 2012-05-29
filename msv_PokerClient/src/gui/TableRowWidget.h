#ifndef TABLEROWWIDGET_H
#define TABLEROWWIDGET_H
#include <QWidget>
#include <QLabel>
#include "src/model/game_engine/PokerRoomModel.h"
#include "src/gui/elements/MsvQPushButton.h"
class TableRowWidget : public QWidget
{
	Q_OBJECT
public:
	TableRowWidget(QWidget *parent,PokerRoomModel* room);
	MsvQPushButton* getButton() const;
private:
	QLabel* tableLabel;
	QLabel* roomLabel;
	QLabel* rates;
	QLabel* players;
	QLabel* moneyInGame;
	MsvQPushButton* button;
	PokerRoomModel* room;
	void init();
};
#endif
