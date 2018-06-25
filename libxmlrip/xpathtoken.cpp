
#include "xpathtoken.h"

using namespace std;

XPathToken::XPathToken(TokenType type, int position, string::const_iterator beginChars, string::const_iterator endChars)
:	m_type{type},
	m_position{ position },
	m_beginChars{beginChars},
	m_endChars{endChars}
{}

XPathToken::XPathToken(TokenType type, int position)
:	m_type{type},
m_position{ position },
m_beginChars{},
	m_endChars{}
{}

string XPathToken::GetString() const
{
	return string(m_beginChars, m_endChars);
}