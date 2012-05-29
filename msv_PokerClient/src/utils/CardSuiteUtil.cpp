#include "src/utils/CardSuiteUtil.h"
#include <QDebug>
CardSuiteUtil::CardSuiteUtil()
{
}

CardModel* CardSuiteUtil::toCard(QString str) {
	if (str.length() != 3 && str.length() != 2) {
		qDebug() << "CardSuiteUtil::toCard# WARNING !! imposible card" << endl;
		return NULL;
	}
	if (str.length() == 3) {
		return new CardModel(10,suitToInt(str[2]));
	}
	return new CardModel(rankToInt(str[0]),suitToInt(str[1]));
}

int CardSuiteUtil::suitToInt(QChar suit){
	if (suit == QChar(88)) {
		return 0; // X, unknown card
	}
	if (suit == QChar(3)) {
		return 1; // HEARTS
	}
	if (suit == QChar(6)) {
		return 2; // SPADES
	}
	if (suit == QChar(4)) {
		return 3; // DIAMONDS
	}
	if (suit == QChar(5)) {
		return 4; // CLUBS
	}
	qDebug() << "CardSuiteUtil::suitToInt# WARNING imposible suit" << endl;
	return 0;
}

int CardSuiteUtil::rankToInt(QChar rank){
	if (rank == QChar(88)) {
		return 0; // X, unknown card
	}
	if (rank == QChar(65)){
		return 14; // ACE
	}
	if (rank == QChar(75)) {
		return 13;// KING
	}
	if (rank == QChar(81)) {
		return 12;// QUEEN
	}
	if (rank == QChar(74)) {
		return 11;// JACKET
	}
	if (rank.isDigit()) {
		return rank.digitValue();
	}
	qDebug() << "CardSuiteUtil::rankToInt# WARNING imposible rank " << endl;
	return 0;
}

QString CardSuiteUtil::intToSuit(int value) {
	if ( value == 0) {
		return "X";
	}

	if (value == 1) {
		return "H";// HEARTS
	}
	if (value == 2) {
		return "S";// SPADES
	}
	if (value == 3) {
		return "D";// DIAMONDS
	}
	if (value == 4) {
		return "C";// CLUBS
	}

	return "X";
}

QString CardSuiteUtil::intToRank(int value){
	QString result;

	if (value == 0 ){
		return "X";
	}
	if (value > 1 && value < 11) {
		result.setNum(value);
		return result;
	}
	if (value == 11) {
		return "J";
	}
	if (value == 12) {
		return "Q";
	}
	if (value == 13) {
		return "K";
	}
	if (value == 14) {
		return "A";
	}
	return "X";
}

QString CardSuiteUtil::toFileName(CardModel model) {
	QString result;
	result.append(intToRank(model.getRanking()));
	result.append("_");
	result.append(intToSuit(model.getSuit()));
	result.append("_1");// TODO
	result.append(".jpg");
	return result;
}
