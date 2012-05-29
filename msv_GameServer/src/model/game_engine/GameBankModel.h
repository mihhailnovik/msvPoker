#ifndef GAME_BANK_MODEL_H
#define GAME_BANK_MODEL_H
#include <QObject>
#include <QList>
/**
 * @author rdir52_msv team
 */

class GameBankModel: public QObject {
	Q_OBJECT
public:
	GameBankModel();
	GameBankModel(const GameBankModel &);
	~GameBankModel();
	void add(quint16 amount);
	quint16 getMoney() const;

private:
	quint16 bank;
};
#endif
