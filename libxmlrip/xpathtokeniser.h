#ifndef XPATHTOKENISER_H
#define XPATHTOKENISER_H

#include <string>

#include "xpathtoken.h"

class XPathTokeniser
{
public:
	XPathTokeniser(std::string& xpathText);
	XPathTokeniser(const XPathTokeniser& rhs) = delete;

public:
	XPathToken GetNextToken();
	XPathTokeniser& operator=(const XPathTokeniser& rhs) = delete;

private:
	XPathToken ExtractQuotedString(const std::string::const_iterator& currentTokenStart);

private:
	std::string m_xpathText;
	std::string::const_iterator m_nextTokenStart;
	std::string::const_iterator m_xpathTextEnd;
};


#endif