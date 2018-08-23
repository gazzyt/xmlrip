#include <cassert>

#include "xmlexpression.h"
#include "stringutils.h"
#include "exception/xpathexception.h"

using namespace std;

XmlExpression::XmlExpression()
:	m_stepExprs{}, m_nextStepExpr{}, m_matches{}
{}

void XmlExpression::AddStepExpr(unique_ptr<XmlStepExpr> stepExpr)
{
	m_stepExprs.push_back(move(stepExpr));
	m_nextStepExpr = m_stepExprs[0].get();
}

const vector<unique_ptr<XmlStepExpr> >& XmlExpression::GetStepExprs() const
{
	return m_stepExprs;
}

// Returns the current document depth relative to the last full xpath match.
// A value of NO_MATCH indicates we haven't had a full xpath match yet
// A value of 0 indicates the last XML tag provided full xpath match
// A value > 0 indicates descendant tags of the full xpath match tag
int XmlExpression::GetCurrentMatchDepth() const
{
	return m_matchDepth;
}

// Returns the current document depth within the XML document
int XmlExpression::GetCurrentDocumentDepth() const
{
	return m_documentDepth;
}

// Process an XML end tag
// Returns the current match depth
int XmlExpression::ProcessEndTag(const char* tagName)
{
	--m_documentDepth;
	
	const auto matchIndex = m_matches.size();
	
	// Does this closing tag close the last matched tag?
	if ((matchIndex > 0) && m_matches.top().element.GetTagName() == tagName)
	{
		// It does
		m_matches.pop();

		if (matchIndex == m_stepExprs.size())
		{
			// We closed the tag that gave us the full match
			// Decrement m_matchDepth to NO_MATCH and
			// return 0 as this closing tag is the final part of the match
			assert(m_matchDepth == 0);
			return m_matchDepth--;
		}
		else
		{
			// Only a partial match
			SetNextStepExpr();
			return NO_MATCH;
		}
	}
	
	// If we already have a full match for all stepExprs
	if (matchIndex == m_stepExprs.size())
	{
		return m_matchDepth--;
	}
	
	return NO_MATCH;
}

