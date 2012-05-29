#include "src/service/AuthenticationService.h"
#include "src/tests/service/Test_AuthenticationService.h"

void Test_AuthenticationService::test_authenticate(){
	AuthenticationService authService;
	PokerPlayerModel* model  = authService.authenticate("mi1","123456");
	QCOMPARE(*(model->getName()),QString("mi1"));
}
