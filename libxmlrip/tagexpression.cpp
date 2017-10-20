#include "tagexpression.h"

using namespace std;

TagExpression::TagExpression()
:	m_predicates{}, m_matchingTags{}
{}

void TagExpression::AddPredicate(TagPredicate predicate)
{
	m_predicates.push_back(predicate);
}

bool TagExpression::ProcessTag(const Tag& tag)
{
	auto matchIndex = m_matchingTags.size();
	auto nextPredicate = m_predicates[matchIndex];
	
	if (nextPredicate.IsMatch(tag))
	{
		m_matchingTags.push(tag);
		return true;
	}
	else
	{
		return false;
	}
}
