#include "src/model/game_engine/SimpleFiftyTwoCardsDeckModel.h"
#include "src/tests/model/game_engine/Test_SimpleFiftyTwoCardsDeckModel.h"

void Test_SimpleFiftyTwoCardsDeckModel::test_getRandomCards() {
	SimpleFiftyTwoCardsDeckModel cardDeck;
//	QList<const CardModel*>* keepList = new QList<const CardModel*>();
//	QList<const CardModel*> cards = cardDeck.getRandomCards(10);
//	for (quint16 i = 0;i<10;i++){
//		for (quint16 j = 0;j<keepList->size();j++){
//			if (keepList->value(j)->getSuit() == cards.value(i)->getSuit() && keepList->value(j)->getRanking() == cards.value(i)->getRanking()){
//				QFAIL ("Seems we have identical cards in card deck");
//			}
//			keepList->append(cards.value(i));
//		}
//	}
}

void Test_SimpleFiftyTwoCardsDeckModel::test_getRandomCard() {
	SimpleFiftyTwoCardsDeckModel cardDeck;
//	QList<const CardModel*>* keepList = new QList<const CardModel*>();
//	for (quint16 i = 0;i<52;i++){
//		const CardModel* card = cardDeck.getRandomCard();
//		for (quint16 j = 0;j<keepList->size();j++){
//			if (keepList->value(j)->getSuit() == card->getSuit() && keepList->value(j)->getRanking() == card->getRanking()){
//				QFAIL ("Seems we have identical cards in card deck");
//			}
//		}
//		keepList->append(card);
//	}
}

