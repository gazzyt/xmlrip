#include <ostream>

#include "memoryutils.h"
#include "xmlstepexpr.h"
#include "exception/xpathexception.h"

using namespace std;

XmlStepExpr::XmlStepExpr(const string& tagName, int documentDepthPredicate)
	:	m_tagName{tagName},
		m_attributePredicates{},
		m_documentDepthPredicate{documentDepthPredicate}
{}

void XmlStepExpr::AddPredicate(XmlAttributePredicate&& predicate)
{
	m_attributePredicates.push_back(predicate);
}

XmlStepExpr::XmlStepExpr(const XmlStepExpr& rhs)
:	m_tagName{rhs.m_tagName},
	m_attributePredicates{rhs.m_attributePredicates},
	m_documentDepthPredicate{rhs.m_documentDepthPredicate}
{}


const string& XmlStepExpr::GetTagName() const
{
	return m_tagName;
}

const vector<XmlAttributePredicate>& XmlStepExpr::GetAttributePredicates() const
{
	return m_attributePredicates;
}

int XmlStepExpr::GetDocumentDepthPredicate() const
{
	return m_documentDepthPredicate;
}


