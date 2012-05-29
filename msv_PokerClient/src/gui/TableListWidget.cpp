#include "src/gui/TableListWidget.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
 TableListWidget::TableListWidget(QWidget* parent,QList<PokerRoomModel*>* roomList)
     : QWidget(parent)
 {
	 this->roomList = roomList;
	 rowList = new QList<TableRowWidget*>();
	 init();
 }

 void TableListWidget::init(){
	if (roomList == NULL){
		QLabel* label = new QLabel("Can't get data from server",this);
		return;
	}
	QVBoxLayout *layout = new QVBoxLayout;
	for (int i=0;i<roomList->size();i++) {
		TableRowWidget* row = new TableRowWidget(this,roomList->at(i));
		rowList->append(row);
		layout->addWidget(row);
	}
	setFixedSize(624, 288);
	setLayout(layout);
 }

 QList<TableRowWidget*>* TableListWidget::getRowList() {
	 return rowList;
 }
