#ifndef XPATHTOKEN_H
#define XPATHTOKEN_H

#include <string>

class XPathToken
{
public:
	enum TokenType {TOK_NULL, TOK_SLASH, TOK_DBLSLASH, TOK_STRING, TOK_AT, TOK_LEFTSQUAREBRACKET, TOK_RIGHTSQUAREBRACKET, TOK_EQUALS};
	
public:
	XPathToken(TokenType type);
	XPathToken(TokenType type, std::string::const_iterator beginChars, std::string::const_iterator endChars);
	XPathToken(const XPathToken& rhs) = default;

public:
	TokenType GetType() const { return m_type; }
	std::string GetString() const;
	XPathToken& operator=(const XPathToken& rhs) = default;

private:
	TokenType m_type;
	std::string::const_iterator m_beginChars;
	std::string::const_iterator m_endChars;
};


#endif