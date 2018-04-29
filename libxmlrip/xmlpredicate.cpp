#include <ostream>

#include "memoryutils.h"
#include "xmlpredicate.h"
#include "exception/xpathexception.h"

using namespace std;

XmlPredicate::XmlPredicate(string tagName, std::unique_ptr<XmlAttribute> attributePredicate, int documentDepthPredicate)
	:	m_tagName(tagName), m_attributePredicate(move(attributePredicate)),
		m_documentDepthPredicate(documentDepthPredicate)
{}

XmlPredicate::XmlPredicate(const XmlPredicate& rhs)
:	m_tagName(rhs.m_tagName),
	m_attributePredicate(copy_unique(rhs.m_attributePredicate)),
	m_documentDepthPredicate(rhs.m_documentDepthPredicate)
{}


const string& XmlPredicate::GetTagName() const
{
	return m_tagName;
}

const XmlAttribute* XmlPredicate::GetAttributePredicate() const
{
	return m_attributePredicate.get();
}

int XmlPredicate::GetDocumentDepthPredicate() const
{
	return m_documentDepthPredicate;
}

XmlPredicate XmlPredicate::FromText(string text)
{
	if (text.empty())
	{
		throw XPathException("Cannot create predicate from empty string");
	}

	bool readingQuotedString = false;
	string tagName;
	string attrName;
	string attrValue;
	string* currentTarget = &tagName;
	
	for (char ch : text)
	{
		if (isspace(ch))
		{
			if (readingQuotedString)
			{
				currentTarget->push_back(ch);
			}
		}
		else if (ch == '[')
		{
			currentTarget = &attrName;
		}
		else if (ch == ']')
		{
		}
		else if (ch == '=')
		{
			currentTarget = &attrValue;
		}
		else if (ch == '"' || ch == '\'')
		{
			readingQuotedString = !readingQuotedString;
		}
		else
		{
			currentTarget->push_back(ch);
		}
	}

	if (attrName.length() > 0)
	{
		return XmlPredicate{tagName, make_unique<XmlAttribute>(move(attrName), move(attrValue))};
	}
	else
	{
		return XmlPredicate{tagName};
	}
}

