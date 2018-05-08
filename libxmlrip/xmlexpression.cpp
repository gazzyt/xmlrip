#include "xmlexpression.h"
#include "stringutils.h"
#include "exception/xpathexception.h"

using namespace std;

XmlExpression::XmlExpression()
:	m_predicates{}, m_matchingElements{}
{}

void XmlExpression::AddPredicate(XmlPredicate predicate)
{
	m_predicates.push_back(predicate);
}

const vector<XmlPredicate>& XmlExpression::GetPredicates() const
{
	return m_predicates;
}

int XmlExpression::GetCurrentMatchDepth() const
{
	return m_matchDepth;
}

int XmlExpression::GetCurrentDocumentDepth() const
{
	return m_documentDepth;
}

int XmlExpression::ProcessEndTag(const char* tagName)
{
	--m_documentDepth;
	
	const auto matchIndex = m_matchingElements.size();
	
	// Does this closing tag close the last matched tag?
	if ((matchIndex > 0) && m_matchingElements.top().GetTagName() == tagName)
	{
		// It does
		m_matchingElements.pop();

		if (matchIndex == m_predicates.size())
		{
			// We matched the last predicate
			return m_matchDepth--;
		}
		else
		{
			// Only a partial match
			return NO_MATCH;
		}
	}
	
	// If we already have a full match for all predicates
	if (matchIndex == m_predicates.size())
	{
		return m_matchDepth--;
	}
	
	return NO_MATCH;
}

unique_ptr<XmlExpression> XmlExpression::FromText(string text)
{
	if (text[0] != '/')
	{
		throw XPathException("XPath must begin with / or //");
	}

	// TODO - replace when xpath splitting implemented
	text.erase(0, 1);

	auto retval = make_unique<XmlExpression>();
	auto tagNames = split(text, '/');
	
	for ( auto tagName : tagNames)
	{
		retval->AddPredicate(XmlPredicate::FromText(tagName));
	}
	
	return retval;
}
