#include "src/tests/gui/Test_PlayerInfoWidget.h"
#include <QTest>

int main(int argc, char *argv[]){
	Test_PlayerInfoWidget tableChoseTest;
	QTest::qExec(&tableChoseTest);
	return 0;
}

