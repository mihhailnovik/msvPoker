#include "src/utils/ConfigReaderUtil.h"
#include "src/model/server/PokerRoomModel.h"
#include "src/utils/XmlParserHelper.h"
#include "src/model/server/BetModel.h"
#include <QList>	
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QString>
#include <QIODevice>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

PokerHostModel* ConfigReaderUtil::getHostModel() { // FIXME dirty code, refactor please, use XmlParserHelper
	QFile file(":/serverConfig.xml");
	PokerHostModel* model = new PokerHostModel();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    	qDebug() << "Can't read file !!!";
        return NULL;
    }
    QTextStream in(&file);
    QString content = in.readAll();
    QDomDocument doc;
    if (doc.setContent(content,false)) {
	    	QDomElement domElement= doc.documentElement(); // <pokerHost>  Element
	    	QDomNode node = domElement.firstChild (); // <server>
	    	QDomNode node1 = node.firstChild(); // <type>

	    	 if (!XmlParserHelper::checkNodeName(node1,QString("type"))) {
	    		 qDebug() << "ConfigReaderUtil::getHostModel# first element isn't type " << endl;
	    		 return NULL;
	    	 }
	    	 model->setType(new QString(XmlParserHelper::getElementText(node1)));

	    	 QDomNode node2 = node1.nextSibling (); // <host>
	    	 if (!XmlParserHelper::checkNodeName(node2,QString("host"))) {
	    	     qDebug() << "ConfigReaderUtil::getHostModel# second element isn't host " << endl;
	    	     return NULL;
	    	 }
	    	 model->setHost(new QString(XmlParserHelper::getElementText(node2)));

	    	 QDomNode node3 = node2.nextSibling (); // <port>
	    	 if (!XmlParserHelper::checkNodeName(node3,QString("port"))) {
	    	   	qDebug() << "ConfigReaderUtil::getHostModel# 3 element isn't port " << endl;
	    	   	return NULL;
	    	 }
	    	 model->setPort(XmlParserHelper::getElementText(node3).toInt());

	    	 QDomNode node4 = node.nextSibling (); // <pokerRooms>
	    	 if (!(QString("pokerRooms").compare(node4.nodeName()) == 0)) {
	    	 	qDebug() << "ConfigReaderUtil::getHostModel# pokerRooms element is missing " << endl;
	    	   	return NULL;
	    	 }
	    	 QDomNode node5 = node4.firstChild(); // pokerRoom
	         QList<PokerRoomModel*>* pokerRoomList = new QList<PokerRoomModel*>();

	      if (!node5.isNull()){
    		 PokerRoomModel* room = new PokerRoomModel();
    		 QDomNode idNode = node5.firstChild();// id
    		 if (!(QString("id").compare(idNode.nodeName()) == 0)) {
    			qDebug() << "ConfigReaderUtil::getHostModel# should be id " << endl;
    		    return NULL;
    		 }
    		 QString id = XmlParserHelper::getElementText(idNode);
    		 room->setId(id.toInt());

    		 QDomNode node6 = idNode.nextSibling();// name
    		 if (!(QString("name").compare(node6.nodeName()) == 0)) {
    			qDebug() << "ConfigReaderUtil::getHostModel# should be name " << endl;
    		    return NULL;
    		 }
    		 QDomElement domElement5 = node6.toElement();
    		 QString* name = new QString(domElement5.text());
    		 room->setName(name);

    		 QDomNode node7 = domElement5.nextSibling(); // type
    		 if (!(QString("type").compare(node7.nodeName()) == 0)) {
    			qDebug() << "ConfigReaderUtil::getHostModel# should be type " << endl;
    		    return NULL;
    		 }
    		 QDomElement domElement6 = node7.toElement();
    		 QString* type = new QString(domElement6.text());
    		 room->setType(type);

    		 QDomNode node8 = domElement6.nextSibling(); // maxPlayers
    		 if (!(QString("maxPlayers").compare(node8.nodeName()) == 0)) {
    		 	qDebug() << "ConfigReaderUtil::getHostModel# sholud be maxPlayers " << endl;
    		    return NULL;
    		 }
    		 QDomElement domElement7 = node8.toElement();
    		 room->setMaxPlayers(domElement7.text().toInt());

    		 pokerRoomList->append(room);
    		 while(!(node5 = node5.nextSibling()).isNull()){// pokerRoom
        		 PokerRoomModel* room1 = new PokerRoomModel();
        		 idNode = node5.firstChild();// id
        		 if (!(QString("id").compare(idNode.nodeName()) == 0)) {
    		     	qDebug() << "ConfigReaderUtil::getHostModel# sholud be id " << endl;
       		     	return NULL;
        		 }
        		 QString id2 = XmlParserHelper::getElementText(idNode);
        		 room1->setId(id2.toInt());

        		 node6 = idNode.nextSibling(); // name
        		 if (!(QString("name").compare(node6.nodeName()) == 0)) {
        			qDebug() << "ConfigReaderUtil::getHostModel# sholud be name tag " << endl;
        		    return NULL;
        		 }
        		 domElement5 = node6.toElement();
        		 QString* name = new QString(domElement5.text());
        		 room1->setName(name);

        		 node7 = domElement5.nextSibling(); // type
        		 if (!(QString("type").compare(node7.nodeName()) == 0)) {
        			qDebug() << "ConfigReaderUtil::getHostModel# sholud be type " << endl;
        		    return NULL;
        		 }

        		 domElement6 = node7.toElement();
        		 QString* type = new QString(domElement6.text());
        		 room1->setType(type);
        		 node8 = domElement6.nextSibling(); // maxPlayers
        		 if (!(QString("maxPlayers").compare(node8.nodeName()) == 0)) {
        		 	qDebug() << "ConfigReaderUtil::getHostModel# sholud be maxPlayers " << endl;
        		    return NULL;
        		 }
        		 domElement7 = node8.toElement();
        		 room1->setMaxPlayers(domElement7.text().toInt());
        		 pokerRoomList->append(room1);
    		 }
    	 }
    	 model->setPokerRoomList(pokerRoomList);
    }
    else {
    	qDebug() << "ConfigReaderUtil::getHostModel() Invalid xml !!!" << endl;
    }
	return model;
}
