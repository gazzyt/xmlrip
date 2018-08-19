#ifndef XMLEXPRESSION_H
#define XMLEXPRESSION_H

#include <memory>
#include <stack>
#include <vector>

#include "xmlstepexpr.h"
#include "xmlelement.h"
#include "xpathtoken.h"
#include "xpathtokeniser.h"
#include "resettingptr.h"

class XmlExpression
{
public:
	XmlExpression();
	XmlExpression(const XmlExpression& rhs) = delete;

public:
	XmlExpression& operator=(const XmlExpression& rhs) = delete;
	void AddStepExpr(std::unique_ptr<XmlStepExpr> stepExpr);
	const std::vector<std::unique_ptr<XmlStepExpr> >& GetStepExprs() const;
	int GetCurrentMatchDepth() const;
	int GetCurrentDocumentDepth() const;
	template<class T> int ProcessStartTag(const char* tagName, const T& attributes);
	int ProcessEndTag(const char* tagName);
	
	static std::unique_ptr<XmlExpression> FromText(const std::string& text);
	static std::unique_ptr<XmlStepExpr> ReadStepExpr(XPathTokeniser& tokeniser, XPathToken& token);
	static std::unique_ptr<XmlAttributePredicate> ReadAttributePredicate(XPathTokeniser& tokeniser, XPathToken& token);
	
	enum NoMatch {NO_MATCH = -1};

private:
	void SetNextStepExpr();
	
private:
	struct Match { XmlElement element; int documentDepth; };

private:
	std::vector<std::unique_ptr<XmlStepExpr> > m_stepExprs;
	ResettingPtr<XmlStepExpr> m_nextStepExpr;
	std::stack<Match> m_matches;
	int m_matchDepth = NO_MATCH;
	int m_documentDepth = 0;
};

// Process an XML start tag with its attributes
// Returns the current match depth
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
	if (matchIndex == m_stepExprs.size())
	{
		return ++m_matchDepth;
	}

	if (m_nextStepExpr->IsMatch(tagName, attributes, m_documentDepth - lastMatchDocumentDepth))
	{
		m_matches.push(Match { XmlElement{XmlElement::Type::tag, tagName, attributes, true, false}, m_documentDepth });
		
		if (matchIndex == (m_stepExprs.size() - 1))
		{
			// We matched the last stepExpr
			m_matchDepth = 0;
			m_nextStepExpr = nullptr;
			return (m_matchDepth);
		}
		else
		{
			// Only a partial match
			m_matchDepth = NO_MATCH;
			SetNextStepExpr();
			return (m_matchDepth);
		}
	}
	else
	{
		m_matchDepth = NO_MATCH;
		return (m_matchDepth);
	}

}

inline void XmlExpression::SetNextStepExpr()
{
	// assert that we don't call this when all step expressions have been matched already
	assert(m_matches.size() < m_stepExprs.size());
	
	m_nextStepExpr = m_stepExprs[m_matches.size()].get();
}

#endif
