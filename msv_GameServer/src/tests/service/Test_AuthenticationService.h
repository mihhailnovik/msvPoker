#ifndef TEST_AUTHENTICATIONSERVICE_H
#define TEST_AUTHENTICATIONSERVICE_H
#include <QtTest>
#include <QObject>

class Test_AuthenticationService: public QObject {
Q_OBJECT
	private slots:
	void test_authenticate();
};
#endif
