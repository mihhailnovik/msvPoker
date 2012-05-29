#include "src/model/AuthInfoModel.h"

AuthInfoModel::AuthInfoModel(QObject *parent)
    : QObject(parent)
{

}

void AuthInfoModel::setPokerPlayer(PokerPlayerModel* model) {
	this->playerModel = model;
}

PokerPlayerModel* AuthInfoModel::getPlayerModel() const {
	return playerModel;
}

bool AuthInfoModel::isAuthenticated(){
	return auth;
}

void AuthInfoModel::setAuth(bool auth){
	this->auth = auth;
}

QString* AuthInfoModel::getName() const {
	return playerModel->getName();
}
quint16 AuthInfoModel::getMoney() const {
	return playerModel->getMoney();
}
