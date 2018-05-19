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
	auto retval = make_unique<XmlExpression>();
	XPathTokeniser tokeniser{ text };
	XPathToken token = tokeniser.GetNextToken();

	if (token.GetType() != XPathToken::TOK_DBLSLASH && token.GetType() != XPathToken::TOK_SLASH)
	{
		throw XPathException("XPath must begin with / or //");
	}

	while (token.GetType() != XPathToken::TOK_NULL)
	{
		retval->AddPredicate(ReadPredicate(tokeniser, token));

		//token = tokeniser.GetNextToken();
	}

	return retval;
}

XmlPredicate XmlExpression::ReadPredicate(XPathTokeniser& tokeniser, XPathToken& token)
{
	if (token.GetType() != XPathToken::TOK_DBLSLASH && token.GetType() != XPathToken::TOK_SLASH)
	{
		throw XPathException("Ecpected / or //");
	}

	token = tokeniser.GetNextToken();

	if (token.GetType() != XPathToken::TOK_STRING)
	{
		throw XPathException("Expected element name");
	}

	string elementName{ token.GetString() };

	token = tokeniser.GetNextToken();

	switch (token.GetType())
	{
	case XPathToken::TOK_LEFTSQUAREBRACKET:
		{
			token = tokeniser.GetNextToken();

			if (token.GetType() != XPathToken::TOK_AT)
				throw XPathException("Expected @ token");

			token = tokeniser.GetNextToken();

			if (token.GetType() != XPathToken::TOK_STRING)
			{
				throw XPathException("Expected attribute name");
			}

			string attributeName{ token.GetString() };

			token = tokeniser.GetNextToken();

			if (token.GetType() != XPathToken::TOK_EQUALS)
				throw XPathException("Expected = token");

			token = tokeniser.GetNextToken();

			if (token.GetType() != XPathToken::TOK_STRING)
			{
				throw XPathException("Expected attribute value");
			}

			string attributeValue{ token.GetString() };

			token = tokeniser.GetNextToken();

			if (token.GetType() != XPathToken::TOK_RIGHTSQUAREBRACKET)
				throw XPathException("Expected ] token");

			token = tokeniser.GetNextToken();

			return XmlPredicate{ elementName, make_unique<XmlAttribute>(move(attributeName), move(attributeValue)) };
		}

	case XPathToken::TOK_DBLSLASH:
	case XPathToken::TOK_SLASH:
	case XPathToken::TOK_NULL:
		return (XmlPredicate{ elementName });

	default:
		throw XPathException{ "Unexpected token" };

	}
}
