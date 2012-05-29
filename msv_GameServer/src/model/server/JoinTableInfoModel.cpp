#include "src/model/server/JoinTableInfoModel.h"

JoinTableInfoModel::JoinTableInfoModel(QObject *parent) : QObject(parent)
{
}

JoinTableInfoModel::~JoinTableInfoModel()
{

}

void JoinTableInfoModel::setTableId(quint16 tableId)
{
	this->tableId = tableId;
}

void JoinTableInfoModel::setBuyInSumma(quint16 buyInSumma)
{
	this->buyInSumma=buyInSumma;
}

quint16 JoinTableInfoModel::getBuyInSumma() const
{
	return buyInSumma;
}

quint16 JoinTableInfoModel::getTableId() const
{
	return tableId;
}
