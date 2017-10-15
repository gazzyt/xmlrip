#include "tagpredicate.h"
#include <ostream>

using namespace std;

TagPredicate::TagPredicate(string tagName)
	: m_tagName(tagName)
{}


bool TagPredicate::IsMatch(const Tag& tag) const
{
	return (m_tagName == tag.GetTagName() && tag.IsOpeningTag());
}

