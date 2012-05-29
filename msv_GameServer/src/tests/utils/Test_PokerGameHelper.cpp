#include "src/tests/utils/Test_PokerGameHelper.h"
#include "src/utils/PokerGameHelper.h"
#include <QMap>
#include "src/model/server/PokerPlayerModel.h"

void Test_PokerGameHelper::test_getNextSit(){
	QMap<quint16,PokerPlayerModel*>* playersMap = new QMap<quint16, PokerPlayerModel*>();
	playersMap->insert(1,NULL);
	playersMap->insert(2,NULL);
	playersMap->insert(3,new PokerPlayerModel());
	playersMap->insert(4,NULL);
	playersMap->insert(5,new PokerPlayerModel());
	playersMap->insert(6,new PokerPlayerModel());


	int result = PokerGameHelper::getNextSit(playersMap,1);
	QCOMPARE(result, 3);
	result = PokerGameHelper::getNextSit(playersMap,result);
	QCOMPARE(result, 5);
	result = PokerGameHelper::getNextSit(playersMap,result);
	QCOMPARE(result, 6);
	result = PokerGameHelper::getNextSit(playersMap,result);
	QCOMPARE(result, 3);
}
