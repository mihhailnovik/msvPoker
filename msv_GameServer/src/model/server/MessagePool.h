#ifndef ROOMMESSAGEPOOL_H
#define ROOMMESSAGEPOOL_H
#include <QObject>

/**
 * All game messages, which was sended by player will be saved there,
 * game logic should check this pool to get a message from client. All methods should be synchornized
 * @author rdir52_msv team
 */
class MessagePool : public QObject {
	Q_OBJECT
public:
	MessagePool(QObject *parent = 0);
	~MessagePool();

private:

};
#endif
