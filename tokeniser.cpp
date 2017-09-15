#include "tokeniser.h"
#include <iostream>

Tokeniser::Tokeniser(std::unique_ptr<std::istream> stream)
:	m_stream(std::move(stream))
{
}


Token Tokeniser::GetNextToken()
{
	char c;
	m_stream->get(c);
	std::cout << c << std::endl;
	return Token::token_lt;
}

