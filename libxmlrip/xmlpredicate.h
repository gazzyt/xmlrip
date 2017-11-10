#ifndef XMLPREDICATE_H
#define XMLPREDICATE_H

#include <memory>
#include <string>

#include "xmlelement.h"

class XmlPredicate
{
public:
	XmlPredicate(std::string tagName, std::unique_ptr<XmlAttribute> attributePredicate = std::unique_ptr<XmlAttribute>());
	XmlPredicate(const XmlPredicate& rhs);

public:
	bool IsMatch(const XmlElement& elem) const;
	const std::string& GetTagName() const;
	const XmlAttribute* GetAttributePredicate() const;

private:
	std::string m_tagName;
	std::unique_ptr<XmlAttribute> m_attributePredicate;
};

#endif