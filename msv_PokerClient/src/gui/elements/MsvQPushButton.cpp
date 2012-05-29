#include "src/gui/elements/MsvQPushButton.h"

MsvQPushButton::MsvQPushButton(const QString & text,int id, QWidget * parent)
     : QPushButton(text,parent)
{
	this->id = id;
	connect(this,SIGNAL(clicked(bool)),this,SLOT(clicked(bool)));
}

int MsvQPushButton::getId() const {
	return id;
}

void MsvQPushButton::setId(int id) {
	this->id = id;
}

void MsvQPushButton::clicked(bool) {
	emit clicked(id);
}
