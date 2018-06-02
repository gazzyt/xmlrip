#ifndef XMLPREDICATE_H
#define XMLPREDICATE_H

#include <memory>
#include <string>

#include "xmlelement.h"

class XmlPredicate
{
public:
	XmlPredicate(const std::string& tagName, std::unique_ptr<XmlAttribute> attributePredicate = std::unique_ptr<XmlAttribute>(),
		int documentDepthPredicate = -1);
	XmlPredicate(const XmlPredicate& rhs);

public:
	XmlPredicate & operator=(const XmlPredicate& rhs) = delete;
	template<class T> bool IsMatch(const char* tagName, const T& attributes, int documentDepth) const;
	const std::string& GetTagName() const;
	const XmlAttribute* GetAttributePredicate() const;
	int GetDocumentDepthPredicate() const;

private:
	std::string m_tagName;
	std::unique_ptr<XmlAttribute> m_attributePredicate;
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

	for (auto iter = std::begin(attributes); iter != std::end(attributes); ++iter)
	{
		if (m_attributePredicate->GetName() == iter->first && m_attributePredicate->GetValue() == iter->second)
		{
			return true;
		}
	}
	return false;
}

#endif