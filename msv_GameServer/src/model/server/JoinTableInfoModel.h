#ifndef JOINTABLEINFOMODEL_H
#define JOINTABLEINFOMODEL_H
#include <QObject>
class JoinTableInfoModel : public QObject {
	Q_OBJECT
	public:
		JoinTableInfoModel(QObject *parent = 0);
		~JoinTableInfoModel();
		quint16 getBuyInSumma() const;
		quint16 getTableId() const;
		void setBuyInSumma(quint16 buyInSumma);
		void setTableId(quint16 tableId);
private:
		quint16 tableId;
		quint16 buyInSumma;
};
#endif
