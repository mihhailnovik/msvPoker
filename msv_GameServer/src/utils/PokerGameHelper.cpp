#include "src/utils/PokerGameHelper.h"

quint16 PokerGameHelper::getNextSit(QMap<quint16, GamePlayerModel*> map,quint16 exDiler){
	QList<quint16> keys = map.keys();
	qSort(keys);
	for (quint16 i=0;i<keys.size();i++){
		if (keys[i] > exDiler) {
			return keys[i];
		}
	}
	return keys[0];
}

quint16 PokerGameHelper::getNextSit(QMap<quint16, AuctionPlayerModel*> map,quint16 exDiler){
	QList<quint16> keys = map.keys();
	qSort(keys);
	for (quint16 i=0;i<keys.size();i++){
		if (keys[i] > exDiler) {
			return keys[i];
		}
	}
	return keys[0];
}

int PokerGameHelper::getCardRank(QList<CardModel> cards){
	/*********************************************************
	 * 					Royal Flash		?					 *
	 ********************************************************/
	if (isRoyalFlush(cards)){
		return 100000;
	}
	if (isFour(cards)){
		return 90000;
	}

	if (isFullHouse(cards)){
		return 85000;
	}

	if (isFlush(cards)){
		return 80000;
	}

	if (isStraight(cards)){
		return 75000;
	}

	if (isThree(cards)){
		return 65000;
	}

	if (getTwoPairPowah(cards) != 0){
		return getTwoPairPowah(cards);
	}

	if (getPairPowah(cards) != 0){
		return getPairPowah(cards);
	}

	if (getKickerPowah(cards) != 0){
		return getKickerPowah(cards);
	}
	qDebug() << " GAME LOGIN ERROR PokerGameHelper::getCardRank";
	return 0;
}

bool PokerGameHelper::isContain(QList<CardModel> cards,int suit, int rank){
	for (int i=0;i<cards.size();i++){
		if (cards.at(i).getSuit() == suit && cards.at(i).getRanking() == rank){
			return true;
		}
	}
	return false;
}

bool PokerGameHelper::isRoyalFlush(QList<CardModel> cards){
	return false; // do not even think about it, you'll never get royal flash anyway : ) // FIXME
}

bool PokerGameHelper::isFour(QList<CardModel> cards){
	for (int i=0;i<cards.size();i++){
		CardModel model = cards.at(i);
		bool isFour = true;
		for (int i=1;i<5;i++){
			if (i != model.getSuit()){
				isFour &= isContain(cards,i,model.getRanking());
			}
		}
		if (isFour){return isFour;}
	}
	return false;
}

bool PokerGameHelper::isFullHouse(QList<CardModel> cards){
	return false; // TODO
}

bool PokerGameHelper::isFlush(QList<CardModel> cards){
	int hearts = 0;
	int spades = 0;
	int diamonds = 0;
	int clubs = 0;

	for (int i=0;i<cards.size();i++){
		CardModel model = cards.at(i);
		if (model.getSuit()== HEARTS){
			hearts++;
		}
		if (model.getSuit() == SPADES){
			spades++;
		}
		if (model.getSuit() == DIAMONDS){
			diamonds++;
		}
		if (model.getSuit() == CLUBS){
			clubs++;
		}
	}
	return (hearts == 5) || (spades==5) || (diamonds == 5) || (clubs == 5);
}

bool PokerGameHelper::isStraight(QList<CardModel> cards){
	for (int i=0;i<cards.size();i++){
		CardModel model = cards.at(i);
		int up = 1;
		bool exwasup = true;
		for (int i2=model.getRanking()+1;i2<ACE+1;i2++){
			if (!exwasup){break;}
			bool wasThere = false;
			for (int j=1;j<5;j++){
				if (exwasup && isContain(cards,j,i2)){
					up++;
					wasThere = true;
					break;
				}
			}
			if (!wasThere){
				exwasup = false;
				break;
			}
		}
		int down = 1;
		bool exwasdown = true;
		for (int i2=model.getRanking()-1;i2>1;i2--){
			if (!exwasdown){break;}
			bool wasThere = false;
			for (int j=1;j<5;j++){
				if (exwasdown && isContain(cards,j,i2)){
					down++;
					wasThere = true;
					break;
				}
			}
			if (!wasThere){
				exwasup = false;
				break;
			}
		}
		if (down + up -1 == 5){
			return true;
		}
	}
	return false;
}

bool PokerGameHelper::isThree(QList<CardModel> cards) {
	for (int i=0;i<cards.size();i++){
		CardModel model = cards.at(i);
		int sameRank = 1;
		for (int i=1;i<5;i++){
			if (i != model.getSuit()){
				if (isContain(cards,i,model.getRanking())){
					sameRank++;
				}
			}
		}
		if (sameRank == 3){
			return true;
		}
	}
	return false;
}

int PokerGameHelper::getTwoPairPowah(QList<CardModel> cards){
	int firstPairRank = 0;
	int secondPairRank = 0;
	for (int i=0;i<cards.size();i++){
		CardModel model = cards.at(i);
		for (int i2=1;i2<5;i2++) {
			if (i2 != model.getSuit()){
				if (isContain(cards,i2,model.getRanking())){
					firstPairRank = model.getRanking();
					break;
				}
			}
		}
	}

	if (firstPairRank == 0){
		return 0;
	}

	for (int i=0;i<cards.size();i++){
			CardModel model = cards.at(i);
			if (model.getRanking() == firstPairRank){
				continue;
			}
			for (int i2=1;i2<5;i2++) {
				if (i2 != model.getSuit()){
					if (isContain(cards,i2,model.getRanking())){
						secondPairRank = model.getRanking();
						break;
					}
				}
			}
		}
	return firstPairRank > secondPairRank ? firstPairRank : secondPairRank;
}

int PokerGameHelper::getPairPowah(QList<CardModel> cards){
	for (int i=0;i<cards.size();i++){
		CardModel model = cards.at(i);
		for (int i2=1;i2<5;i2++){
			if (i2 != model.getSuit()){
				if (isContain(cards,i2,model.getRanking())){
					return model.getRanking();
				}
			}
		}
	}
	return 0;
}

int PokerGameHelper::getKickerPowah(QList<CardModel> cards){
	int best = 2;
	for (int i=0;i<cards.size();i++){
		CardModel model = cards.at(i);
		if (model.getRanking() > best){
			best = model.getRanking();
		}
	}
	return best;
}
