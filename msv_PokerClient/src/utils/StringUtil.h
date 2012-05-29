#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include <QString>

class StringUtil
{
public:
	StringUtil();
	static bool isEquals(QString str1, QString str2); // returns true if str1 equals to str2
	static QString valueOf(bool someBool);
	static QString valueOf(quint16 someInteger);
	static bool valueOf(QString str);
	static QString getStringWithLenth(int length,QString str);
	static QString wrapWord(int length, QString str);
};
#endif
