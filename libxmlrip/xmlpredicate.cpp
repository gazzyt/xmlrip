#include "xmlpredicate.h"
#include <ostream>

using namespace std;

XmlPredicate::XmlPredicate(string tagName)
	: m_tagName(tagName)
{}


bool XmlPredicate::IsMatch(const XmlElement& elem) const
{
	return (m_tagName == elem.GetTagName() && elem.IsOpeningTag());
}

const string& XmlPredicate::GetTagName() const
{
	return m_tagName;
}
