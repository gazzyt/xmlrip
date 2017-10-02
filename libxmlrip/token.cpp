#include "token.h"
#include <ostream>

using namespace std;

ostream& operator<<(ostream& os, const Token& token)
{
	os << "{type:\"" << token.GetName() << "\",stringValue:\"" << token.GetStringValue() << "\"}";
	return os;
}

const char * Token::GetName() const
{
	switch (m_type)
	{
	case Type::lt: return "lt";
	case Type::lt_slash: return "lt_slash";
	case Type::gt: return "gt";
	case Type::slash_gt: return "slash_gt";
	case Type::string: return "string";
	case Type::eof: return "eof";
	default: return nullptr;
	};
}

bool Token::operator==(const Token& t1) const
{
	return (t1.m_type == m_type) && (t1.m_stringValue == m_stringValue);
}
