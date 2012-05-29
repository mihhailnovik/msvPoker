#include "src/utils/MessageTransformer.h"
#include "src/model/MsvServerMessage.h"
#include "src/model/AuthInfoModel.h"
#include "src/model/PokerPlayerModel.h"
#include "src/model/game_engine/PokerRoomModel.h"
#include "src/utils/StringUtil.h"
#include "src/utils/XmlParserHelper.h"
#include "src/model/PlayerJoinChairModel.h"
#include "src/model/game_engine/CardModel.h"
#include "src/utils/CardSuiteUtil.h"
#include <QDomDocument>
#include <QDomElement>
#include <QDebug>
#include <QDomNode>
#include <QList>

MessageTransformer::MessageTransformer()
{

}

MsvServerMessage* MessageTransformer::transformServerMessage(QString* serverXml){
	QDomDocument doc;
	MsvServerMessage* model = new MsvServerMessage();
	if (doc.setContent(*serverXml,false)) {
			 QDomElement domElement= doc.documentElement(); // msvServerMessage Element
			 QDomNode domNode = domElement.firstChild(); // type

			 if (!XmlParserHelper::checkNodeName(domNode,QString("type"))) {
				qDebug() << "Check node fail (type)" << endl;
				return NULL;
			 }

			 QString type = XmlParserHelper::getElementText(domNode);
			 if (XmlParserHelper::isEquals("authentication_succesfull",type)){ // auth succesfull
				 parseAuthSuccesfullMessage(model,domElement);
				 return model;
			 }

			 if(XmlParserHelper::isEquals("auth_failed",type)){
				 model->setType(new QString("auth_failed"));
				 return model;
			 }

			 if (XmlParserHelper::isEquals(QString("server_info"),type)) {
				 parseServerInfoMessage(model,domElement);
				 return model;
			 }

			 if (XmlParserHelper::isEquals(QString("join_table"),type)) {
				 parseJoinTableMessage(model,domElement);
				 return model;
			 }
			 if (XmlParserHelper::isEquals(QString("player_joined_chair"),type)) {
				 parseJoinChairMessage(model,domElement);
				 return model;
			 }

			 if (XmlParserHelper::isEquals(QString("game_action"),type)) {
				 parseGameAction(model,domElement);
				 return model;
			 }

			 if (XmlParserHelper::isEquals(QString("your_turn"),type)) {
				 model->setType(new QString("your_turn"));
				 return model;
			 }
	} else {
		qDebug() << "MessageTransformer::transformServerMessage Can't set xml !!" << endl;
	}
	qDebug() << "MessageTransformer::transformServerMessage# Warning !!!! unknow type :(" << endl;
	return model;
}

void MessageTransformer::parseGameAction(MsvServerMessage* model,QDomElement domElement){
	model->setType(new QString("game_action"));
	QDomNode domNode = domElement.firstChild(); //type
	domNode = domNode.nextSibling(); //gameAction

	if (!XmlParserHelper::checkNodeName(domNode,QString("gameAction"))){
		qDebug() << "MessageTransformer::parseGameAction# Warning ! gameAction element not found" <<  endl;
		return;
	}
	domNode = domNode.firstChild();//maxPlayers

	if (!XmlParserHelper::checkNodeName(domNode,QString("maxPlayers"))){
		qDebug() << "MessageTransformer::parseGameAction# Warning ! maxPlayers element not found" <<  endl;
		return;
	}
	PokerRoomModel* room1 = new PokerRoomModel(NULL,XmlParserHelper::getElementText(domNode).toInt());

	domNode = domNode.nextSibling(); //<players>
	if (!XmlParserHelper::checkNodeName(domNode,QString("players"))){
		qDebug() << "MessageTransformer::parseGameAction# Warning ! players element not found" <<  endl;
		return;
	}

	QDomNode playerNode = domNode.firstChild(); // player if exist
	if (!(playerNode.isNull())) {
		PokerPlayerModel* player1  = parsePokerPlayer(playerNode);
		room1->takeSeat(player1,player1->getChairId());
		do {
			playerNode = playerNode.nextSibling();
			if (!playerNode.isNull() && XmlParserHelper::isEquals("name",playerNode.firstChild().nodeName())) {
				PokerPlayerModel* player  = parsePokerPlayer(playerNode);
				room1->takeSeat(player,player->getChairId());
			}
		}
		while (!playerNode.isNull()&& XmlParserHelper::isEquals("name",playerNode.firstChild().nodeName()));
	}
	domNode = domNode.nextSibling(); //<table>
	if (!XmlParserHelper::checkNodeName(domNode,QString("table"))){
		qDebug() << "MessageTransformer::parseGameAction# Warning ! table element not found" <<  endl;
		return;
	}

	domNode = domNode.firstChild(); // <cards>
	if (!XmlParserHelper::checkNodeName(domNode,QString("cards"))){
		qDebug() << "MessageTransformer::parseGameAction# Warning ! cards element not found" <<  endl;
		return;
	}
	QDomNode cardDomNode = domNode.firstChild();// card
	if (!cardDomNode.isNull()) {
		if (!XmlParserHelper::checkNodeName(cardDomNode,QString("card"))){
			qDebug() << "MessageTransformer::parseGameAction# Warning ! card element not found [element = " <<cardDomNode.toElement().text() <<"]"<< endl;
			return;
		}
		room1->addCard(CardSuiteUtil::toCard(XmlParserHelper::getElementText(cardDomNode)));
		do { cardDomNode = cardDomNode.nextSibling();
			if (!(cardDomNode.isNull())) { // card
				if (!XmlParserHelper::checkNodeName(cardDomNode,QString("card"))){
					qDebug() << "MessageTransformer::parseGameAction# Warning ! card element not found [element = " <<domNode.toElement().text() <<"]"<< endl;
					return;
				}
				room1->addCard(CardSuiteUtil::toCard(XmlParserHelper::getElementText(cardDomNode)));
			}
		} while (!(cardDomNode.isNull()));
	}
	qDebug() << "MessageTransformer::parseGameAction# cards presented ? " << room1->getCards()->isEmpty();

	QDomNode money = domNode.nextSibling(); // <money>
	if (!XmlParserHelper::checkNodeName(money,QString("money"))){
		qDebug() << "MessageTransformer::parseGameAction# Warning ! money element not found [element = " <<domNode.toElement().text() <<"]"<< endl;
		return;
	}
	room1->setMoney(XmlParserHelper::getElementText(money).toInt());
	model->setPokerRoomModel(room1);
}

void MessageTransformer::parseAuthSuccesfullMessage(MsvServerMessage* model,QDomElement domElement){
	 model->setType(new QString("authentication_succesfull"));
	 QDomNode domNode = domElement.firstChild(); //type
	 domNode = domNode.nextSibling(); //authInfo
	 if (!XmlParserHelper::checkNodeName(domNode,QString("authInfo"))){
		 qDebug() << "MessageTransformer::parseAuthSuccesfullMessage# Warning ! authInfo element not found" <<  endl;
		 return;
	 }

	 domNode = domNode.firstChild(); // <player>
	 domNode = domNode.firstChild(); // <name>
	 QString* name = new QString(XmlParserHelper::getElementText(domNode));

	 domNode = domNode.nextSibling(); // money
	 QString* money = new QString(XmlParserHelper::getElementText(domNode));

	 AuthInfoModel* authModel = new AuthInfoModel();
	 PokerPlayerModel* playerModel = new PokerPlayerModel();
	 playerModel->setName(name);
	 playerModel->setMoney(money->toInt());
	 authModel->setPokerPlayer(playerModel);
	 model->setAuthInfoModel(authModel);
}

void MessageTransformer::parseServerInfoMessage(MsvServerMessage* model,QDomElement domElement){
	ServerInfoModel* serverInfoModel = new ServerInfoModel();
	model->setType(new QString("server_info"));
	QDomNode domNode = domElement.firstChild(); //type
	domNode = domNode.nextSibling(); //serverInfo
	if (!(XmlParserHelper::checkNodeName(domNode,"serverInfo"))) {
		qDebug() << "Missing serverInfo tag " << endl ;
	}
	domNode = domNode.firstChild(); //<pokerRooms>
	if (!(XmlParserHelper::checkNodeName(domNode,"pokerRooms"))) {
		qDebug() << "Missing serverInfo pokerRooms " << endl ;
	}
	QList<PokerRoomModel*>* roomList = new QList<PokerRoomModel*>();
	QDomNode roomNode = domNode.firstChild(); // pokerRoom if exist
	quint16 id = 1;
	if (!(roomNode.isNull())) {
		PokerRoomModel* room1  = parsePokerRoomInfo(roomNode);
		room1->setId(id);
		id++;
		roomList->append(room1);
		do {
			roomNode = roomNode.nextSibling();
			if (!roomNode.isNull() && XmlParserHelper::isEquals("name",roomNode.firstChild().nodeName())) {
				PokerRoomModel* room2  = parsePokerRoomInfo(roomNode);
				room2->setId(id);
				id++;
				roomList->append(room2);
			}
		}
		while (!roomNode.isNull()&& XmlParserHelper::isEquals("name",roomNode.firstChild().nodeName()));
	}
	serverInfoModel->setRoomList(roomList);
	model->setServerInfoModel(serverInfoModel);
}

PokerRoomModel* MessageTransformer::parsePokerRoomInfo(QDomNode roomNode){
	if (!(XmlParserHelper::checkNodeName(roomNode,QString("pokerroom")))){
		qDebug() << "MessageTransformer::parsePokerRoomInfo# This isn't pokerroom tag, fuck you !" << endl;
		return NULL;
	}
	PokerRoomModel* room1 = new PokerRoomModel();
	roomNode = roomNode.firstChild(); // name
	if (!(XmlParserHelper::checkNodeName(roomNode,QString("name")))){
		qDebug() << "MessageTransformer::parsePokerRoomInfo# Warning invalid tag name" << endl;
		return NULL;
	}
	room1->setName(new QString(XmlParserHelper::getElementText(roomNode)));

	roomNode = roomNode.nextSibling(); // type
	if (!(XmlParserHelper::checkNodeName(roomNode,QString("type")))){
		qDebug() << "MessageTransformer::parsePokerRoomInfo# Warning invalid tag type" << endl;
		return NULL;
	}
	room1->setType(new QString(XmlParserHelper::getElementText(roomNode)));

	roomNode = roomNode.nextSibling(); // maxPlayers
	if (!(XmlParserHelper::checkNodeName(roomNode,QString("maxPlayers")))){
		qDebug() << "MessageTransformer::parsePokerRoomInfo# Warning invalid tag maxPlayers" << endl;
		return NULL;
	}
	room1->setMaxPlayers(XmlParserHelper::getElementText(roomNode).toInt());

	roomNode = roomNode.nextSibling(); // players
	if (!(XmlParserHelper::checkNodeName(roomNode,QString("players")))){
		qDebug() << "MessageTransformer::parsePokerRoomInfo# Warning invalid tag players" << endl;
		return NULL;
	}

	QDomNode playerNode = roomNode.firstChild(); // player if exist

	if (!(playerNode.isNull())) {
		PokerPlayerModel* player1  = parsePokerPlayer(playerNode);
		room1->takeSeat(player1,player1->getChairId());

		do {
			playerNode = playerNode.nextSibling();
			if (!playerNode.isNull() && XmlParserHelper::isEquals("name",playerNode.firstChild().nodeName())) {
				PokerPlayerModel* player  = parsePokerPlayer(playerNode);
				room1->takeSeat(player,player->getChairId());
			}
		}
		while (!playerNode.isNull()&& XmlParserHelper::isEquals("name",playerNode.firstChild().nodeName()));
	}

	return room1;
}

PokerPlayerModel* MessageTransformer::parsePokerPlayer(QDomNode playerNode) {
	PokerPlayerModel* model = new PokerPlayerModel(); //player
	playerNode = playerNode.firstChild(); //name
	if (!(XmlParserHelper::checkNodeName(playerNode,QString("name")))){
		qDebug() << "MessageTransformer::parsePokerPlayer# Warning invalid tag name" << XmlParserHelper::getElementText(playerNode) <<endl;
		return NULL;
	}
	model->setName(new QString(XmlParserHelper::getElementText(playerNode)));

	playerNode = playerNode.nextSibling(); //money
	if (!(XmlParserHelper::checkNodeName(playerNode,QString("money")))){
		qDebug() << "MessageTransformer::parsePokerPlayer# Warning invalid tag money" << endl;
		return NULL;
	}
	model->setMoney(XmlParserHelper::getElementText(playerNode).toInt());

	playerNode = playerNode.nextSibling(); //chair_id
	if (!(XmlParserHelper::checkNodeName(playerNode,QString("chair_id")))){
		qDebug() << "MessageTransformer::parsePokerPlayer# Warning invalid tag chair_id " <<playerNode.nodeName() <<endl;
		return NULL;
	}
	model->setChairId(XmlParserHelper::getElementText(playerNode).toInt());

	playerNode = playerNode.nextSibling(); //diler
	if (playerNode.isNull()) {
		return model;
	}
	if (!(XmlParserHelper::checkNodeName(playerNode,QString("diler")))){
		qDebug() << "MessageTransformer::parsePokerPlayer# Warning invalid tag diler" << endl;
		return NULL;
	}
	model->setDiler(StringUtil::valueOf(XmlParserHelper::getElementText(playerNode)));

	playerNode = playerNode.nextSibling();//lastActionName
	if (!(XmlParserHelper::checkNodeName(playerNode,QString("lastActionName")))){
		qDebug() << "MessageTransformer::parsePokerPlayer# Warning invalid tag lastActionName" << endl;
		return NULL;
	}
	model->setLastAction(XmlParserHelper::getElementText(playerNode));

	playerNode = playerNode.nextSibling();//currentRoundMoney
	if (!(XmlParserHelper::checkNodeName(playerNode,QString("currentRoundMoney")))){
		qDebug() << "MessageTransformer::parsePokerPlayer# Warning invalid tag currentRoundMoney" << endl;
		return NULL;
	}
	model->setRoundMoney(XmlParserHelper::getElementText(playerNode).toInt());

	playerNode = playerNode.nextSibling();//cards

	if (XmlParserHelper::checkNodeName(playerNode,QString("cards"))){
		QDomNode cardNode = playerNode.firstChild(); // card
			if (!(XmlParserHelper::checkNodeName(cardNode,QString("card")))){
				qDebug() << "MessageTransformer::parsePokerPlayer# Warning invalid tag card" << endl;
				return NULL;
			}
			QString card1 = XmlParserHelper::getElementText(cardNode);

			cardNode = cardNode.nextSibling(); // card
			if (!(XmlParserHelper::checkNodeName(cardNode,QString("card")))){
				qDebug() << "MessageTransformer::parsePokerPlayer# Warning invalid tag card" << endl;
				return NULL;
			}
			QString card2 = XmlParserHelper::getElementText(cardNode);

			QList<CardModel> cards;
			cards.append(parseCard(card1));
			cards.append(parseCard(card2));
			model->setCardList(cards);
	}

	return model;
}

CardModel MessageTransformer::parseCard(QString str) {
	return *(CardSuiteUtil::toCard(str));
}

void MessageTransformer::parseJoinChairMessage(MsvServerMessage* model,QDomElement domElement){
	model->setType(new QString("player_joined_chair"));
	QDomNode domNode = domElement.firstChild();//type
	if (!(XmlParserHelper::checkNodeName(domNode,QString("type")))){
		qDebug() << "MessageTransformer::parseJoinChairMessage# Warning invalid tag type" << endl;
		return;
	}
	domNode = domNode.nextSibling(); // <playerJoinedChair>
	if (!(XmlParserHelper::checkNodeName(domNode,QString("playerJoinedChair")))){
		qDebug() << "MessageTransformer::parseJoinChairMessage# Warning invalid tag join_table" << endl;
		return;
	}
	domNode = domNode.firstChild(); // <player>
	if (!(XmlParserHelper::checkNodeName(domNode,QString("player")))){
		qDebug() << "MessageTransformer::parseJoinChairMessage# Warning invalid tag join_table" << endl;
		return;
	}
	PokerPlayerModel* player1  = parsePokerPlayer(domNode);
	domNode = domNode.nextSibling(); // <chair_id>
	if (!(XmlParserHelper::checkNodeName(domNode,QString("chair_id")))){
		qDebug() << "MessageTransformer::parseJoinChairMessage# Warning invalid tag join_table" << endl;
		return;
	}
	QString chairIdStr = XmlParserHelper::getElementText(domNode);
	quint16 chairId = chairIdStr.toInt();
	PlayerJoinChairModel* playerJoinChairModel = new PlayerJoinChairModel();
	playerJoinChairModel->setPokerPlayerModel(player1);
	playerJoinChairModel->setChairId(chairId);
	model->setPlayerJoinChairModel(playerJoinChairModel);
}

void MessageTransformer::parseJoinTableMessage(MsvServerMessage* model,QDomElement domElement){
	QDomNode domNode = domElement.firstChild();//type
	model->setType(new QString("join_table"));
	if (!(XmlParserHelper::checkNodeName(domNode,QString("type")))){
		qDebug() << "MessageTransformer::parseJoinTableMessage# Warning invalid tag type" << endl;
		return;
	}
	domNode = domNode.nextSibling(); // <join_table>
	if (!(XmlParserHelper::checkNodeName(domNode,QString("join_table")))){
		qDebug() << "MessageTransformer::parseJoinTableMessage# Warning invalid tag join_table" << endl;
		return;
	}
	domNode = domNode.firstChild(); // pokerroom
	if (!(XmlParserHelper::checkNodeName(domNode,QString("pokerroom")))){
		qDebug() << "MessageTransformer::parseJoinTableMessage# Warning invalid tag pokerroom" << endl;
		return;
	}
	PokerRoomModel* pokerRoom = parsePokerRoomInfo(domNode);
	JoinTableInfoModel* joinModel = new JoinTableInfoModel();
	joinModel->setPokerRoomModel(pokerRoom);
	model->setJoinTableInfoModel(joinModel);
}
