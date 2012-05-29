#ifndef MESSAGESENDERUTIL_H
#define MESSAGESENDERUTIL_H

#include <QString>
#include <QList>
#include <QMap>
#include <QTcpSocket>
#include "src/model/server/PokerPlayerModel.h"
/*
 * @author rdir52_msv team
 */
class MessageSenderUtil {

public:
	static void sendMessage(QString* message, QList<PokerPlayerModel*>* playerList);
	static void sendMessage(QString* message, QMap<quint16,PokerPlayerModel*>* playerList);
	static void sendMessage(QString* message, PokerPlayerModel* playerList);
	static void sendMessage(QTcpSocket* pSocket, const QString &data);
};

#endif
