#include <ostream>

#include "libxmlattributecollection-iterator.h"
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

bool XmlStepExpr::IsMatch(const char* tagName, const LibXmlAttributeCollection& attributes, int documentDepth) const
{
	bool tagMatch = m_tagName == tagName;

	if (!tagMatch)
		return false;
	
	bool depthMatch = m_documentDepthPredicate == -1 || m_documentDepthPredicate == documentDepth;

	if (!depthMatch)
		return false;

	if (m_attributePredicates.size() == 0)
		return true;

	return std::all_of(std::begin(m_attributePredicates),
		std::end(m_attributePredicates),
		[&attributes](const auto& a){ return a.IsMatch(attributes); });
}

