#ifndef XMLSTEPEXPR_H
#define XMLSTEPEXPR_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "libxmlattributecollection.h"
#include "xmlattributepredicate.h"

class XmlStepExpr
{
public:
	XmlStepExpr(const std::string& tagName, int documentDepthPredicate = -1);
	XmlStepExpr(const XmlStepExpr& rhs);

public:
	void AddPredicate(XmlAttributePredicate&& predicate);
	XmlStepExpr & operator=(const XmlStepExpr& rhs) = delete;
	bool IsMatch(const char* tagName, const LibXmlAttributeCollection& attributes, int documentDepth) const;
	const std::string& GetTagName() const;
	const std::vector<XmlAttributePredicate>& GetAttributePredicates() const;
	int GetDocumentDepthPredicate() const;

private:
	std::string m_tagName;
	std::vector<XmlAttributePredicate> m_attributePredicates;
	int m_documentDepthPredicate;
};



#endif