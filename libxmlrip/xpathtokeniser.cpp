#include <iostream>

#include "xpathtokeniser.h"

using namespace std;

XPathTokeniser::XPathTokeniser(std::istream& inStream)
:	m_inStream{inStream}
{}

XPathToken XPathTokeniser::GetNextToken()
{
	return XPathToken{XPathToken::TOK_NULL};
}
