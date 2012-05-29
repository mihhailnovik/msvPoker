#include "src/tests/service/Test_AuthenticationService.h"
#include "src/tests/model/game_engine/Test_SimpleFiftyTwoCardsDeckModel.h"
#include "src/tests/utils/Test_PokerGameHelper.h"
#include "src/tests/utils/Test_ConfigReaderUtil.h"
#include "src/tests/utils/Test_MessageTransformer.h"
int main(int argc, char *argv[]){

	Test_AuthenticationService authTest;
	Test_PokerGameHelper pokerGameHelperTest;
	Test_MessageTransformer messageTransformer;
	Test_ConfigReaderUtil configReaderUtilTest;

	//Test_SimpleFiftyTwoCardsDeckModel cardDeckTest;
    QTest::qExec(&authTest);
    QTest::qExec(&pokerGameHelperTest);
    QTest::qExec(&messageTransformer);
    QTest::qExec(&configReaderUtilTest);
    //QTest::qExec(&cardDeckTest);
	return 0;
}

