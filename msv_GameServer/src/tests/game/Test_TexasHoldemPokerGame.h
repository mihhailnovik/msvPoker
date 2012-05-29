#ifndef TEST_TEXASHOLDEMPOKERGAME_H
#define TEST_TEXASHOLDEMPOKERGAME_H
#include <QtTest>
#include <QObject>

class Test_TexasHoldemPokerGame: public QObject {
Q_OBJECT
public:
    void initTestCase();
private slots:
	void test_startGame();
};
#endif
