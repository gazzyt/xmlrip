#ifndef TAGEXPRESSION_H
#define TAGEXPRESSION_H

#include <memory>
#include <stack>
#include <vector>

#include "tagpredicate.h"

class TagExpression
{
public:
	TagExpression();

public:
	void AddPredicate(TagPredicate predicate);
	const std::vector<TagPredicate>& GetPredicates() const;
	bool ProcessTag(const Tag& tag);
	
	static std::unique_ptr<TagExpression> FromText(std::string text);

private:
	std::vector<TagPredicate> m_predicates;
	std::stack<Tag> m_matchingTags;
};

#endif