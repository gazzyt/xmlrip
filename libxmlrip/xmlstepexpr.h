#ifndef XMLSTEPEXPR_H
#define XMLSTEPEXPR_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "xmlattributepredicate.h"

class XmlStepExpr
{
public:
	XmlStepExpr(const std::string& tagName, int documentDepthPredicate = -1);
	XmlStepExpr(const XmlStepExpr& rhs);

public:
	void AddPredicate(XmlAttributePredicate&& predicate);
	XmlStepExpr & operator=(const XmlStepExpr& rhs) = delete;
	template<class T> bool IsMatch(const char* tagName, const T& attributes, int documentDepth) const;
	const std::string& GetTagName() const;
	const std::vector<XmlAttributePredicate>& GetAttributePredicates() const;
	int GetDocumentDepthPredicate() const;

private:
	std::string m_tagName;
	std::vector<XmlAttributePredicate> m_attributePredicates;
	int m_documentDepthPredicate;
};


template<class T> bool XmlStepExpr::IsMatch(const char* tagName, const T& attributes, int documentDepth) const
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


#endif