#include <QApplication>
#include <QDebug>
#include "src/game/GameHost.h"

	int main(int argc, char *argv[])
    {
        QApplication app(argc, argv);
        GameHost host;
        return app.exec();
    }
