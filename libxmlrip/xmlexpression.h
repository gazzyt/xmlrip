#ifndef XMLEXPRESSION_H
#define XMLEXPRESSION_H

#include <memory>
#include <stack>
#include <vector>

#include "xmlpredicate.h"
#include "xmlelement.h"
#include "xpathtoken.h"
#include "xpathtokeniser.h"

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
	
	static std::unique_ptr<XmlExpression> FromText(const std::string& text);
	static XmlPredicate ReadPredicate(XPathTokeniser& tokeniser, XPathToken& token);
	
	enum NoMatch {NO_MATCH = -1};

private:
	struct Match { XmlElement element; int documentDepth; };

private:
	std::vector<XmlPredicate> m_predicates;
	std::stack<Match> m_matches;
	int m_matchDepth = NO_MATCH;
	int m_documentDepth = 0;
};

template<class T> int XmlExpression::ProcessStartTag(const char* tagName, const T& attributes)
{
	int lastMatchDocumentDepth = 0;
	
	++m_documentDepth;
	
	const auto matchIndex = m_matches.size();
	
	if (matchIndex > 0)
	{
		lastMatchDocumentDepth = m_matches.top().documentDepth;
	}
	
	// If we already have a full match for all predicates
	if (matchIndex == m_predicates.size())
	{
		return ++m_matchDepth;
	}

	auto& nextPredicate = m_predicates[matchIndex];
	
	if (nextPredicate.IsMatch(tagName, attributes, m_documentDepth - lastMatchDocumentDepth))
	{
		//m_matchingElements.push(XmlElement{XmlElement::Type::tag, tagName, attributes, true, false});
		m_matches.push(Match { XmlElement{XmlElement::Type::tag, tagName, attributes, true, false}, m_documentDepth });
		
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