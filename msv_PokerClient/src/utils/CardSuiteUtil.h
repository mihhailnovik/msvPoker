#ifndef CARDSUITEUTIL_H
#define CARDSUITEUTIL_H
#include "src/model/game_engine/CardModel.h"
#include <QChar>
#include <QString>

class CardSuiteUtil
{
public:
	CardSuiteUtil();
	static CardModel* toCard(QString str);
	static int suitToInt(QChar suit);
	static int rankToInt(QChar rank);

	static QString intToSuit(int value);
	static QString intToRank(int value);
	static QString toFileName(CardModel model);
};
#endif
