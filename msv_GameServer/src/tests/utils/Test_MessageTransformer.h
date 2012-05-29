#ifndef TEST_MESSAGETRANSFORMER_H
#define TEST_MESSAGETRANSFORMER_H
#include <QtTest>
#include <QObject>

/*
 * @author rdir52_msv team
 */
class Test_MessageTransformer: public QObject {
Q_OBJECT
private slots:
	void test_transformClientMessage();
	/*void test_transformServerInfoResponse();
	void test_transformAuthenticationOkResponse();
	void test_transformAuthenticationFailedResponse();
	void test_transformUnknownMessageFormatResponse();
	void test_transformCantJoinTable();
	void test_transformTableJoinSuccessfully();
	void test_transformServerMessageResponse();
	*/
};
#endif
