#include "token.h"

Token::Token(std::string tagName, bool isOpeningTag, bool isClosingTag)
	: m_tagName(tagName), m_isOpeningTag(isOpeningTag), m_isClosingTag(isClosingTag)
{}


bool Token::IsOpeningTag() const
{
	return m_isOpeningTag;
}

bool Token::IsClosingTag() const
{
	return m_isClosingTag;
}


std::string Token::GetTagName() const
{
	return m_tagName;
}

