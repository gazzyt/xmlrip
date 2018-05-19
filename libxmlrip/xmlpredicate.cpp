#include <ostream>

#include "memoryutils.h"
#include "xmlpredicate.h"
#include "exception/xpathexception.h"

using namespace std;

XmlPredicate::XmlPredicate(string tagName, std::unique_ptr<XmlAttribute> attributePredicate, int documentDepthPredicate)
	:	m_tagName(tagName), m_attributePredicate(move(attributePredicate)),
		m_documentDepthPredicate(documentDepthPredicate)
{}

XmlPredicate::XmlPredicate(const XmlPredicate& rhs)
:	m_tagName(rhs.m_tagName),
	m_attributePredicate(copy_unique(rhs.m_attributePredicate)),
	m_documentDepthPredicate(rhs.m_documentDepthPredicate)
{}


const string& XmlPredicate::GetTagName() const
{
	return m_tagName;
}

const XmlAttribute* XmlPredicate::GetAttributePredicate() const
{
	return m_attributePredicate.get();
}

int XmlPredicate::GetDocumentDepthPredicate() const
{
	return m_documentDepthPredicate;
}


