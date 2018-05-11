#ifndef XPATHTOKENISER_H
#define XPATHTOKENISER_H

#include <iosfwd>
#include <string>

#include "xpathtoken.h"

class XPathTokeniser
{
public:
	XPathTokeniser(std::istream& inStream);
	XPathTokeniser(const XPathTokeniser& rhs) = delete;

public:
	XPathToken GetNextToken();
	XPathTokeniser& operator=(const XPathTokeniser& rhs) = delete;

private:
	std::istream& m_inStream;
};


#endif