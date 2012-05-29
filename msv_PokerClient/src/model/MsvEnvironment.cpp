#include "src/model/MsvEnvironment.h"

MsvEnvironment::MsvEnvironment(QObject *parent)
    : QObject(parent)
{

}

ServiceHolder* MsvEnvironment::getServiceHolder() const {
	return serviceHolder;
}

void MsvEnvironment::setServiceHolder(ServiceHolder* serviceHolder) {
	this->serviceHolder = serviceHolder;
}

PokerPlayerModel* MsvEnvironment::getAuthenticatedPlayer() const {
	return authenticatedPlayer;
}

void MsvEnvironment::setAuthenticatedPlayer(PokerPlayerModel* authenticatedPlayer){
	this->authenticatedPlayer = authenticatedPlayer;
}
