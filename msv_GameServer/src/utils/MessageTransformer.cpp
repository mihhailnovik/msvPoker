#include "src/utils/MessageTransformer.h"
#include "src/utils/MessageDefines.h"
#include "src/utils/XmlParserHelper.h"
#include "src/utils/StringUtil.h"
#include "src/model/server/JoinChairInfoModel.h"

#include <QDomDocument>
#include <QDomNode>
#include <QDebug>

MsvClientMessage* MessageTransformer::transformClientMessage(const QString* xmlMessage) {
	QDomDocument doc;
	MsvClientMessage* clientMessage = new MsvClientMessage();
	if (doc.setContent(*xmlMessage,false)) {
		 QDomElement domElement= doc.documentElement(); // msvClientMessage Element
		 QDomNode domNode = domElement.firstChild();
		 if (!XmlParserHelper::checkNodeName(domNode,TYPE)) {
			qDebug() << "MessageTransformer::transformClientMessage# Warning !!! First element child isn't type !" << endl;
			return NULL;
		 }
		 qDebug() << "MessageTransformer::transformClientMessage# type = " <<XmlParserHelper::getElementText(domNode)<< endl;
		 QString type = XmlParserHelper::getElementText(domNode);
		 if (type.compare(AUTHENTICATION) == 0){ // if authentication
			 clientMessage->setType(new QString(AUTHENTICATION));
			 parseAuthenticationMessage(clientMessage,domNode);
			 return clientMessage;
		 }

		 if (type.compare(JOIN_TABLE) == 0) {
			 clientMessage->setType(new QString(JOIN_TABLE));
			 parseJoinTableMessage(clientMessage,domNode);
			 return clientMessage;
		 }

		 if (type.compare(GETINFO) == 0){
			 clientMessage->setType(new QString(GETINFO));
			 return clientMessage;
		 }

		 if (type.compare(JOIN_CHAIR) == 0){
			 clientMessage->setType(new QString(JOIN_CHAIR));
			 parseJoinChairMessage(clientMessage,domNode);
			 return clientMessage;
		 }

		 if (StringUtil::isEquals(type,QString("bet"))) {
			 clientMessage->setType(new QString("bet"));
			 domNode = domNode.nextSibling(); // <bet>
			 if (!XmlParserHelper::checkNodeName(domNode,QString("bet"))){
				qDebug() << "MessageTransformer::transformClientMessage# Warning ! bet element not found" <<  endl;
				return NULL;
			 }
			 QString bet = XmlParserHelper::getElementText(domNode);
			 clientMessage->setBet(bet.toInt());
			 return clientMessage;
		 }
		 qDebug() << "MessageTransformer::transformClientMessage# WARNING uknow message type" << endl;
		 return NULL;
	} else {
		qDebug() << "MessageTransformer::transformClientMessage# Can't set xml content " << *xmlMessage << endl;
	}
	qDebug() << "MessageTransformer::transformClientMessage# Message processed sucessfull " << endl;
	return clientMessage;
}

void MessageTransformer::parseAuthenticationMessage(MsvClientMessage* clientMessage,QDomNode domNode) {
	qDebug() << "MessageTransformer::parseAuthenticationMessage# paseAuthentication message"<< endl;
	domNode = domNode.nextSibling();
	 if (!XmlParserHelper::checkNodeName(domNode,AUTHINFO)){
		 qDebug() << "MessageTransformer::parseAuthenticationMessage# Warning ! "<< AUTHINFO << " element not found" <<  endl;
		 return ;
	 }
	 domNode = domNode.firstChild(); // login
	 if (!XmlParserHelper::checkNodeName(domNode,QString("login"))){
		 qDebug() << "MessageTransformer::parseAuthenticationMessage# Warning ! login element not found" <<  endl;
		 return ;
	 }
	 QString* login = new QString(XmlParserHelper::getElementText(domNode));
	 domNode = domNode.nextSibling(); // password
	 if (!XmlParserHelper::checkNodeName(domNode,QString("pass"))){
		 qDebug() << "MessageTransformer::parseAuthenticationMessage# Warning ! password element not found" <<  endl;
		 return ;
	 }
	 QString* password = new QString(XmlParserHelper::getElementText(domNode));
	 AuthInfoModel* authInfoModel = new AuthInfoModel(login,password);
	 clientMessage->setAuthInfoModel(authInfoModel);
}

void MessageTransformer::parseJoinTableMessage(MsvClientMessage* clientMessage,QDomNode domNode) {
	domNode = domNode.nextSibling(); //join_table
	if (!XmlParserHelper::checkNodeName(domNode,"joinTableInfo")){
		 qDebug() << "MessageTransformer::parseJoinTableMessage# Warning ! "<< JOIN_TABLE_INFO << " element not found" <<  endl;
		 return;
	}
	JoinTableInfoModel* infoModel = new JoinTableInfoModel();
	domNode = domNode.firstChild(); //table_id
	if (!XmlParserHelper::checkNodeName(domNode,TABLE_ID)){
		 qDebug() << "MessageTransformer::parseJoinTableMessage# Warning ! "<< TABLE_ID << " element not found" <<  endl;
		 return;
	}
	QString table = XmlParserHelper::getElementText(domNode);
	infoModel->setTableId(table.toInt());
	clientMessage->setJoinTableModel(infoModel);
}

void MessageTransformer::parseJoinChairMessage(MsvClientMessage* clientMessage,QDomNode domNode) {
	domNode = domNode.nextSibling(); //join_chair
	if (!XmlParserHelper::checkNodeName(domNode,"joinChairInfo")){
		qDebug() << "MessageTransformer::parseJoinChairMessage# Warning ! joinChairInfo element not found" <<  endl;
		return;
	}
	JoinChairInfoModel* model = new JoinChairInfoModel();
	domNode = domNode.firstChild(); //chair_id

	if (!XmlParserHelper::checkNodeName(domNode,"chair_id")){
		 qDebug() << "MessageTransformer::parseJoinChairMessage# Warning ! chair_id element not found" <<  endl;
		 return;
	}
	 QString chair = XmlParserHelper::getElementText(domNode);
	 model->setChairId(chair.toInt());
	 clientMessage->setJoinChairInfoModel(model);
}
