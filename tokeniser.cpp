#include "tokeniser.h"

Tokeniser::Tokeniser(std::unique_ptr<std::istream> stream)
:	m_stream(std::move(stream))
{
}


token Tokeniser::GetNextToken()
{
	return token::token_lt;
}

