#include <cstring>
#include <ostream>

#include "xmlstreammodifiers.h"

#include "xmlattributepredicate.h"

using namespace std;

XmlAttributePredicate::XmlAttributePredicate(Mode mode, string&& attrName, string&& attrValue) noexcept
	: m_mode{mode}, m_name{attrName}, m_value{attrValue}
{}

XmlAttributePredicate::Mode XmlAttributePredicate::GetMode() const
{
	return m_mode;
}

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
	if (m_mode == MODE_EQUAL)
	{
		return ((m_name == name) && (m_value == value));
	}
	else
	{
		return ((m_name == name) && (::strlen(value) >= m_value.length()) && (::memcmp(value, m_value.c_str(), m_value.length()) == 0));
	}
}

