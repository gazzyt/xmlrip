#ifndef XPATHTOKEN_H
#define XPATHTOKEN_H

#include <string>

class XPathToken
{
public:
	enum TokenType {TOK_SLASH, TOK_STRING};
	
public:
	XPathToken(TokenType type);
	XPathToken(const XPathToken& rhs) = delete;

public:
	TokenType GetType() const { return m_type; }
	XPathToken& operator=(const XPathToken& rhs) = delete;

private:
	TokenType m_type;
};

#endif