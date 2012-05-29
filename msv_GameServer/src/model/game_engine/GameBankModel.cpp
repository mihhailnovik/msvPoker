#include "src/model/game_engine/GameBankModel.h"

GameBankModel::GameBankModel() {
	bank = 0;
}

GameBankModel::~GameBankModel(){

}

GameBankModel::GameBankModel(const GameBankModel &){

}

void GameBankModel::add(quint16 amount){
	bank += amount;
}

quint16 GameBankModel::getMoney() const {
	return bank;
}
