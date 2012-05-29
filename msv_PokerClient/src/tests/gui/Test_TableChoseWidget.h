#ifndef TEST_TABLECHOSEWIDGET_H
#define TEST_TABLECHOSEWIDGET_H
#include <QtTest>
#include <QObject>
#include "src/gui/TableChoseWidget.h"
#include "src/model/MsvEnvironment.h"
#include "src/model/ServerInfoModel.h"

class Test_TableChoseWidget: public QObject {
Q_OBJECT
public:
    void initTestCase();
private slots:
	void test_serverInfoReceived(); // this test do not actualy test anything
private:
	MsvEnvironment* env;
	ServerInfoModel* serverInfo;
};
#endif
