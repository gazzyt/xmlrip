#ifndef XMLPREDICATE_H
#define XMLPREDICATE_H

#include <string>

#include "xmlelement.h"

class XmlPredicate
{
public:
	XmlPredicate(std::string tagName);

public:
	bool IsMatch(const XmlElement& elem) const;
	const std::string& GetTagName() const;

private:
	std::string m_tagName;
};

#endif