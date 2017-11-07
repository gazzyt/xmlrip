#include <ostream>

#include "xmlelement.h"
#include "xmlstreammodifiers.h"

using namespace std;

XmlElement::XmlElement() noexcept
	: m_type{Type::tag}, m_tagName{}, m_attributeText{}, m_isOpeningTag{false}, m_isClosingTag{false}
{}

XmlElement::XmlElement(XmlElement::Type type, string tagName, bool isOpeningTag, bool isClosingTag) noexcept
	: m_type{type}, m_tagName(tagName), m_attributeText{}, m_isOpeningTag(isOpeningTag), m_isClosingTag(isClosingTag)
{}

XmlElement::XmlElement(XmlElement::Type type, string tagName, string attributeText, bool isOpeningTag, bool isClosingTag) noexcept
	: m_type{type}, m_tagName(tagName), m_attributeText{attributeText}, m_isOpeningTag(isOpeningTag), m_isClosingTag(isClosingTag)
{}

XmlElement::Type XmlElement::GetType() const
{
	return m_type;
}

bool XmlElement::IsOpeningTag() const
{
	return m_isOpeningTag;
}

bool XmlElement::IsClosingTag() const
{
	return m_isClosingTag;
}


string XmlElement::GetTagName() const
{
	return m_tagName;
}

string XmlElement::GetAttributeText() const
{
	return m_attributeText;
}

bool XmlElement::IsMatch(const XmlElement& e1) const
{
	return (e1.m_tagName == m_tagName);
}

bool XmlElement::operator==(const XmlElement& e1) const
{
	return (e1.m_type == m_type) && (e1.m_tagName == m_tagName) && (e1.m_isOpeningTag == m_isOpeningTag) && (e1.m_isClosingTag == m_isClosingTag);
}

ostream& operator<<(ostream& os, const XmlElement& elem)
{
	elem.Print(os);
	
	return os;
}

void XmlElement::Print(std::ostream& os) const
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

void XmlElement::PrintAsXml(std::ostream& os) const
{
	switch (GetType())
	{
		case XmlElement::Type::tag:
		{
			auto opening = (IsClosingTag() && !IsOpeningTag()) ? "</" : "<";
			auto closing = (IsClosingTag() && IsOpeningTag()) ? "/>" : ">";

			os << opening;
			os << GetTagName();
			os << GetAttributeText();
			os << closing;
		}
		break;
			
		case XmlElement::Type::declaration:
			os << "<?" << GetTagName() << "?>";
			break;

		case XmlElement::Type::comment:
			os << "<!--" << GetTagName() << "-->";
			break;
			
		case XmlElement::Type::text:
			os << GetTagName();
			break;
	};
}

void XmlElement::PrintAsVerbose(std::ostream& os) const
{
	os << "{type:\"" << static_cast<underlying_type<Type>::type>(m_type) << "\",TagName:\"" << m_tagName << "\",IsOpeningTag:" << m_isOpeningTag;
	os << ",IsClosingTag:" << m_isClosingTag << ",AttributeText:\"" << m_attributeText << "\"}";
}

XmlElement XmlElement::FromText(std::string text, bool isOpeningTag, bool isClosingTag)
{
	auto firstSpace = text.find_first_of(' ');
	
	if (firstSpace == string::npos)
	{
		return XmlElement(Type::tag, text, isOpeningTag, isClosingTag);
	}
	else
	{
		return XmlElement(Type::tag, text.substr(0, firstSpace), text.substr(firstSpace), isOpeningTag, isClosingTag);
	}
}

