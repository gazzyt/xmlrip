#include "tag.h"
#include <ostream>

using namespace std;

Tag::Tag(string tagName, bool isOpeningTag, bool isClosingTag)
	: m_tagName(tagName), m_isOpeningTag(isOpeningTag), m_isClosingTag(isClosingTag)
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

bool Tag::operator==(const Tag& t1) const
{
	return (t1.m_tagName == m_tagName) && (t1.m_isOpeningTag == m_isOpeningTag) && (t1.m_isClosingTag == m_isClosingTag);
}

ostream& operator<<(ostream& os, const Tag& tag)
{
	os << "{name:\"" << tag.GetTagName() << "\",isOpeningTag:\"" << tag.IsOpeningTag() << "\",isClosingTag:\"" << tag.IsClosingTag() << "\"}";
	return os;
}
