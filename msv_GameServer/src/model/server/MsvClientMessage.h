#ifndef MSVCLIENTMESSAGE_H
#define MSVCLIENTMESSAGE_H
#include <QString>
#include <QObject>
#include "src/model/server/JoinTableInfoModel.h"
#include "src/model/server/AuthInfoModel.h"
#include "src/model/server/GameActionModel.h"
#include "src/model/server/JoinChairInfoModel.h"
/*
	client message model
*/
class MsvClientMessage:public QObject {
	Q_OBJECT
public:
	MsvClientMessage(QObject *parent = 0);
	~MsvClientMessage();
	QString* getType() const;
	void setType(QString* tyoe);
	bool isInfoMessage() const;
	bool isJoinTable() const;
	bool isAuthentication() const;
	bool isGameAction() const;
	bool isJoinChair() const;
	bool isBet() const;
	JoinTableInfoModel* getJoinTableModel() const;
	void setJoinTableModel(JoinTableInfoModel* model);
	AuthInfoModel* getAuthInfoModel() const;
	void setAuthInfoModel(AuthInfoModel* model);
	GameActionModel* getGameActionModel() const;
	void setGameActionModel(GameActionModel* model);
	JoinChairInfoModel* getJoinChairInfoModel() const;
	void setJoinChairInfoModel(JoinChairInfoModel* model);
	int getBet() const;
	void setBet(int);
private:
	QString* type;
	JoinTableInfoModel* joinTableModel;
	AuthInfoModel* authInfo;
	JoinChairInfoModel* joinChairModel;
	GameActionModel* actionModel;
	int bet;
};
#endif
