#ifndef AUTHENTICATIONSERVICE_H
#define AUTHENTICATIONSERVICE_H
#include <QString>
#include "src/model/server/PokerPlayerModel.h"
/*
 *	provides authentication
 */
class AuthenticationService {

public:
	AuthenticationService();
	// returns PokerPlayerModel if authentication is successful, otherwise returns null
	PokerPlayerModel* authenticate(QString login, QString password);
};

#endif
