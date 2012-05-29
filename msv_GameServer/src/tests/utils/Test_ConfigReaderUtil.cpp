#include "src/tests/utils/Test_ConfigReaderUtil.h"
#include "src/utils/ConfigReaderUtil.h"
#include "src/model/server/PokerHostModel.h"
#include "src/model/server/PokerRoomModel.h"

void Test_ConfigReaderUtil::test_getHostModel(){
	PokerHostModel* model = ConfigReaderUtil::getHostModel();
	QCOMPARE(*(model->getType()),QString("SingleThread"));
	QCOMPARE(*(model->getHost()),QString("127.0.0.1"));
	if (model->getPort() != 7777){
		QFAIL("port isn't 7777");
		return;
	}
	if (model->getPokerRoomList() == NULL) {
		QFAIL("PokerroomList is null");
		return;
	}
	if (model->getPokerRoomList()->isEmpty()) {
		QFAIL("PokerroomList is empty");
		return;
	}
	PokerRoomModel* room1 = model->getPokerRoomList()->first();
	QCOMPARE(*(room1->getName()),QString("room1"));
	QCOMPARE(*(room1->getType()),QString("Texas Holdem"));
	if (room1->getMaxPlayers() != 5) {
		QFAIL("Max players isn't 5 ");
	}
}
