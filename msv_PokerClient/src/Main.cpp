#include <QApplication>
#include <QDebug>
#include <QHostAddress>
#include "src/gui/LoginWidget.h"
#include "src/utils/SocketHolder.h"
#include "src/utils/ServiceHolder.h"
#include "src/model/MsvEnvironment.h"
int main(int argc, char *argv[])
    {
		QApplication app(argc, argv);
        SocketHolder* socketHolder = new SocketHolder();
        socketHolder->connectToHost(QHostAddress::LocalHost,7777);
        ServiceHolder* serviceHolder = new ServiceHolder(socketHolder);
        MsvEnvironment* env = new MsvEnvironment();
        env->setServiceHolder(serviceHolder);
        LoginWidget login(NULL,env);
        login.show();
        return app.exec();
    }
