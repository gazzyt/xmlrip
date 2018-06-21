#include <algorithm>
#include <cctype>

#include "xpathtokeniser.h"
#include "exception/xpathexception.h"

using namespace std;

XPathTokeniser::XPathTokeniser(const std::string& xpathText)
:	m_xpathText{xpathText},
	m_nextTokenStart{m_xpathText.begin()},
	m_xpathTextEnd{m_xpathText.end()}
{}

XPathToken XPathTokeniser::GetNextToken()
{
	// Skip any whitespace
	while (m_nextTokenStart != m_xpathTextEnd && ::isblank(*m_nextTokenStart))
	{
		++m_nextTokenStart;
	}
	
	if (m_nextTokenStart == m_xpathTextEnd)
		return XPathToken{XPathToken::TOK_NULL, GetPosition(m_nextTokenStart)};
	
	const auto currentTokenStart = m_nextTokenStart;
	
	switch (*m_nextTokenStart)
	{
		case '/':
			return ExtractSlashToken(currentTokenStart);
			
		case '@':
			return ExtractSingleCharToken(XPathToken::TOK_AT, currentTokenStart);

		case '[':
			return ExtractSingleCharToken(XPathToken::TOK_LEFTSQUAREBRACKET, currentTokenStart);

		case ']':
			return ExtractSingleCharToken(XPathToken::TOK_RIGHTSQUAREBRACKET, currentTokenStart);

		case '(':
			return ExtractSingleCharToken(XPathToken::TOK_LEFTBRACKET, currentTokenStart);

		case ')':
			return ExtractSingleCharToken(XPathToken::TOK_RIGHTBRACKET, currentTokenStart);

		case ',':
			return ExtractSingleCharToken(XPathToken::TOK_COMMA, currentTokenStart);

		case '=':
			return ExtractSingleCharToken(XPathToken::TOK_EQUALS, currentTokenStart);
	
		case '"':
		case '\'':
			return ExtractQuotedString(currentTokenStart);

		default:
			if (::isalnum(*m_nextTokenStart))
				return ExtractStringToken(currentTokenStart);
			else
				throw XPathException(string("Unexpected character in XPath: ") + *m_nextTokenStart, GetPosition(currentTokenStart));
	};
}


XPathToken XPathTokeniser::ExtractSingleCharToken(XPathToken::TokenType type, const std::string::const_iterator& currentTokenStart)
{
	++m_nextTokenStart;
	
	return XPathToken{type, GetPosition(currentTokenStart), currentTokenStart, m_nextTokenStart};
}

XPathToken XPathTokeniser::ExtractSlashToken(const std::string::const_iterator& currentTokenStart)
{
	const auto nextChar = m_nextTokenStart + 1;
	
	if (nextChar != m_xpathTextEnd && *nextChar == '/')
	{
		++m_nextTokenStart;
		return ExtractSingleCharToken(XPathToken::TOK_DBLSLASH, currentTokenStart);
	}
	else
	{
		return ExtractSingleCharToken(XPathToken::TOK_SLASH, currentTokenStart);
	}
}

XPathToken XPathTokeniser::ExtractStringToken(const std::string::const_iterator& currentTokenStart)
{
	auto isValidChar = [](char c){return ::isalnum(c) || c == '-';};
	auto stringEnd = find_if_not(currentTokenStart, m_xpathTextEnd, isValidChar);
	
	m_nextTokenStart = stringEnd;
	
	return XPathToken{XPathToken::TOK_STRING, GetPosition(currentTokenStart), currentTokenStart, m_nextTokenStart};
}

XPathToken XPathTokeniser::ExtractQuotedString(const string::const_iterator& currentTokenStart)
{
	char quote = *m_nextTokenStart;
	++m_nextTokenStart;

	auto closingQuote = find(m_nextTokenStart, m_xpathTextEnd, quote);
		
	if (closingQuote == m_xpathTextEnd)
		throw XPathException("Missing closing quote", GetPosition(closingQuote - 1));
	
	m_nextTokenStart = closingQuote + 1;
	
	return XPathToken{XPathToken::TOK_STRING, GetPosition(currentTokenStart), currentTokenStart + 1, closingQuote};
}
