#include "src/model/MsvServerMessage.h"

MsvServerMessage::MsvServerMessage(QObject *parent)
    : QObject(parent)
{

}

bool MsvServerMessage::isAuthentication() const {
	return QString("authentication_succesfull").compare(*type) == 0;
}

AuthInfoModel* MsvServerMessage::getAuthInfoModel() const {
	return authModel;
}

void MsvServerMessage::setAuthInfoModel(AuthInfoModel* model){
	this->authModel = model;
}

void MsvServerMessage::setType(QString* type){
	this->type = type;
}

QString* MsvServerMessage::getType() const{
	return type;
}

ServerInfoModel* MsvServerMessage::getServerInfoModel() const {
	return serverInfoModel;
}

bool MsvServerMessage::isServerInfo() const {
	return QString("server_info").compare(*type) == 0;
}

bool MsvServerMessage::isJoinTable() const {
	return QString("join_table").compare(*type) == 0;
}

bool MsvServerMessage::isPlayerJoinChair() const {
	return QString("player_joined_chair").compare(*type) == 0;
}

bool MsvServerMessage::isGameAction() const {
	return QString("game_action").compare(*type) == 0;
}

bool MsvServerMessage::isYourTurn() const {
	return QString("your_turn").compare(*type) == 0;
}

bool MsvServerMessage::isAuthFailed() const {
	return QString("auth_failed").compare(*type) == 0;
}

void MsvServerMessage::setServerInfoModel(ServerInfoModel* model) {
	this->serverInfoModel = model;
}

void MsvServerMessage::setJoinTableInfoModel(JoinTableInfoModel* model) {
	this->joinTableInfoModel = model;
}

JoinTableInfoModel* MsvServerMessage::getJoinTableInfoModel() const{
	return joinTableInfoModel;
}

void MsvServerMessage::setPlayerJoinChairModel(PlayerJoinChairModel* model){
	this->joinChairInfo = model;
}

PlayerJoinChairModel* MsvServerMessage::getPlayerJoinChairModel() const{
	return joinChairInfo;
}

void MsvServerMessage::setPokerRoomModel(PokerRoomModel* model) {
	this->room = model;
}

PokerRoomModel* MsvServerMessage::getPokerRoomModel() const{
	return room;
}
