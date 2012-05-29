#ifndef MESSAGEBUILDER_H
#define MESSAGEBUILDER_H
#include <QString>

class MessageBuilder
{
public:
	MessageBuilder();
	static QString buildAuthenticationMessage(QString login, QString password);
	static QString buildGetServerInfoMessage();
	static QString buildJoinTableMessage(QString tableId);
	static QString buildTakeSeatMessage(QString chairId);
	static QString buildGameAction(int sum);
};
#endif
