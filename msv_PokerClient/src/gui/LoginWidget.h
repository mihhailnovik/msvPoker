#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "src/service/LoginService.h"
#include "src/model/MsvEnvironment.h"

class LoginWidget : public QWidget
{
	Q_OBJECT
public:
	LoginWidget(QWidget *parent = 0, MsvEnvironment* env = 0);
	void keyPressEvent(QKeyEvent* pe);
public slots:
	void login();
	void newAccount();
	void loginSuccesful(PokerPlayerModel* authenticatedPlayer);
	void loginFailed();
private:
    QLineEdit *loginEdit;
    QLabel *loginLabel;
    QLineEdit *passwordEdit;
    QLabel *passwordLabel;
    QPushButton* connectButton;
    QPushButton* newAccountButton;
    LoginService* loginService;
    MsvEnvironment* environment;
};
#endif
