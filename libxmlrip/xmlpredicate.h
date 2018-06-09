#ifndef XMLPREDICATE_H
#define XMLPREDICATE_H

#include <memory>
#include <string>

#include "xmlattributepredicate.h"

class XmlPredicate
{
public:
	XmlPredicate(const std::string& tagName, std::unique_ptr<XmlAttributePredicate> attributePredicate,
		int documentDepthPredicate = -1);
	XmlPredicate(const std::string& tagName, int documentDepthPredicate = -1);
	XmlPredicate(const XmlPredicate& rhs);

public:
	XmlPredicate & operator=(const XmlPredicate& rhs) = delete;
	template<class T> bool IsMatch(const char* tagName, const T& attributes, int documentDepth) const;
	const std::string& GetTagName() const;
	const XmlAttributePredicate* GetAttributePredicate() const;
	int GetDocumentDepthPredicate() const;

private:
	std::string m_tagName;
	std::unique_ptr<XmlAttributePredicate> m_attributePredicate;
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

	if (!m_attributePredicate)
		return true;

	for (auto attribute : attributes)
	{
		if (m_attributePredicate->IsMatch(attribute.first, attribute.second))
		{
			return true;
		}
	}
	return false;
}

#endif