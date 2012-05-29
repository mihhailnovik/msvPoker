#include "src/model/server/JoinChairInfoModel.h"

JoinChairInfoModel::JoinChairInfoModel(QObject *parent) : QObject(parent)
{
}

JoinChairInfoModel::~JoinChairInfoModel()
{

}

void JoinChairInfoModel::setChairId(quint16 chairId) {
	this->chairId = chairId;
}
quint16 JoinChairInfoModel::getChairId() const {
	return chairId;
}
