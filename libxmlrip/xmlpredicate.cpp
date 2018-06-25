#include <ostream>

#include "memoryutils.h"
#include "xmlpredicate.h"
#include "exception/xpathexception.h"

using namespace std;

XmlPredicate::XmlPredicate(const string& tagName, int documentDepthPredicate)
	:	m_tagName{tagName},
		m_attributePredicates{},
		m_documentDepthPredicate{documentDepthPredicate}
{}

void XmlPredicate::AddPredicate(XmlAttributePredicate&& predicate)
{
	m_attributePredicates.push_back(predicate);
}

XmlPredicate::XmlPredicate(const XmlPredicate& rhs)
:	m_tagName{rhs.m_tagName},
	m_attributePredicates{rhs.m_attributePredicates},
	m_documentDepthPredicate{rhs.m_documentDepthPredicate}
{}


const string& XmlPredicate::GetTagName() const
{
	return m_tagName;
}

const vector<XmlAttributePredicate>& XmlPredicate::GetAttributePredicates() const
{
	return m_attributePredicates;
}

int XmlPredicate::GetDocumentDepthPredicate() const
{
	return m_documentDepthPredicate;
}


