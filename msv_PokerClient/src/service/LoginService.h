#ifndef LOGINSERVICE_H
#define LOGINSERVICE_H
#include <QObject>
#include <QString>
#include "src/model/PokerPlayerModel.h"
#include "src/utils/SocketHolder.h"
#include "src/model/MsvServerMessage.h"

class LoginService : public QObject
{
	Q_OBJECT
public:
	LoginService(SocketHolder* holder);
	void login(QString login,QString password);
	void authetication(MsvServerMessage* model);
signals:
	void loginSuccesful(PokerPlayerModel* authenticatedPlayer);
	void loginFailed();
private:
	SocketHolder* holder;
};
#endif
