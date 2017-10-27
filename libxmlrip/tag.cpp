#include "tag.h"
#include <ostream>

using namespace std;

Tag::Tag(string tagName, bool isOpeningTag, bool isClosingTag) noexcept
	: m_tagName(tagName), m_attributeText{}, m_isOpeningTag(isOpeningTag), m_isClosingTag(isClosingTag)
{}

Tag::Tag(string tagName, string attributeText, bool isOpeningTag, bool isClosingTag) noexcept
	: m_tagName(tagName), m_attributeText{attributeText}, m_isOpeningTag(isOpeningTag), m_isClosingTag(isClosingTag)
{}

bool Tag::IsOpeningTag() const
{
	return m_isOpeningTag;
}

bool Tag::IsClosingTag() const
{
	return m_isClosingTag;
}


string Tag::GetTagName() const
{
	return m_tagName;
}

string Tag::GetAttributeText() const
{
	return m_attributeText;
}

bool Tag::IsMatch(const Tag& t1) const
{
	return (t1.m_tagName == m_tagName);
}

bool Tag::operator==(const Tag& t1) const
{
	return (t1.m_tagName == m_tagName) && (t1.m_isOpeningTag == m_isOpeningTag) && (t1.m_isClosingTag == m_isClosingTag);
}

ostream& operator<<(ostream& os, const Tag& tag)
{
	auto opening = (tag.IsClosingTag() && !tag.IsOpeningTag()) ? "</" : "<";
	auto closing = (tag.IsClosingTag() && tag.IsOpeningTag()) ? "/>" : ">";

	os << opening;
	os << tag.GetTagName();
	os << tag.GetAttributeText();
	os << closing;

	return os;
}

Tag Tag::FromText(std::string text, bool isOpeningTag, bool isClosingTag)
{
	auto firstSpace = text.find_first_of(' ');
	
	if (firstSpace == string::npos)
	{
		return Tag(text, isOpeningTag, isClosingTag);
	}
	else
	{
		return Tag(text.substr(0, firstSpace), text.substr(firstSpace), isOpeningTag, isClosingTag);
	}
}
