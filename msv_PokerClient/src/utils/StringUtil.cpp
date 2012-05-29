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

bool StringUtil::valueOf(QString str) {
	return isEquals("true",str);
}

QString StringUtil::valueOf(quint16 someInteger){
	QString ret;
	ret.setNum(someInteger);
	return ret;
}

QString StringUtil::wrapWord(int length, QString str) {
	if (length == str.length() && str.length() > length) {
		return str;
	}
	int difference = length - str.length();
	int halfDifference = difference / 2;
	bool indivisibleHalf = ((difference % 2)==1);
	return "<font size=5 color='darkblue'>" + getStringWithLenth(halfDifference,"_") + "</font><font size=5 color='red'>" + str + "</font><font size=5 color='darkblue'>"+getStringWithLenth(halfDifference,"_")+"</font>";
}

QString StringUtil::getStringWithLenth(int length,QString str) {
	QString result;
	for (int i=0;i<length;i++){
		result += str;
	}
	return result;
}
