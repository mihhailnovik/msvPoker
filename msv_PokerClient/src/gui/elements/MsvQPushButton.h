#ifndef MSVQPUSHBUTTON_H
#define MSVQPUSHBUTTON_H
#include <QPushButton>
/*
 * Same as QpushButton plus have id attribute
 */
class MsvQPushButton : public QPushButton
{
	Q_OBJECT
public:
	MsvQPushButton(const QString & text, int id,QWidget * parent = 0);
	int getId() const;
	void setId(int id);
private:
	int id;
signals:
	void clicked (int id);
private slots:
	void clicked(bool);
};
#endif
