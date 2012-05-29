#include "src/service/LoginService.h"
#include "src/utils/MessageBuilder.h"
#include <QDebug>

LoginService::LoginService(SocketHolder* holder)
{
	this->holder = holder;
}

void LoginService::login(QString login,QString password){
	qDebug() << "LoginService::login# Login with name " << login << " and password " << password << endl;
	holder->sendData(MessageBuilder::buildAuthenticationMessage(login,password));
}

void LoginService::authetication(MsvServerMessage* model){
	if (model->isAuthentication()) {
		if (model->getAuthInfoModel()){
			if (model->getAuthInfoModel()->isAuthenticated()) {
				qDebug() << "LoginService::authetication# LoginService::authetication# Authentication succesfull !" << endl;
				emit loginSuccesful(model->getAuthInfoModel()->getPlayerModel());
				return;
			}
			qDebug() << "LoginService::authetication# LoginService::authetication# Auth failed, incorrect password " << endl;
			emit loginFailed();
			return;
		}
		qDebug() << "LoginService::authetication# Warning !!! why AuthInfoModel is null ?? " << endl;
		emit loginFailed();
		return;
	}
	qDebug() << "LoginService::authetication# Warning !!! it isn't authentication message " << endl;
	emit loginFailed();
}
