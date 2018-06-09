#include <ostream>

#include "xmlstreammodifiers.h"

#include "xmlattributepredicate.h"

using namespace std;

XmlAttributePredicate::XmlAttributePredicate(string&& attrName, string&& attrValue) noexcept
	: m_name{attrName}, m_value{attrValue}
{}


const string& XmlAttributePredicate::GetName() const
{
	return m_name;
}

const string& XmlAttributePredicate::GetValue() const
{
	return m_value;
}

bool XmlAttributePredicate::IsMatch(const char* name, const char* value) const noexcept
{
	return ((m_name == name) && (m_value == value));
}

