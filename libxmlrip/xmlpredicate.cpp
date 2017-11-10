#include <ostream>

#include "memoryutils.h"
#include "xmlpredicate.h"

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
	return (m_tagName == elem.GetTagName() && elem.IsOpeningTag());
}

const string& XmlPredicate::GetTagName() const
{
	return m_tagName;
}

const XmlAttribute* XmlPredicate::GetAttributePredicate() const
{
	return m_attributePredicate.get();
}
