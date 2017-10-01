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

		if (c == '<')
		{
			if (m_stream->peek() == '/')
			{
				m_stream->get(c);
				return Token(Token::Type::lt_slash);
			}
			else
			{
				return Token(Token::Type::lt);
			}
		}
		else if (c == '/')
		{
			if (m_stream->peek() == '>')
			{
				m_stream->get(c);
				return Token(Token::Type::slash_gt);
			}
			else
			{
				std::cerr << "Unexpected character '/'" << std::endl;
			}
		}
		else if (c == '>')
		{
			return Token(Token::Type::gt);
		}
		else
		{
			if (m_stream->eof())
				return Token(Token::Type::eof);
			
			return ExtractStringToken();
		}
	};
}

Token Tokeniser::ExtractStringToken()
{
	return Token(Token::Type::string);
}
