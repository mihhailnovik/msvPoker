#ifndef MESSAGETRANSFORMER_H
#define MESSAGETRANSFORMER_H
#include <QString>
#include <QDomElement>
#include "src/model/MsvServerMessage.h"
#include "src/model/game_engine/PokerRoomModel.h"
#include "src/model/game_engine/CardModel.h"

class MessageTransformer
{
public:
	MessageTransformer();
	static MsvServerMessage* transformServerMessage(QString* serverXml);
private:
	static void parseAuthSuccesfullMessage(MsvServerMessage* model,QDomElement domElement);
	static void parseServerInfoMessage(MsvServerMessage* model,QDomElement domElement);
	static void parseJoinTableMessage(MsvServerMessage* model,QDomElement domElement);
	static void parseJoinChairMessage(MsvServerMessage* model,QDomElement domElement);
	static void parseGameAction(MsvServerMessage* model,QDomElement domElement);
	static PokerRoomModel* parsePokerRoomInfo(QDomNode domNode);
	static PokerPlayerModel* parsePokerPlayer(QDomNode playerNode);
	static CardModel parseCard(QString str);
};
#endif
