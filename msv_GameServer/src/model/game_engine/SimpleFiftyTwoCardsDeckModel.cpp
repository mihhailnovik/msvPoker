#include "src/model/game_engine/SimpleFiftyTwoCardsDeckModel.h"
#include <QTime>

SimpleFiftyTwoCardsDeckModel::SimpleFiftyTwoCardsDeckModel() : AbstractCardsDeckModel() {
	for (quint16 i = 2;i<15;i++){
		for (quint16 j = 1; j< 5;j++) {
			cardDeck.append(CardModel(i,j));
		}
	}
}

SimpleFiftyTwoCardsDeckModel::~SimpleFiftyTwoCardsDeckModel(){
}


QList<CardModel> SimpleFiftyTwoCardsDeckModel::getRandomCards(quint16 count){
	QList<CardModel> list;
	for (int i = 0;i<count;i++){
		list.append(getRandomCard());
	}
	return list;
}

CardModel SimpleFiftyTwoCardsDeckModel::getRandomCard(){
	QTime midnight(0, 0, 0);
	qsrand(midnight.secsTo(QTime::currentTime()));
	int nr = qrand() % cardDeck.size();

	CardModel returnCard = cardDeck.at(nr);
	cardDeck.removeAt(nr);
	return returnCard;
}

void SimpleFiftyTwoCardsDeckModel::shuffle(){
	// TODO
}
