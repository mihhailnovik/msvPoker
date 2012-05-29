#include "src/model/server/MsvClientMessage.h"
#include "src/utils/MessageDefines.h"
#include <QDebug>
MsvClientMessage::MsvClientMessage(QObject *parent) : QObject(parent) {

}

MsvClientMessage::~MsvClientMessage(){
	 delete type;
	 delete authInfo;
	 delete joinTableModel;
	 delete actionModel;
}

QString* MsvClientMessage::getType() const{
	return type;
}

void MsvClientMessage::setType(QString* type) {
	this->type = type;
}

bool MsvClientMessage::isInfoMessage() const
{
	return type != 0 ? QString(GETINFO).compare(*type) == 0 : false;
}

bool MsvClientMessage::isJoinChair() const {
	return type != 0 ? QString("join_chair").compare(*type) == 0 : false;
}

bool MsvClientMessage::isJoinTable() const
{
	return type != 0 ? QString("join_table").compare(*type) == 0 : false;
}

bool MsvClientMessage::isAuthentication() const
{
	return type != 0 ? QString(AUTHENTICATION).compare(*type) == 0 : false;
}

bool MsvClientMessage::isGameAction() const
{
	return type != 0 ? QString("game_action").compare(*type) == 0 : false;
}

bool MsvClientMessage::isBet() const {
	return type != 0 ? QString("bet").compare(*type) == 0 : false;
}

void MsvClientMessage::setJoinTableModel(JoinTableInfoModel *model)
{
	this->joinTableModel = model;
}

JoinTableInfoModel *MsvClientMessage::getJoinTableModel() const
{
	return joinTableModel;
}

AuthInfoModel* MsvClientMessage::getAuthInfoModel() const {
	return authInfo;
}
void MsvClientMessage::setAuthInfoModel(AuthInfoModel* model){
	this->authInfo=model;
}

GameActionModel* MsvClientMessage::getGameActionModel() const {
	return actionModel;
}

void MsvClientMessage::setGameActionModel(GameActionModel* model){
	this->actionModel = model;
}

JoinChairInfoModel* MsvClientMessage::getJoinChairInfoModel() const {
	return joinChairModel;
}
void MsvClientMessage::setJoinChairInfoModel(JoinChairInfoModel* model) {
	this->joinChairModel = model;
}

int MsvClientMessage::getBet() const {
	return bet;
}

void MsvClientMessage::setBet(int bet){
	this->bet = bet;
}
