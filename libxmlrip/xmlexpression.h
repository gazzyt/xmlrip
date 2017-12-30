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
	template<class T> bool ProcessStartTag(const char* tagName, const T& attributes);
	bool ProcessEndTag(const char* tagName);
	
	static std::unique_ptr<XmlExpression> FromText(std::string text);

private:
	bool ProcessTag(const XmlElement& elem);

	std::vector<XmlPredicate> m_predicates;
	std::stack<XmlElement> m_matchingElements;
};

template<class T> bool XmlExpression::ProcessStartTag(const char* tagName, const T& attributes)
{
	const auto matchIndex = m_matchingElements.size();
	
	// If we already have a full match for all predicates
	if (matchIndex == m_predicates.size())
	{
		return true;
	}

	auto& nextPredicate = m_predicates[matchIndex];
	
	if (nextPredicate.IsMatch(tagName, attributes))
	{
		m_matchingElements.push(XmlElement{XmlElement::Type::tag, tagName, attributes, true, false});
		
		if (matchIndex == (m_predicates.size() - 1))
		{
			// We matched the last predicate
			return true;
		}
		else
		{
			// Only a partial match
			return false;
		}
	}
	else
	{
		return false;
	}

}

#endif