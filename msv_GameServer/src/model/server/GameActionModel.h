#ifndef GAMEACTIONMODEL_H
#define GAMEACTIONMODEL_H
#include <QString>
#include <QObject>
class GameActionModel:public QObject {
	Q_OBJECT
public:
	GameActionModel(QObject *parent = 0);
	~GameActionModel();
};
#endif
