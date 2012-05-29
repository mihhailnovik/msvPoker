#ifndef JOINCHAIRINFOMODEL_H
#define JOINCHAIRINFOMODEL_H
#include <QObject>
class JoinChairInfoModel : public QObject {
	Q_OBJECT
	public:
		JoinChairInfoModel(QObject *parent = 0);
		~JoinChairInfoModel();
		void setChairId(quint16);
		quint16 getChairId() const;
	private:
		quint16 chairId;
};
#endif
