#include <ostream>

#include "xmlstreammodifiers.h"

#include "xmlattribute.h"

using namespace std;

XmlAttribute::XmlAttribute(string&& attrName, string&& attrValue) noexcept
	: m_name{attrName}, m_value{attrValue}
{}


string XmlAttribute::GetName() const
{
	return m_name;
}

string XmlAttribute::GetValue() const
{
	return m_value;
}

bool XmlAttribute::operator==(const XmlAttribute& rhs) const
{
	return ((rhs.m_name == m_name) && (rhs.m_value == m_value));
}


ostream& operator<<(ostream& os, const XmlAttribute& attr)
{
	attr.Print(os);
	
	return os;
}

void XmlAttribute::Print(std::ostream& os) const
{
	switch (XmlStreamModifiers::GetCurrentOutputFormat(os))
	{
		case XmlStreamModifiers::xml:
			PrintAsXml(os);
			break;
			
		case XmlStreamModifiers::verbose:
			PrintAsVerbose(os);
			break;
	};
}

void XmlAttribute::PrintAsXml(std::ostream& os) const
{
	os << m_name << '=' << m_value;
}

void XmlAttribute::PrintAsVerbose(std::ostream& os) const
{
	os << m_name << ':' << m_value;
}
