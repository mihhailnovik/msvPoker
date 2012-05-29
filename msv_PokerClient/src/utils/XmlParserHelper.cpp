#include "src/utils/XmlParserHelper.h"
#include <QDebug>
XmlParserHelper::XmlParserHelper()
{
}

bool XmlParserHelper::checkNodeName(QDomNode domNode,QString expectedName) {
	if (domNode.isNull()){
		return false;
	}
	return isEquals(expectedName,domNode.nodeName());
}

bool XmlParserHelper::isEquals(QString str1, QString str2) {
	return str1.compare(str2) == 0;
}

QString XmlParserHelper::getElementText(QDomNode domNode) {
	if (domNode.isNull()) {
		qDebug() << "MessageTransformer::getElementText domNode is null";
	}
	return domNode.toElement().text();
}
