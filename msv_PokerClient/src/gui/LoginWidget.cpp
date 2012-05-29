#include "src/gui/LoginWidget.h"
#include "src/gui/TableChoseWidget.h"
#include "src/model/PokerPlayerModel.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QKeyEvent>

LoginWidget::LoginWidget(QWidget *parent,MsvEnvironment* environment)
     : QWidget(parent)
{
	this->environment = environment;
	loginEdit = new QLineEdit;
	loginLabel = new QLabel(tr("Username :"));
	passwordEdit = new QLineEdit;
	passwordEdit->setEchoMode(QLineEdit::Password);
	passwordLabel = new QLabel(tr("Password :"));

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(loginLabel, 0, 0);
    mainLayout->addWidget(loginEdit, 0, 1);
    mainLayout->addWidget(passwordLabel, 1, 0);
    mainLayout->addWidget(passwordEdit, 1, 1);

    connectButton = new QPushButton(tr("Login"));
    connect(connectButton, SIGNAL(clicked()), this, SLOT(login()));
    newAccountButton = new QPushButton(tr("Create account"));
    connect(newAccountButton, SIGNAL(clicked()), this, SLOT(newAccount()));

    mainLayout->addWidget(connectButton,2,0);
    mainLayout->addWidget(newAccountButton,2,1);

    setLayout(mainLayout);
    setWindowTitle(tr("Please login"));

    loginService = environment->getServiceHolder()->getLoginService();
}

void LoginWidget::login(){
	qDebug() << "LoginWidget::login# Login button submited " << endl;
	connect(loginService,SIGNAL(loginFailed()),this,SLOT(loginFailed()));
	connect(loginService,SIGNAL(loginSuccesful(PokerPlayerModel*)),this,SLOT(loginSuccesful(PokerPlayerModel*)));
    loginService->login(loginEdit->text(),passwordEdit->text());
}

void LoginWidget::newAccount(){
	// TODO this isn't necceseary at all at this moment
    QMessageBox::information(this, tr("Not implemented yet"),
        tr("Not implemented yet!!"));
}

void LoginWidget::loginSuccesful(PokerPlayerModel* authenticatedPlayer){
	qDebug() << "LoginWidget::loginSuccesful# Login succesfull " << endl;
	environment->setAuthenticatedPlayer(authenticatedPlayer);
	TableChoseWidget* tableChoseWidget = new TableChoseWidget(environment);
    tableChoseWidget->show();
	disconnect(loginService,SIGNAL(loginFailed()),this,SLOT(loginFailed()));
	disconnect(loginService,SIGNAL(loginSuccesful(PokerPlayerModel*)),this,SLOT(loginSuccesful(PokerPlayerModel*)));
    this->hide();
}

void LoginWidget::loginFailed(){
	qDebug() << "LoginWidget::loginFailed# Login failed " << endl;
	QMessageBox::information(this, tr("Authentication failed"),
	            tr("The username or password you entered is incorrect"));
	disconnect(loginService,SIGNAL(loginFailed),this,SLOT(loginFailed()));
	disconnect(loginService,SIGNAL(loginSuccesful(PokerPlayerModel*)),this,SLOT(loginSuccesful(PokerPlayerModel*)));
}

void LoginWidget::keyPressEvent(QKeyEvent* pe) {
	switch(pe->key()) {
		case Qt::Key_Enter: login();break;
		case 16777220:login();break;
	}
}
