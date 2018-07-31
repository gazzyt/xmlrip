#include <cassert>

#include "xmlexpression.h"
#include "stringutils.h"
#include "exception/xpathexception.h"

using namespace std;

XmlExpression::XmlExpression()
:	m_stepExprs{}, m_matches{}
{}

void XmlExpression::AddStepExpr(unique_ptr<XmlStepExpr> stepExpr)
{
	m_stepExprs.push_back(move(stepExpr));
}

const vector<unique_ptr<XmlStepExpr> >& XmlExpression::GetStepExprs() const
{
	return m_stepExprs;
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
	
	const auto matchIndex = m_matches.size();
	
	// Does this closing tag close the last matched tag?
	if ((matchIndex > 0) && m_matches.top().element.GetTagName() == tagName)
	{
		// It does
		m_matches.pop();

		if (matchIndex == m_stepExprs.size())
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
	if (matchIndex == m_stepExprs.size())
	{
		return m_matchDepth--;
	}
	
	return NO_MATCH;
}

unique_ptr<XmlExpression> XmlExpression::FromText(const string& text)
{
	auto retval = make_unique<XmlExpression>();
	XPathTokeniser tokeniser{ text };
	XPathToken token = tokeniser.GetNextToken();

	if (token.GetType() != XPathToken::TOK_DBLSLASH && token.GetType() != XPathToken::TOK_SLASH)
	{
		throw XPathException("XPath must begin with / or //", token.GetPosition());
	}

	while (token.GetType() != XPathToken::TOK_NULL)
	{
		retval->AddStepExpr(ReadStepExpr(tokeniser, token));

		//token = tokeniser.GetNextToken();
	}

	return retval;
}

unique_ptr<XmlStepExpr> XmlExpression::ReadStepExpr(XPathTokeniser& tokeniser, XPathToken& token)
{
	int depthPredicate = -1;

	if (token.GetType() == XPathToken::TOK_SLASH)
	{
		depthPredicate = 1;
	}
	else if (token.GetType() != XPathToken::TOK_DBLSLASH)
	{
		throw XPathException("Expected / or //", token.GetPosition());
	}

	token = tokeniser.GetNextToken();

	if (token.GetType() != XPathToken::TOK_STRING)
	{
		throw XPathException("Expected element name", token.GetPosition());
	}

	auto stepExpr = make_unique<XmlStepExpr>(token.GetString(), depthPredicate);

	bool done = false;
	
	while (!done)
	{
		token = tokeniser.GetNextToken();

		switch (token.GetType())
		{
		case XPathToken::TOK_LEFTSQUAREBRACKET:
			stepExpr->AddPredicate(ReadAttributePredicate(tokeniser, token));
			break;

		case XPathToken::TOK_DBLSLASH:
		case XPathToken::TOK_SLASH:
		case XPathToken::TOK_NULL:
			done = true;
			break;

		default:
			throw XPathException{ "Unexpected token", token.GetPosition() };

		}
	}
	
	return stepExpr;
}

unique_ptr<XmlAttributePredicate> XmlExpression::ReadAttributePredicate(XPathTokeniser& tokeniser, XPathToken& token)
{
	assert(token.GetType() == XPathToken::TOK_LEFTSQUAREBRACKET);
	
	token = tokeniser.GetNextToken();

	// Is this an @attrib="xx" type predicate?
	if (token.GetType() == XPathToken::TOK_AT)
	{
		token = tokeniser.GetNextToken();

		if (token.GetType() != XPathToken::TOK_STRING)
		{
			throw XPathException("Expected attribute name", token.GetPosition());
		}

		string attributeName{ token.GetString() };

		token = tokeniser.GetNextToken();

		if (token.GetType() != XPathToken::TOK_EQUALS)
			throw XPathException("Expected = token", token.GetPosition());

		token = tokeniser.GetNextToken();

		if (token.GetType() != XPathToken::TOK_STRING)
		{
			throw XPathException("Expected attribute value", token.GetPosition());
		}

		string attributeValue{ token.GetString() };

		token = tokeniser.GetNextToken();

		if (token.GetType() != XPathToken::TOK_RIGHTSQUAREBRACKET)
			throw XPathException("Expected ] token", token.GetPosition());

		return make_unique<XmlAttributePredicate>(XmlAttributePredicate::MODE_EQUAL, move(attributeName), move(attributeValue));
	}
	else if (token.GetType() == XPathToken::TOK_STRING)
	{
		auto functionName = token.GetString();
		auto functionNamePos = token.GetPosition();
		
		token = tokeniser.GetNextToken();

		if (token.GetType() != XPathToken::TOK_LEFTBRACKET)
		{
			throw XPathException("Expected '('", token.GetPosition());
		}

		// We got a function in the predicate. Is it one we know?
		if (functionName != "starts-with")
		{
			throw XPathException("Unknown function name: " + functionName, functionNamePos);
		}
		
		token = tokeniser.GetNextToken();
		
		if (token.GetType() != XPathToken::TOK_AT)
		{
			throw XPathException("Expected '@'", token.GetPosition());
		}

		token = tokeniser.GetNextToken();
		
		if (token.GetType() != XPathToken::TOK_STRING)
		{
			throw XPathException("Expected attribute name", token.GetPosition());
		}

		auto attributeName = token.GetString();
		
		token = tokeniser.GetNextToken();
		
		if (token.GetType() != XPathToken::TOK_COMMA)
		{
			throw XPathException("Expected ','", token.GetPosition());
		}

		token = tokeniser.GetNextToken();
		
		if (token.GetType() != XPathToken::TOK_STRING)
		{
			throw XPathException("Expected attribute value", token.GetPosition());
		}

		auto attributeValue = token.GetString();

		token = tokeniser.GetNextToken();
		
		if (token.GetType() != XPathToken::TOK_RIGHTBRACKET)
		{
			throw XPathException("Expected ')'", token.GetPosition());
		}

		token = tokeniser.GetNextToken();

		if (token.GetType() != XPathToken::TOK_RIGHTSQUAREBRACKET)
			throw XPathException("Expected ] token", token.GetPosition());

		return make_unique<XmlAttributePredicate>(XmlAttributePredicate::MODE_STARTSWITH, move(attributeName), move(attributeValue));
		
	}
	else
	{
		throw XPathException("Unexpected token", token.GetPosition());
	}
}
