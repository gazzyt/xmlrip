#ifndef XPATHTOKENISER_H
#define XPATHTOKENISER_H

#include <string>

#include "xpathtoken.h"

class XPathTokeniser
{
public:
	XPathTokeniser(const std::string& xpathText);
	XPathTokeniser(const XPathTokeniser& rhs) = delete;

public:
	XPathToken GetNextToken();
	XPathTokeniser& operator=(const XPathTokeniser& rhs) = delete;

private:
	XPathToken ExtractSingleCharToken(XPathToken::TokenType type, const std::string::const_iterator& currentTokenStart);
	XPathToken ExtractSlashToken(const std::string::const_iterator& currentTokenStart);
	XPathToken ExtractStringToken(const std::string::const_iterator& currentTokenStart);
	XPathToken ExtractQuotedString(const std::string::const_iterator& currentTokenStart);
	int GetPosition(const std::string::const_iterator& currentTokenStart)
	{
		return static_cast<int>(currentTokenStart - begin(m_xpathText));
	}

private:
	const std::string m_xpathText;
	std::string::const_iterator m_nextTokenStart;
	std::string::const_iterator m_xpathTextEnd;
};


#endif