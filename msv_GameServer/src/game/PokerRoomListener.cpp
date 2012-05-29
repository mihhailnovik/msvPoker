#include "src/game/PokerRoomListener.h"
#include "src/game/TexasHoldemPokerGame.h"
#include "src/utils/MessageTransformer.h"
#include "src/utils/MessageSenderUtil.h"
#include "src/utils/MessageBuilder.h"
#include <QDebug>
#include <QString>

PokerRoomListener::PokerRoomListener(PokerRoomModel* room) {
	m_nNextBlockSize = 0;
	this->room = room;
	QString id;
	id.setNum(room->getId());
	this->id = id;
	init();
}

PokerRoomListener::~PokerRoomListener(){
}

void PokerRoomListener::gameEnded(){
	disconnect(game,SIGNAL(gameEnded()),this,SLOT(gameEnded()));
	disconnect(game,SIGNAL(sendMessage(QString*,PokerPlayerModel*)),this,SLOT(sendMessage(QString*,PokerPlayerModel*)));
	game = new TexasHoldemPokerGame(room);
	connect(game,SIGNAL(gameEnded()),this,SLOT(gameEnded()));
	connect(game,SIGNAL(sendMessage(QString*,PokerPlayerModel*)),this,SLOT(sendMessage(QString*,PokerPlayerModel*)));
	roomReady();
}

void PokerRoomListener::roomReady(){
	qDebug() << "PokerRoomListener::roomReady# ready signal received" << endl;
	if (!(game->isRunning())) {
		qDebug() << "PokerRoomListener::roomReady# Room is ready to start game !!!" << endl;
		game->start();
	}
}

void PokerRoomListener::init() {
	if (room->getType()->compare("Texas Holdem") == 0) {
		game = new TexasHoldemPokerGame(room);
		connect(game,SIGNAL(gameEnded()),this,SLOT(gameEnded()));
		connect(game,SIGNAL(sendMessage(QString*,PokerPlayerModel*)),this,SLOT(sendMessage(QString*,PokerPlayerModel*)));
		connect(room,SIGNAL(ready()),this,SLOT(roomReady()));
		connect(room,SIGNAL(playerJoined(PokerPlayerModel*)),this,SLOT(slotPlayerJoined(PokerPlayerModel*)));
		return;
	}
	qDebug() << "PokerRoomListener::init# Warning, thread is broken, unknown poker type !!!" << endl;
}

void PokerRoomListener::slotPlayerJoined(PokerPlayerModel* player) {
	qDebug() << "PokerRoomListener::slotPlayerJoined# player "<<*(player->getName())<<" joined " << endl;
	connectSignal(player->getSocket());
}

void PokerRoomListener::setId(QString id){
	this->id = id;
}

QString PokerRoomListener::getId() const{
	return id;
}

void PokerRoomListener::connectSignal(QTcpSocket* pClientSocket){
	 connect(pClientSocket, SIGNAL(disconnected()),
	            this, SLOT(slotClientDisconnect())
	           );
	 connect(pClientSocket, SIGNAL(readyRead()),
	            this, SLOT(slotReadClient())
	           );
}

void PokerRoomListener::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    	QDataStream in(pClientSocket);
        in.setVersion(QDataStream::Qt_4_2);
        for (;;) {
            if (!m_nNextBlockSize) {
                if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                    break;
                }
                in >> m_nNextBlockSize;
            }
            if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
                break;
            }
            QString str;
            in >> str;
            m_nNextBlockSize = 0;
    		MsvClientMessage* clientMessage = MessageTransformer::transformClientMessage(new QString(str));
    		processMessage(clientMessage,getPlayerBySocket(pClientSocket->socketDescriptor()));
        }
}

void PokerRoomListener::processMessage(MsvClientMessage* clientMessage,PokerPlayerModel* player) {
	if (clientMessage->isJoinChair()&& clientMessage->getJoinChairInfoModel() != NULL) {
		QString chair;
		chair.setNum(clientMessage->getJoinChairInfoModel()->getChairId());
		MessageSenderUtil::sendMessage(MessageBuilder::buildPlayerJoinedChair(chair,player),room->getPlayerList());
		qDebug() << "PokerRoomListener::processMessage# Player "<< *(player->getName()) << " joined chair " << endl;
		room->joinTable(clientMessage->getJoinChairInfoModel()->getChairId(),player);
		return;
	}
	if (clientMessage->isBet()) {
		qDebug() << "PokerRoomListener::processMessage# bet message received " << endl;
		player->addMessage(clientMessage);
		return;
	}
	qDebug() << "PokerRoomListener::processMessage# WARNING!!! can't undestand message, unknown format" << endl;
}

void PokerRoomListener::slotClientDisconnect() {
	qDebug() << "PokerRoomListener::slotClientDisconnect# client disconnect " << endl;
}

PokerPlayerModel* PokerRoomListener::getPlayerBySocket(quint16 socketDesk) {
	for (int i=0;i<room->getPlayerList()->size();i++){
		PokerPlayerModel* player = room->getPlayerList()->at(i);
		if (player->getSocket()->socketDescriptor() == socketDesk) {
			return player;
		}
	}
	qDebug() << "PokerRoomListener::getPlayerBySocket# WARNING Player not found, please relook" << endl;
	return NULL;
}

void PokerRoomListener::sendMessage(QString* message, PokerPlayerModel* player) {
	MessageSenderUtil::sendMessage(message,player);
}
