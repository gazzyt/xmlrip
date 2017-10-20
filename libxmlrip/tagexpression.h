#ifndef TAGEXPRESSION_H
#define TAGEXPRESSION_H

#include <stack>
#include <vector>

#include "tagpredicate.h"

class TagExpression
{
public:
	TagExpression();

public:
	void AddPredicate(TagPredicate predicate);
	bool ProcessTag(const Tag& tag);

private:
	std::vector<TagPredicate> m_predicates;
	std::stack<Tag> m_matchingTags;
};

#endif