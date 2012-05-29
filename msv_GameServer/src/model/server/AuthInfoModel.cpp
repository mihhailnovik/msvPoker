#include "src/model/server/AuthInfoModel.h"

AuthInfoModel::AuthInfoModel(QObject *parent) : QObject(parent) {

}

AuthInfoModel::AuthInfoModel(QString* login, QString* pass){
	this->login = login;
	this->pass = pass;
}

AuthInfoModel::~AuthInfoModel() {
	delete login;
	delete pass;
}

QString* AuthInfoModel::getLogin() const
{
    return login;
}

QString* AuthInfoModel::getPass() const
{
    return pass;
}

void AuthInfoModel::setLogin(QString *login)
{
    this->login = login;
}

void AuthInfoModel::setPass(QString *pass)
{
    this->pass = pass;
}
