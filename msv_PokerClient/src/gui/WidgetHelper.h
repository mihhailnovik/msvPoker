#ifndef WIDGETHELPER_H
#define WIDGETHELPER_H
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QColor>
#include <QFont>
class WidgetHelper
{
public:
	WidgetHelper();
	static QFont getLabelFont();
	static QLabel* getLabel(QWidget* parent,QString text,QColor color);
};
#endif
