#ifndef XMLPARSERHELPER_H
#define XMLPARSERHELPER_H
#include <QString>
#include <QDomNode>

class XmlParserHelper
{
public:
	XmlParserHelper();
	static bool checkNodeName(QDomNode domNode,QString expectedName); // returns true if domNode name is equals with expextedName
	static bool isEquals(QString str1, QString str2); // returns true if str1 equals to str2
	static QString getElementText(QDomNode domNode); // return domNode text
};
#endif
