#include "xmlexpression.h"
#include "stringutils.h"

using namespace std;

XmlExpression::XmlExpression()
:	m_predicates{}, m_matchingElements{}
{}

void XmlExpression::AddPredicate(XmlPredicate predicate)
{
	m_predicates.push_back(predicate);
}

const vector<XmlPredicate>& XmlExpression::GetPredicates() const
{
	return m_predicates;
}

bool XmlExpression::ProcessElement(const XmlElement& elem)
{
	switch (elem.GetType())
	{
		case XmlElement::Type::tag:
		case XmlElement::Type::text:
			return ProcessTag(elem);
			
		// Skip these types as not interesting
		default:
			return false;
	};
}

bool XmlExpression::ProcessTag(const XmlElement& elem)
{
	const auto matchIndex = m_matchingElements.size();
	
	if (elem.IsOpeningTag())
	{
	
		// If we already have a full match for all predicates
		if (matchIndex == m_predicates.size())
		{
			return true;
		}
	
		auto nextPredicate = m_predicates[matchIndex];
		
		if (nextPredicate.IsMatch(elem))
		{
			if (!elem.IsClosingTag())
			{
				m_matchingElements.push(elem);
			}
			
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
	else if (elem.IsClosingTag())
	{
		// Does this closing tag close the last matched tag?
		if ((matchIndex > 0) && m_matchingElements.top().IsMatch(elem))
		{
			// It does
			m_matchingElements.pop();

			if (matchIndex == m_predicates.size())
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
		
		// If we already have a full match for all predicates
		if (matchIndex == m_predicates.size())
		{
			return true;
		}
		
		return false;
	}
	
	return false; // We only get here if that tag is neither opening nor closing
}

unique_ptr<XmlExpression> XmlExpression::FromText(string text)
{
	auto retval = make_unique<XmlExpression>();
	auto tagNames = split(text, '/');
	
	for ( auto tagName : tagNames)
	{
		retval->AddPredicate(XmlPredicate(tagName));
	}
	
	return retval;
}
