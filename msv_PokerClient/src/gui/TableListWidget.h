#ifndef TABELLISTWIDGET_H
#define TABELLISTWIDGET_H
#include <QWidget>
#include <QList>
#include "src/model/game_engine/PokerRoomModel.h"
#include "src/gui/TableRowWidget.h"
class TableListWidget : public QWidget
{
	Q_OBJECT
public:
	TableListWidget(QWidget* parent,QList<PokerRoomModel*>* roomList);
	QList<TableRowWidget*>* getRowList();
private:
	QList<PokerRoomModel*>* roomList;
	QList<TableRowWidget*>* rowList;
	void init();
};
#endif
