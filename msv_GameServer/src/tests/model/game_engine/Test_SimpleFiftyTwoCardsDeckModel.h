#ifndef TEST_SIMPLEFIFTYTWOCARDSDECKMODEL_H
#define TEST_SIMPLEFIFTYTWOCARDSDECKMODEL_H
#include <QtTest>
#include <QObject>

class Test_SimpleFiftyTwoCardsDeckModel: public QObject {
Q_OBJECT
	private slots:
	void test_getRandomCards(); // test for unique
	void test_getRandomCard();
};
#endif
