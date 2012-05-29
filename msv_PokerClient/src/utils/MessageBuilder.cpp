#include "src/utils/MessageBuilder.h"
//XXX Xml hardcode not best desicion
MessageBuilder::MessageBuilder()
{
}

QString MessageBuilder::buildAuthenticationMessage(QString login, QString password){
	QString message("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	message.append("<msvClientMessage>");
		message.append("<type>");
			message.append("authentication");
		message.append("</type>");
		message.append("<authInfo>");
			message.append("<login>");
				message.append(login);
			message.append("</login>");
			message.append("<pass>");
				message.append(password);
			message.append("</pass>");
		message.append("</authInfo>");
	message.append("</msvClientMessage>");
	return message;
}

QString MessageBuilder::buildGetServerInfoMessage(){
	QString message("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		message.append("<msvClientMessage>");
			message.append("<type>");
				message.append("get_info");
			message.append("</type>");
		message.append("</msvClientMessage>");
	return message;
}

QString MessageBuilder::buildJoinTableMessage(QString tableId) {
	QString message("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		message.append("<msvClientMessage>");
			message.append("<type>");
				message.append("join_table");
			message.append("</type>");

			message.append("<joinTableInfo>");
				message.append("<table_id>");
					message.append(tableId);
				message.append("</table_id>");

			message.append("</joinTableInfo>");
		message.append("</msvClientMessage>");
	return message;
}

QString MessageBuilder::buildTakeSeatMessage(QString chairId) {
	QString message("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		message.append("<msvClientMessage>");
			message.append("<type>");
				message.append("join_chair");
			message.append("</type>");

			message.append("<joinChairInfo>");
				message.append("<chair_id>");
					message.append(chairId);
				message.append("</chair_id>");
			message.append("</joinChairInfo>");

		message.append("</msvClientMessage>");
	return message;
}

QString MessageBuilder::buildGameAction(int sum) {
	QString message("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		message.append("<msvClientMessage>");
			message.append("<type>");
				message.append("bet");
			message.append("</type>");

			message.append("<bet>");
				message.append(QString::number(sum));
			message.append("</bet>");
			message.append("</msvClientMessage>");
	return message;
}
