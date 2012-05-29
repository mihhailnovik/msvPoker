#ifndef ABSTRACTPOKERGAME_H
#define ABSTRACTPOKERGAME_H
#include <QObject>
#include <QMap>
#include <QList>
#include <QThread>
#include "src/model/server/PokerPlayerModel.h"
#include "src/model/server/PokerRoomModel.h"

/**
 * @author rdir52_msv team
 * Abstract class represent pokergame logic
 */

class AbstractPokerGame : public QThread {
Q_OBJECT
public:
	AbstractPokerGame();
	~AbstractPokerGame();
	void virtual run() = 0; // runs game
	bool isRunning();
	static void sleep(int msec);
protected:
	quint16 roundCounter;
	PokerRoomModel* room;
	bool running;
};
#endif
