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
	
	if (tag.IsOpeningTag())
	{
	
		// If we already have a full match for all predicates
		if (matchIndex == m_predicates.size())
		{
			return true;
		}
	
		auto nextPredicate = m_predicates[matchIndex];
		
		if (nextPredicate.IsMatch(tag))
		{
			if (!tag.IsClosingTag())
			{
				m_matchingTags.push(tag);
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (tag.IsClosingTag())
	{
		// Does this closing tag close the last matched tag?
		if ((matchIndex > 0) && m_matchingTags.top().IsMatch(tag))
		{
			// It does
			m_matchingTags.pop();
			return true;
		}
		
		// If we already have a full match for all predicates
		if (matchIndex == m_predicates.size())
		{
			return true;
		}
		
		return false;
	}
	
	return false; // We only get here if that tag is neither opening nor closing
}
