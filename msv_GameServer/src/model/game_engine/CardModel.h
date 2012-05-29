#ifndef CARDMODEL_H
#define CARDMODEL_H
#include <QString>
#include "src/model/game_engine/CardDefines.h"

/**
 * @author rdir52_msv team
 */
class CardModel {
public:
	CardModel(quint16 ranking, quint16 suit);
	~CardModel();
	const quint16 getSuit() const;
	const quint16 getRanking() const;
	QString toString() const;

private:
	quint16 suit;
	quint16 ranking;
};
#endif
