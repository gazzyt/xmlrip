#ifndef TOKEN_H
#define TOKEN_H

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

inline const char * GetName() const
{
	switch (m_type)
	{
	case Type::lt: return "lt";
	case Type::lt_slash: return "lt_slash";
	case Type::gt: return "gt";
	case Type::slash_gt: return "slash_gt";
	case Type::eof: return "eof";
	default: return nullptr;
	};
}
private:
	Token::Type m_type;
	std::string m_stringValue;
};

#endif
