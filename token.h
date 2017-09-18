#ifndef TOKEN_H
#define TOKEN_H

enum class Token {lt, lt_slash, gt, slash_gt, eof};

inline const char * GetName(Token t)
{
	switch (t)
	{
	case Token::lt: return "lt";
	case Token::lt_slash: return "lt_slash";
	case Token::gt: return "gt";
	case Token::slash_gt: return "slash_gt";
	case Token::eof: return "eof";
	default: return nullptr;
	};
}

#endif
