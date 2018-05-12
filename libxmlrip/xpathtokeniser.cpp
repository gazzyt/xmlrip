#include <algorithm>
#include <cctype>

#include "xpathtokeniser.h"
#include "exception/xpathexception.h"

using namespace std;

XPathTokeniser::XPathTokeniser(std::string& xpathText)
:	m_xpathText{xpathText},
	m_nextTokenStart{xpathText.begin()},
	m_xpathTextEnd{xpathText.end()}
{}

XPathToken XPathTokeniser::GetNextToken()
{
	string::const_iterator currentTokenStart(m_nextTokenStart);
	
	if (m_nextTokenStart == m_xpathTextEnd)
		return XPathToken{XPathToken::TOK_NULL};
	
	if (::isalnum(*m_nextTokenStart))
	{
		while (::isalnum(*m_nextTokenStart) && (m_nextTokenStart != m_xpathTextEnd))
			++m_nextTokenStart;
		
		return XPathToken{XPathToken::TOK_STRING, currentTokenStart, m_nextTokenStart};
	}
	
	if (*m_nextTokenStart == '/')
	{
		++m_nextTokenStart;
		
		if (*m_nextTokenStart == '/')
		{
			++m_nextTokenStart;
			return XPathToken{XPathToken::TOK_DBLSLASH, currentTokenStart, m_nextTokenStart};
		}
		
		return XPathToken{XPathToken::TOK_SLASH, currentTokenStart, m_nextTokenStart};
	}

	if (*m_nextTokenStart == '@')
	{
		++m_nextTokenStart;
		
		return XPathToken{XPathToken::TOK_AT, currentTokenStart, m_nextTokenStart};
	}

	if (*m_nextTokenStart == '[')
	{
		++m_nextTokenStart;
		
		return XPathToken{XPathToken::TOK_LEFTSQUAREBRACKET, currentTokenStart, m_nextTokenStart};
	}

	if (*m_nextTokenStart == ']')
	{
		++m_nextTokenStart;
		
		return XPathToken{XPathToken::TOK_RIGHTSQUAREBRACKET, currentTokenStart, m_nextTokenStart};
	}

	if (*m_nextTokenStart == '=')
	{
		++m_nextTokenStart;
		
		return XPathToken{XPathToken::TOK_EQUALS, currentTokenStart, m_nextTokenStart};
	}
	
	if (*m_nextTokenStart == '"' || *m_nextTokenStart == '\'')
	{
		return ExtractQuotedString(currentTokenStart);
	}
	
	throw XPathException(string("Unexpected character in XPath: ") + *m_nextTokenStart);
}

XPathToken XPathTokeniser::ExtractQuotedString(const string::const_iterator& currentTokenStart)
{
	char quote = *m_nextTokenStart;
	++m_nextTokenStart;

	auto closingQuote = find(m_nextTokenStart, m_xpathTextEnd, quote);
		
	if (closingQuote == m_xpathTextEnd)
		throw XPathException("Missing closing quote");
	
	m_nextTokenStart = closingQuote + 1;
	
	return XPathToken{XPathToken::TOK_STRING, currentTokenStart + 1, closingQuote};
}
