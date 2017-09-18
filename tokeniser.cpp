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
				return Token::lt_slash;
			}
			else
			{
				return Token::lt;
			}
		case '/':
			if (m_stream->peek() == '>')
			{
				m_stream->get(c);
				return Token::slash_gt;
			}
			else
			{
				std::cerr << "Unexpected character '/'" << std::endl;
			}
		case '>':
			return Token::gt;
		default:
			if (m_stream->eof())
				return Token::eof;
		};
	};
}

