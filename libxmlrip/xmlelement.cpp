#include <algorithm>
#include <ostream>

#include "xmlelement.h"
#include "xmlstreammodifiers.h"

using namespace std;

XmlElement::XmlElement() noexcept
	: m_type{Type::tag}, m_tagName{}, m_attributes{}, m_isOpeningTag{false}, m_isClosingTag{false}
{}

XmlElement::XmlElement(XmlElement::Type type, string tagName, bool isOpeningTag, bool isClosingTag) noexcept
	: m_type{type}, m_tagName{tagName}, m_attributes{}, m_isOpeningTag{isOpeningTag}, m_isClosingTag{isClosingTag}
{}

XmlElement::XmlElement(XmlElement::Type type, string tagName, vector<XmlAttribute>&& attributes, bool isOpeningTag, bool isClosingTag) noexcept
	: m_type{type}, m_tagName{tagName}, m_attributes{move(attributes)}, m_isOpeningTag{isOpeningTag}, m_isClosingTag{isClosingTag}
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


const string& XmlElement::GetTagName() const
{
	return m_tagName;
}

string XmlElement::GetAttributeText() const
{
	string attrText;
	
	for (auto attr : m_attributes)
	{
		if (attrText.length() != 0)
		{
			attrText += " ";
		}
		
		attrText += attr.GetName() + "=" 
#ifndef USE_INTERNAL_PARSER
			+ '"'
#endif
			+ attr.GetValue()
#ifndef USE_INTERNAL_PARSER
			+ '"'
#endif
		;
	}
	
	return attrText;
}

const string* XmlElement::GetAttributeValue(const string& attrName) const
{
	auto iter = find_if(m_attributes.begin(), m_attributes.end(), [attrName] (XmlAttribute attr) {return attr.GetName() == attrName;});
	if (iter == m_attributes.end())
	{
		return nullptr;
	}
	else
	{
		return &iter->GetValue();
	}
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

void XmlElement::Print(ostream& os) const
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

void XmlElement::PrintAsXml(ostream& os) const
{
	switch (GetType())
	{
		case XmlElement::Type::tag:
		{
			auto opening = (IsClosingTag() && !IsOpeningTag()) ? "</" : "<";
			auto closing = (IsClosingTag() && IsOpeningTag()) ? "/>" : ">";
			auto attrText = GetAttributeText();
			os << opening;
			os << GetTagName();
			if (attrText.length() > 0)
			{
				os << ' ' << attrText;
			}
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

void XmlElement::PrintAsVerbose(ostream& os) const
{
	os << "{type:\"" << static_cast<underlying_type<Type>::type>(m_type) << "\",TagName:\"" << m_tagName << "\",IsOpeningTag:" << m_isOpeningTag;
	os << ",IsClosingTag:" << m_isClosingTag << ",AttributeText:\"" << GetAttributeText() << "\"}";
}

vector<XmlAttribute> XmlElement::ReadAttributes(string text)
{
	static auto attrs = vector<XmlAttribute>{};
	static string attrName;
	static string attrValue;
	attrs.clear();
	attrName.assign("");
	attrValue.assign("");
	string* currentTarget = &attrName;
	bool readingQuotedString = false;

	for (char ch : text)
	{
		if (isspace(ch))
		{
			if (readingQuotedString)
			{
				currentTarget->push_back(ch);
			}
			else if (currentTarget == &attrValue && attrValue.length() > 0)
			{
				// we just finished reading the value of an attribute
				attrs.push_back(XmlAttribute{move(attrName), move(attrValue)});
				attrName.clear();
				attrValue.clear();
				currentTarget = &attrName;
			}
		}
		else if (ch == '=')
		{
			currentTarget = &attrValue;
		}
		else if (ch == '"')
		{
			readingQuotedString = !readingQuotedString;
			currentTarget->push_back(ch);
		}
		else
		{
			currentTarget->push_back(ch);
		}
	}

	// Check if there is one ready to go
	if (attrName.length() > 0)
	{
		attrs.push_back(XmlAttribute{move(attrName), move(attrValue)});
	}
	return attrs;
}

XmlElement XmlElement::FromText(string text, bool isOpeningTag, bool isClosingTag)
{
	auto firstSpace = text.find_first_of(' ');
	
	if (firstSpace == string::npos)
	{
		return XmlElement(Type::tag, text, isOpeningTag, isClosingTag);
	}
	else
	{
		//return XmlElement(Type::tag, text.substr(0, firstSpace), isOpeningTag, isClosingTag);
		return XmlElement(Type::tag, text.substr(0, firstSpace), move(ReadAttributes(text.substr(firstSpace))), isOpeningTag, isClosingTag);
	}
}

