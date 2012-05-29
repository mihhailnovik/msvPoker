#include "src/tests/utils/Test_MessageTransformer.h"
#include "src/utils/MessageTransformer.h"
#include "src/model/server/MsvClientMessage.h"
#include <QtTest>
#include <QString>

void Test_MessageTransformer::test_transformClientMessage(){
	/* Authetication message transform */
	QString message("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	message.append("<msvClientMessage>");
		message.append("<type>");
			message.append("authentication");
		message.append("</type>");
		message.append("<authInfo>");
			message.append("<login>");
				message.append("login");
			message.append("</login>");
			message.append("<pass>");
				message.append("password");
			message.append("</pass>");
		message.append("</authInfo>");
	message.append("</msvClientMessage>");

	MsvClientMessage* clientMessage = MessageTransformer::transformClientMessage(&message);
	if (!(clientMessage->isAuthentication())){
		QFAIL("Sould be auth message !");
	}
	if (clientMessage->getAuthInfoModel() == NULL){
		QFAIL("AuthInfoModel is null");
		return;
	}
	QCOMPARE(*(clientMessage->getAuthInfoModel()->getLogin()),QString("login"));
	QCOMPARE(*(clientMessage->getAuthInfoModel()->getPass()),QString("password"));
}
