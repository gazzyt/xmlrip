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
	template<class T> bool IsMatch(const char* tagName, const T& attributes) const;
	const std::string& GetTagName() const;
	const XmlAttribute* GetAttributePredicate() const;

	static XmlPredicate FromText(std::string text);

private:
	std::string m_tagName;
	std::unique_ptr<XmlAttribute> m_attributePredicate;
};


template<class T> bool XmlPredicate::IsMatch(const char* tagName, const T& attributes) const
{
	bool tagMatch = m_tagName == tagName;

	if (!tagMatch)
		return false;

	if (!m_attributePredicate)
		return true;

	for (auto iter = begin(attributes); iter != end(attributes); ++iter)
	{
		if (m_attributePredicate->GetName() == iter->first && m_attributePredicate->GetValue() == iter->second)
		{
			return true;
		}
	}
	return false;
}

#endif