#ifndef TEST_CONFIGREADERUTIL_H
#define TEST_CONFIGREADERUTIL_H
#include <QtTest>
#include <QObject>

class Test_ConfigReaderUtil: public QObject {
Q_OBJECT
private slots:
	void test_getHostModel();
};
#endif
