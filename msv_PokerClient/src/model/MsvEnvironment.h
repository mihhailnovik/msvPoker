#ifndef MSVENVIRONMENT_H
#define MSVENVIRONMENT_H
#include <QObject>
#include "src/utils/ServiceHolder.h"
#include "src/model/PokerPlayerModel.h"
/*
 * Stores environment of current session
 */
class MsvEnvironment : public QObject
{
	Q_OBJECT
public:
	MsvEnvironment(QObject *parent = 0);
	ServiceHolder* getServiceHolder() const;
	void setServiceHolder(ServiceHolder* serviceHolder);
	PokerPlayerModel* getAuthenticatedPlayer() const;
	void setAuthenticatedPlayer(PokerPlayerModel* model);

private:
	ServiceHolder* serviceHolder;
	PokerPlayerModel* authenticatedPlayer;
};
#endif
