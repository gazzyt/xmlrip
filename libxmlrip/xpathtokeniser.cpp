
#include "xpathtokeniser.h"

using namespace std;

XPathTokeniser::XPathTokeniser(std::string& xpathText)
:	m_xpathText{xpathText}
{}

XPathToken XPathTokeniser::GetNextToken()
{
	return XPathToken{XPathToken::TOK_NULL};
}
