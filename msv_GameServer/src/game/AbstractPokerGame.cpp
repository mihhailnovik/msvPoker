#include "src/game/AbstractPokerGame.h"

AbstractPokerGame::AbstractPokerGame() {
	roundCounter = 0;
	running = false;
}
AbstractPokerGame::~AbstractPokerGame(){

}

bool AbstractPokerGame::isRunning() {
	return running;
}

void AbstractPokerGame::sleep(int msec) {
	QThread::sleep(msec);
}
