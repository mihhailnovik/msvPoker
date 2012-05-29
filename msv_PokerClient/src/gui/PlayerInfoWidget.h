#ifndef PLAYERINFOWIDGET_H
#define PLAYERINFOWIDGET_H
#include <QWidget>
#include <QLabel>
#include "src/model/PokerPlayerModel.h"
#include "src/gui/elements/MsvQPushButton.h"
/**
 * Widget for displayng player info (name, money, cards, etc..
 */
class PlayerInfoWidget : public QWidget
{
	Q_OBJECT
public:
	PlayerInfoWidget(QWidget *parent,PokerPlayerModel* player,int chairId);
	~PlayerInfoWidget();
    PlayerInfoWidget(const PlayerInfoWidget &);
	void setPlayer(PokerPlayerModel* model);
	PokerPlayerModel* getPokerPlayer() const;
	void paintEvent(QPaintEvent *event);
	MsvQPushButton* getJoinButton() const;
	int getChairId() const;
	void setChairId(int chairId);
private:
	void init();
	PokerPlayerModel* player;
	QLabel* nameLabel;
	QLabel* moneyLabel;
	QLabel* roundMoneyLabel;
	QLabel* actionLabel;
	MsvQPushButton* joinButton;
	int chairId;
private slots:
	void dataUpdated();
};
#endif
