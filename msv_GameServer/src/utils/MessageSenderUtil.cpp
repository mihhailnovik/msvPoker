#include "src/utils/MessageSenderUtil.h"


void MessageSenderUtil::sendMessage(QString* message, QList<PokerPlayerModel*>* playerList){
	for (int i=0;i<playerList->size();i++){
		sendMessage(message,playerList->at(i));
	}
}

void MessageSenderUtil::sendMessage(QString* message, QMap<quint16,PokerPlayerModel*>* playerList){
	sendMessage(message,&playerList->values());
}

void MessageSenderUtil::sendMessage(QString* message, PokerPlayerModel* player){
	qDebug() << "MessageSenderUtil::sendMessage# server -> " << *(player->getName()) << *(message) << endl;
	player->lock();
	sendMessage(player->getSocket(),*(message));
	player->unlock();
}

void MessageSenderUtil::sendMessage(QTcpSocket* pSocket, const QString &data){
	QByteArray  arrBlock;
	QDataStream out(&arrBlock, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_2);
	out << quint16(0) << data;
	out.device()->seek(0);
	out << quint16(arrBlock.size() - sizeof(quint16));
	pSocket->write(arrBlock);
}
