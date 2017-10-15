#ifndef TAGPREDICATE_H
#define TAGPREDICATE_H

#include <string>

#include "tag.h"

class TagPredicate
{
public:
	TagPredicate(std::string tagName);

public:
	bool IsMatch(const Tag& tag) const;

private:
	std::string m_tagName;
};

#endif