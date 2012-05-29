#include "src/game/GameHost.h"
#include "src/utils/ConfigReaderUtil.h"
#include "src/utils/MessageTransformer.h"
#include "src/utils/MessageBuilder.h"
#include "src/model/server/MsvClientMessage.h"
#include "src/server/SingleThreadServer.h"
#include "src/game/PokerRoomListener.h"
#include <QHostAddress>
#include <QObject>
#include <QTcpSocket>
#include <QMapIterator>

	GameHost::GameHost(QObject *parent) : QObject(parent){
		init();
	}
	
	GameHost::~GameHost() {
		delete authService;
		delete server;
		delete playersMap;
		delete pokerRoomMap;
		delete pokerHostModel;
	}

	void GameHost::init() {
		/********************** Configuration *******************************/
		qDebug() << "GameHost::init() loading config" << endl;
		pokerHostModel = ConfigReaderUtil::getHostModel();
		if (pokerHostModel->getType()->compare("SingleThread") == 0){
			server = new SingleThreadServer();
		}
		authService = new AuthenticationService();
		playersMap = new QMap<quint16, PokerPlayerModel*>();
		pokerRoomMap = new QMap<quint16,PokerRoomModel*>();
		QList<PokerRoomModel*>* pokerRoomList = pokerHostModel->getPokerRoomList();

		for (int i = 0;i<pokerRoomList->size();i++) {
			quint16 roomId = pokerRoomList->at(i)->getId();
			QString roomIdStr;
			roomIdStr.setNum(roomId);
			qDebug() << "GameHost::init() pokerRoom "<< *(pokerRoomList->at(i)->getName()) << "loaded (id = " << roomIdStr << ")"<< endl;
			pokerRoomMap->insert(pokerRoomList->at(i)->getId(),pokerRoomList->at(i));
		}
		/*********************************************************************/

		/*********************** Connections *********************************/
		connect(server,SIGNAL(dataReaded(const QString*,QTcpSocket*)),this,SLOT(dataReaded(const QString*,QTcpSocket*)));
		QMapIterator<quint16, PokerRoomModel*> i(*pokerRoomMap);
		while (i.hasNext()) { // Starting threads
		     i.next();
		     PokerRoomListener* listener = new PokerRoomListener(i.value());
		}
		/**********************************************************************/
		startServer();
	}

	void GameHost::startServer(){
		if (server->isListening()) {
			qDebug() << tr("GameHost::startServer()# Server already running ") << endl;
			return;
		}
		if (!server->listen(*(new QHostAddress(*(pokerHostModel->getHost()))),pokerHostModel->getPort())) {
			qDebug() << tr("GameHost::startServer()# Can't start server ") << endl;
		}
		qDebug() << tr("GameHost::startServer()# Server started and listening port ") << pokerHostModel->getPort() << endl;

	}
	
	void GameHost::dataReaded(const QString* str, QTcpSocket* socket) {
		MsvClientMessage* receivedMessage = MessageTransformer::transformClientMessage(str);
		qDebug() << tr("GameHost::dataReaded# Processing client message..") << endl;

		if (!receivedMessage) {
			qDebug() << tr("GameHost::dataReaded# Warning can't get client message..") << endl;
			sendUnknowMessageFormatError(socket);
			return;
		}

		if (receivedMessage->isAuthentication()) {
			if (receivedMessage->getAuthInfoModel() == NULL) {
				sendUnknowMessageFormatError(socket);
				return;
			}
			PokerPlayerModel* player = authService->authenticate(*(receivedMessage->getAuthInfoModel()->getLogin()), *(receivedMessage->getAuthInfoModel()->getPass()));
			if (player != NULL) {
				qDebug() << tr("GameHost::dataReaded# player ") << *(receivedMessage->getAuthInfoModel()->getLogin()) << tr(" authenticated ") << endl;
				player->setSocket(socket);
				playersMap->insert(socket->socketDescriptor(),player);
				server->sendData(socket,*(MessageBuilder::buildAuthenticationOkResponse(player)));
			} else {
				qDebug() << tr("GameHost::dataReaded# player ") << *(receivedMessage->getAuthInfoModel()->getLogin()) << tr(" authentication failed with password ") << *(receivedMessage->getAuthInfoModel()->getPass()) << endl;
				server->sendData(socket,*(MessageBuilder::buildAuthenticationFailedResponse(receivedMessage->getAuthInfoModel())));
			}
			return;
		}

		if (receivedMessage->isInfoMessage()) { // if client want to get info about server, then we send that info to him
			qDebug() << "GameHost::dataReaded# Building server info message..." << endl;
			server->sendData(socket,*(MessageBuilder::buildServerInfoResponse(pokerHostModel)));
			qDebug() << tr("GameHost::dataReaded# Server info sent to client ") << endl;
			return;
		}

		if (receivedMessage->isJoinTable()) { // if client want to join table, then we should check is table free
			qDebug() << "GameHost::dataReaded# JoinTable info message..." << endl;
			if (receivedMessage->getJoinTableModel() == NULL) {
				sendUnknowMessageFormatError(socket);
				return;
			}
			qDebug() << "GameHost::dataReaded# tableId = " << receivedMessage->getJoinTableModel()->getTableId() << " player = " << *(playersMap->value(socket->socketDescriptor())->getName()) << endl;
			server->sendData(socket, *(MessageBuilder::buildTableJoinSuccessfully(pokerRoomMap->value(receivedMessage->getJoinTableModel()->getTableId()))));
			joinTable(receivedMessage->getJoinTableModel()->getTableId(),playersMap->value(socket->socketDescriptor()));
			return;
		}
		qDebug() << "GameHost::dataReaded# Warning message received but, not processed, unknow type !!!" << endl;
	}

	void GameHost::joinTable(quint16 tableId, PokerPlayerModel* player) {
		pokerRoomMap->value(tableId)->addPlayer(player);
		server->disconnectSignal(player->getSocket());
		qDebug() << "GameHost::joinTable# player " << *(player->getName()) << "added to pokerroom" << endl;
	}

	void GameHost::sendUnknowMessageFormatError(QTcpSocket* socket){
		qDebug() << tr("GameHost::sendUnknowMessageFormatError# Warning ! Client message format is invalid") << endl;
		server->sendData(socket,*(MessageBuilder::buildUnknownMessageFormatResponse()));
	}

