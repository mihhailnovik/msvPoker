#ifndef MESSAGETRANSFORMER_H
#define MESSAGETRANSFORMER_H
#include "src/model/server/MsvClientMessage.h"
#include <QString>
#include <QDomNode>
/*
 * @author rdir52_msv team
 * Class tranform XML data to msvClientMessage objects and contrary
 */
class MessageTransformer {

public:
	static MsvClientMessage* transformClientMessage(const QString* clientXml); // returns null if message is unsupported format
	static void parseAuthenticationMessage(MsvClientMessage* clientMessage,QDomNode domNode);
	static void parseJoinTableMessage(MsvClientMessage* clientMessage,QDomNode domNode);
	static void parseJoinChairMessage(MsvClientMessage* clientMessage,QDomNode domNode);
};
#endif
