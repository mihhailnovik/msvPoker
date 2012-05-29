#include "src/utils/StringUtil.h"
#include <QDebug>
StringUtil::StringUtil()
{
}

bool StringUtil::isEquals(QString str1, QString str2) {
	return str1.compare(str2) == 0;
}

QString StringUtil::valueOf(bool someBoolean){
	if (someBoolean) {
		return "true";
	}
	return "false";
}

QString StringUtil::valueOf(int someInteger){
	QString ret;
	ret.setNum(someInteger);
	return ret;
}
