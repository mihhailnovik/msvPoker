#ifndef CONFIGREADERUTIL_H
#define CONFIGREADERUTIL_H
#include "src/model/server/PokerHostModel.h"
/*
 * @author rdir52_msv team
 * Returns config objects
 */
class ConfigReaderUtil {
public:
	static PokerHostModel* getHostModel();
};
#endif
