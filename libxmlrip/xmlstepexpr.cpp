#include <ostream>

#include "libxmlattributecollection-iterator.h"
#include "memoryutils.h"
#include "xmlstepexpr.h"
#include "exception/xpathexception.h"

using namespace std;

XmlStepExpr::XmlStepExpr(const string& tagName, int documentDepthPredicate)
	:	m_tagName{tagName},
		m_predicates{},
		m_documentDepthPredicate{documentDepthPredicate}
{}

void XmlStepExpr::AddPredicate(unique_ptr<XmlPredicate> predicate)
{
	m_predicates.push_back(move(predicate));
}


const string& XmlStepExpr::GetTagName() const
{
	return m_tagName;
}

const vector<unique_ptr<XmlPredicate> >& XmlStepExpr::GetPredicates() const
{
	return m_predicates;
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

	if (m_predicates.size() == 0)
		return true;

	return std::all_of(std::begin(m_predicates),
		std::end(m_predicates),
		[&attributes](const auto& a){ return a->IsMatch(attributes); });
}

// Resets any matching state
void XmlStepExpr::Reset()
{
	for_each(begin(m_predicates),
		end(m_predicates),
		[] (auto& p) { p->Reset(); });
}
