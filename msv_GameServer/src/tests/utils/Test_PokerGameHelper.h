#ifndef TEST_POKERGAMEHELPER_H
#define TEST_POKERGAMEHELPER_H
#include <QtTest>
#include <QObject>
/*
 * @author rdir52_msv team
 */
class Test_PokerGameHelper: public QObject {
Q_OBJECT
private slots:
	void test_getNextSit();
	void test_getCardRank();
};
#endif
