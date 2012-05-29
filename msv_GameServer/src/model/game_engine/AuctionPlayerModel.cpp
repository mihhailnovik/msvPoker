#include "src/model/game_engine/AuctionPlayerModel.h"

AuctionPlayerModel::AuctionPlayerModel(quint16 chairId,GamePlayerModel* player) {
	this->player = player;
	allIn = false;
	fold = false;
	wasInAuction = false;
	this->chairId = chairId;
}

AuctionPlayerModel::~AuctionPlayerModel(){

}

GamePlayerModel* AuctionPlayerModel::getGamePlayer() const{
	return player;
}

void AuctionPlayerModel::setGamePlayer(GamePlayerModel* player){
	this->player = player;
}

bool AuctionPlayerModel::getAllIn() const{
	return allIn;
}

void AuctionPlayerModel::setAllIn(bool allIn){
	this->allIn = allIn;
}

quint16 AuctionPlayerModel::getChairId() const {
	return chairId;
}
void AuctionPlayerModel::setChairId(quint16 chairId){
	this->chairId = chairId;
}

bool AuctionPlayerModel::isFold() const {
	return fold;
}

void AuctionPlayerModel::setFold(bool fold) {
	this->fold = fold;
}

void AuctionPlayerModel::setWasInAutction(bool wasInAuction){
	this->wasInAuction = wasInAuction;
}
bool AuctionPlayerModel::getWasInAuction(){
	return wasInAuction;
}
