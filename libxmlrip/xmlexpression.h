#ifndef XMLEXPRESSION_H
#define XMLEXPRESSION_H

#include <memory>
#include <stack>
#include <vector>

#include "xmlpredicate.h"

class XmlExpression
{
public:
	XmlExpression();

public:
	void AddPredicate(XmlPredicate predicate);
	const std::vector<XmlPredicate>& GetPredicates() const;
	bool ProcessElement(const XmlElement& elem);
	
	static std::unique_ptr<XmlExpression> FromText(std::string text);

private:
	bool ProcessTag(const XmlElement& elem);

	std::vector<XmlPredicate> m_predicates;
	std::stack<XmlElement> m_matchingElements;
};

#endif