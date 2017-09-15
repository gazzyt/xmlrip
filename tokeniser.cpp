#include "tokeniser.h"

Tokeniser::Tokeniser(std::unique_ptr<std::istream> stream)
:	m_stream(std::move(stream))
{
}


Token Tokeniser::GetNextToken()
{
	return Token::token_lt;
}

