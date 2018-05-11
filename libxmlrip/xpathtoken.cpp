
#include "xpathtoken.h"

using namespace std;

XPathToken::XPathToken(TokenType type, string::const_iterator beginChars, string::const_iterator endChars)
:	m_type{type},
	m_beginChars{beginChars},
	m_endChars{endChars}
{}

string XPathToken::GetString() const
{
	return string(m_beginChars, m_endChars);
}