#include <ostream>

#include "memoryutils.h"
#include "xmlpredicate.h"
#include "exception/xpathexception.h"

using namespace std;

XmlPredicate::XmlPredicate(string tagName, std::unique_ptr<XmlAttribute> attributePredicate)
	: m_tagName(tagName), m_attributePredicate(move(attributePredicate))
{}

XmlPredicate::XmlPredicate(const XmlPredicate& rhs)
:	m_tagName(rhs.m_tagName),
	m_attributePredicate(copy_unique(rhs.m_attributePredicate))
{}

bool XmlPredicate::IsMatch(const XmlElement& elem) const
{
	bool tagMatch = m_tagName == elem.GetTagName() && elem.IsOpeningTag();
	
	if (!tagMatch)
		return false;
	
	if (!m_attributePredicate)
		return true;

	auto val = elem.GetAttributeValue(m_attributePredicate->GetName());
	
	return !(val == nullptr || m_attributePredicate->GetValue() != *val);
}

const string& XmlPredicate::GetTagName() const
{
	return m_tagName;
}

const XmlAttribute* XmlPredicate::GetAttributePredicate() const
{
	return m_attributePredicate.get();
}

XmlPredicate XmlPredicate::FromText(string text)
{
	if (text.empty())
	{
		throw XPathException("Cannot create predicate from empty string");
	}
	
	return XmlPredicate(text);
}
