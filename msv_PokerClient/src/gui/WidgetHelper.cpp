#include "src/gui/WidgetHelper.h"
#include <QPalette>
WidgetHelper::WidgetHelper()
 {
 }

QFont WidgetHelper::getLabelFont() {
	 return QFont("Times", 18, QFont::Bold);
}


QLabel* WidgetHelper::getLabel(QWidget* parent,QString text,QColor color){
	QLabel* label = new QLabel(text,parent);
	label->setFont(WidgetHelper::getLabelFont());
	QPalette palette;
	palette.setColor(label->foregroundRole(),color);
	label->setPalette(palette);
	return label;
}
