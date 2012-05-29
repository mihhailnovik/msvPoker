#ifndef SIMPLEFIFTYTWOCARDSDECKMODEL_H
#define SIMPLEFIFTYTWOCARDSDECKMODEL_H
#include <QObject>
#include "src/model/game_engine/CardDefines.h"
#include "src/model/game_engine/AbstractCardsDeckModel.h"
/**
 * @author rdir52_msv team
 */
class SimpleFiftyTwoCardsDeckModel: public AbstractCardsDeckModel {
	Q_OBJECT
public:
	SimpleFiftyTwoCardsDeckModel();
	~SimpleFiftyTwoCardsDeckModel();
	QList<CardModel> getRandomCards(quint16 count);
	CardModel getRandomCard();
	void shuffle(); //@parent
};
#endif
