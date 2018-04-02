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
	int GetCurrentMatchDepth() const;
	int GetCurrentDocumentDepth() const;
	template<class T> int ProcessStartTag(const char* tagName, const T& attributes);
	int ProcessEndTag(const char* tagName);
	
	static std::unique_ptr<XmlExpression> FromText(std::string text);
	
	enum NoMatch {NO_MATCH = -1};

private:
	std::vector<XmlPredicate> m_predicates;
	std::stack<XmlElement> m_matchingElements;
	int m_matchDepth = NO_MATCH;
	int m_documentDepth = 0;
};

template<class T> int XmlExpression::ProcessStartTag(const char* tagName, const T& attributes)
{
	++m_documentDepth;
	
	const auto matchIndex = m_matchingElements.size();
	
	// If we already have a full match for all predicates
	if (matchIndex == m_predicates.size())
	{
		return ++m_matchDepth;
	}

	auto& nextPredicate = m_predicates[matchIndex];
	
	if (nextPredicate.IsMatch(tagName, attributes, m_documentDepth - 1))
	{
		m_matchingElements.push(XmlElement{XmlElement::Type::tag, tagName, attributes, true, false});
		
		if (matchIndex == (m_predicates.size() - 1))
		{
			// We matched the last predicate
			m_matchDepth = 0;
			return (m_matchDepth);
		}
		else
		{
			// Only a partial match
			m_matchDepth = NO_MATCH;
			return (m_matchDepth);
		}
	}
	else
	{
		m_matchDepth = NO_MATCH;
		return (m_matchDepth);
	}

}

#endif