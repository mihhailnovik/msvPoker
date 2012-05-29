#include "src/service/AuthenticationService.h"

AuthenticationService::AuthenticationService() {

}

PokerPlayerModel* AuthenticationService::authenticate(QString login,QString password) {
	qDebug() << "AuthenticationService::authenticate# " << " login = " << login << " password = " << password <<endl;
	if (QString("mi1").compare(login) == 0 && QString("123456").compare(password) == 0) {
		PokerPlayerModel* player = new PokerPlayerModel();
		player->setName(new QString("mi1"));
		player->setMoney(8000);
		return player; // TODO
	}
	if (QString("s1").compare(login) == 0 && QString("1").compare(password) == 0) {
		PokerPlayerModel* player = new PokerPlayerModel();
		player->setName(new QString("s1aY"));
		player->setMoney(5000);
		return player; // TODO
	}

	if (QString("v1").compare(login) == 0 && QString("1").compare(password) == 0) {
		PokerPlayerModel* player = new PokerPlayerModel();
		player->setName(new QString("Viktor"));
		player->setMoney(7000);
		return player; // TODO
	}

	if (QString("r1").compare(login) == 0 && QString("1").compare(password) == 0) {
		PokerPlayerModel* player = new PokerPlayerModel();
		player->setName(new QString("roma"));
		player->setMoney(2000);
		return player; // TODO
	}

	return NULL;

}
