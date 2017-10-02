#ifndef TOKEN_H
#define TOKEN_H

#include <ostream>
#include <string>

class Token
{
public:
	enum class Type {lt, lt_slash, gt, slash_gt, string, eof};

	Token(Token::Type t, std::string stringValue = std::string{}) : m_type(t), m_stringValue(stringValue){}

	Token::Type GetType() const
	{
		return m_type;
	}
	
	const std::string& GetStringValue() const
	{
		return m_stringValue;
	}

	const char * GetName() const;
	
	bool operator==(const Token& t1) const;

private:
	Token::Type m_type;
	std::string m_stringValue;
};

std::ostream& operator<<(std::ostream& os, const Token& token);

#endif
