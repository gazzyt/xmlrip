#include "tokeniser.h"
#include <iostream>

using namespace std;

Tokeniser::Tokeniser(unique_ptr<istream> stream)
:	m_stream(move(stream))
{
}


Token Tokeniser::GetNextToken()
{
	char c;

	while (true)
	{
		m_stream->get(c);
		cout << c << endl;

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
				cerr << "Unexpected character '/'" << endl;
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
			
			return ExtractStringToken(c);
		}
	};
}

Token Tokeniser::ExtractStringToken(char firstChar)
{
	string tokenValue{};
	char c = firstChar;
	char nextChar = m_stream->peek();
	tokenValue.push_back(c);
	
	while ((nextChar != '<') && (nextChar != '>'))
	{
		m_stream->get(c);
		tokenValue.push_back(c);
		nextChar = m_stream->peek();
	};
	
	return Token(Token::Type::string, tokenValue);
}
