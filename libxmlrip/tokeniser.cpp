#include "tokeniser.h"
#include <iostream>

Tokeniser::Tokeniser(std::unique_ptr<std::istream> stream)
:	m_stream(std::move(stream))
{
}


Token Tokeniser::GetNextToken()
{
	char c;

	while (true)
	{
		m_stream->get(c);
		std::cout << c << std::endl;
		switch (c)
		{
		case '<':
			if (m_stream->peek() == '/')
			{
				m_stream->get(c);
				return Token(Token::Type::lt_slash);
			}
			else
			{
				return Token(Token::Type::lt);
			}
		case '/':
			if (m_stream->peek() == '>')
			{
				m_stream->get(c);
				return Token(Token::Type::slash_gt);
			}
			else
			{
				std::cerr << "Unexpected character '/'" << std::endl;
			}
		case '>':
			return Token(Token::Type::gt);
		default:
			if (m_stream->eof())
				return Token(Token::Type::eof);
		};
	};
}

