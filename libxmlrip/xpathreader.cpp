#include <cassert>
#include <cctype>

#include "xpathreader.h"
#include "xmlattributepredicate.h"
#include "xmlordinalpredicate.h"
#include "stringutils.h"
#include "exception/xpathexception.h"

using namespace std;

// Create an XPathReader by parsing an xpath expression as a string
unique_ptr<XmlExpression> XPathReader::FromText(const string& text)
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

unique_ptr<XmlStepExpr> XPathReader::ReadStepExpr(XPathTokeniser& tokeniser, XPathToken& token)
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
			stepExpr->AddPredicate(ReadPredicate(tokeniser, token));
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

unique_ptr<XmlPredicate> XPathReader::ReadPredicate(XPathTokeniser& tokeniser, XPathToken& token)
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
		auto tokenText = token.GetString();
		if (::isdigit(tokenText[0]))
		{
			unsigned int ordinal = ::atoi(tokenText.c_str());

			token = tokeniser.GetNextToken();

			if (token.GetType() != XPathToken::TOK_RIGHTSQUAREBRACKET)
				throw XPathException("Expected ] token", token.GetPosition());

			return make_unique<XmlOrdinalPredicate>(ordinal);
		}
		else
		{
			auto functionNamePos = token.GetPosition();
			
			token = tokeniser.GetNextToken();

			if (token.GetType() != XPathToken::TOK_LEFTBRACKET)
			{
				throw XPathException("Expected '('", token.GetPosition());
			}

			// We got a function in the predicate. Is it one we know?
			if (tokenText != "starts-with")
			{
				throw XPathException("Unknown function name: " + tokenText, functionNamePos);
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
	}
	else
	{
		throw XPathException("Unexpected token", token.GetPosition());
	}
}
