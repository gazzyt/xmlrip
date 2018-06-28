#ifndef XMLPREDICATE_H
#define XMLPREDICATE_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "xmlattributepredicate.h"

class XmlPredicate
{
public:
	XmlPredicate(const std::string& tagName, int documentDepthPredicate = -1);
	XmlPredicate(const XmlPredicate& rhs);

public:
	void AddPredicate(XmlAttributePredicate&& predicate);
	XmlPredicate & operator=(const XmlPredicate& rhs) = delete;
	template<class T> bool IsMatch(const char* tagName, const T& attributes, int documentDepth) const;
	const std::string& GetTagName() const;
	const std::vector<XmlAttributePredicate>& GetAttributePredicates() const;
	int GetDocumentDepthPredicate() const;

private:
	std::string m_tagName;
	std::vector<XmlAttributePredicate> m_attributePredicates;
	int m_documentDepthPredicate;
};


template<class T> bool XmlPredicate::IsMatch(const char* tagName, const T& attributes, int documentDepth) const
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