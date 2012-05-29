#ifndef AUTHINFOMODEL_H
#define AUTHINFOMODEL_H
#include <QObject>
#include <QString>
#include "src/model/PokerPlayerModel.h"

class AuthInfoModel : public QObject
{
	Q_OBJECT
public:
	AuthInfoModel(QObject *parent = 0);
	bool isAuthenticated();
	PokerPlayerModel* getPlayerModel() const;
	void setPokerPlayer(PokerPlayerModel* model);
	void setAuth(bool auth);
	QString* getName() const;
	quint16 getMoney() const;

private:
	PokerPlayerModel* playerModel;
	bool auth;
};
#endif
