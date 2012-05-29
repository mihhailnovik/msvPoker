#ifndef POKERHOSTMODEL_H
#define POKERHOSTMODEL_H
#include <QString>
#include <QList>
#include <QObject>
#include "src/model/server/PokerRoomModel.h"

class PokerHostModel:public QObject {
	Q_OBJECT
	public:
		~PokerHostModel();
		PokerHostModel(QObject *parent = 0);
		QString* getHost() const;
		QString* getType() const;
		void setType(QString* type);
		void setHost(QString* host);
		quint16 getPort() const;
		void setPort(quint16 port);
		QList<PokerRoomModel*>* getPokerRoomList() const;
		void setPokerRoomList(QList<PokerRoomModel*>* list);
		quint16 getTimeOut();
		void setTimeOut(quint16 timeout);
	private: 
		QString* type;
		QString* host;
		quint16 port;
		QList<PokerRoomModel*>* pokerRoomList;
		quint16 timeout;
};
#endif
