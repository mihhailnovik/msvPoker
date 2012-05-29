#ifndef AUTHINFOMODEL_H
#define AUTHINFOMODEL_H
#include <QString>
#include <QObject>

class AuthInfoModel : public QObject {
Q_OBJECT
public:
	AuthInfoModel(QObject *parent = 0);
	AuthInfoModel(QString* login, QString* pass);
	~AuthInfoModel();
	QString* getPass() const;
	QString* getLogin() const;
	void setPass(QString* pass);
	void setLogin(QString* login);
private:
	QString* login;
	QString* pass;
};
#endif
