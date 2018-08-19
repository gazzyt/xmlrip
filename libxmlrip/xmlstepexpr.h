#ifndef XMLSTEPEXPR_H
#define XMLSTEPEXPR_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "libxmlattributecollection.h"
#include "xmlpredicate.h"

class XmlStepExpr
{
public:
	XmlStepExpr(const std::string& tagName, int documentDepthPredicate = -1);
	XmlStepExpr(const XmlStepExpr& rhs) = delete;

public:
	void AddPredicate(std::unique_ptr<XmlPredicate> predicate);
	XmlStepExpr & operator=(const XmlStepExpr& rhs) = delete;
	bool IsMatch(const char* tagName, const LibXmlAttributeCollection& attributes, int documentDepth) const;
	const std::string& GetTagName() const;
	const std::vector<std::unique_ptr<XmlPredicate> >& GetPredicates() const;
	int GetDocumentDepthPredicate() const;
	void Reset();

private:
	std::string m_tagName;
	std::vector<std::unique_ptr<XmlPredicate> > m_predicates;
	int m_documentDepthPredicate;
};



#endif