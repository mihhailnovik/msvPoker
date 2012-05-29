#ifndef TEST_PLAYERINFOWIDGET_H
#define TEST_PLAYERINFOWIDGET_H
#include <QtTest>
#include <QObject>

class Test_PlayerInfoWidget: public QObject {
Q_OBJECT

public:
	Test_PlayerInfoWidget();
	~Test_PlayerInfoWidget();
private slots:
	void test_design(); // this test do not actualy test anything
};
#endif
