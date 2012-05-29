#include "src/model/game_engine/CardModel.h"
#include <QChar>

CardModel::CardModel(quint16 ranking, quint16 suit){
	this->suit = suit;
	this->ranking = ranking;
}

CardModel::~CardModel(){

}

const quint16 CardModel::getSuit() const {
	return suit;
}
const quint16 CardModel::getRanking() const{
	return ranking;
}

QString CardModel::toString() const{
	QString name;
	switch(ranking){
		case JACK: name.append("J");break;
		case QUEEN: name.append("Q");break;
		case KING: name.append("K");break;
		case ACE: name.append("A");break;
		default: name.append(QString::number(ranking));break;
	}

	switch(suit) {
		case HEARTS: name.append(QChar(3));break;
		case SPADES: name.append(QChar(6));break;
		case DIAMONDS: name.append(QChar(4));break;
		case CLUBS: name.append(QChar(5));break;
	}
	return name;
}
