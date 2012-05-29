#ifndef BETMODEL_H
#define BETMODEL_H
#include <QObject>
class BetModel : public QObject {
	Q_OBJECT
public:
	BetModel(QObject *parent = 0);
	~BetModel();
	quint16 getBuyInMin() const;
	quint16 getBuyInMax() const;
	quint16 getBigBlind() const;
	quint16 getSmallBlind() const;
	quint16 getMinRaisePercent() const;
	quint16 getMaxRaisePercent() const;

	void setBuyInMin(quint16 buyInMin);
	void setBuyInMax(quint16 buyInMax);
	void setBigBlind(quint16 bigBlind);
	void setSmallBlind(quint16 smallBlind);
	void setMinRaisePercent(quint16 minRaisePercent);
	void setMaxRaisePercent(quint16 maxRaisePercent);
private:
	quint16 buyInMax;
	quint16 buyInMin;
	quint16 bigBlind;
	quint16 smallBlind;
	quint16 maxRaisePercent;
	quint16 minRaisePercent;
};
#endif
