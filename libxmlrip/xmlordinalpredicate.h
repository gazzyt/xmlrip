#ifndef XMLORDINALPREDICATE_H
#define XMLORDINALPREDICATE_H

#include <string>

#include "xmlattribute.h"
#include "xmlpredicate.h"
#include "libxmlattributecollection.h"
#include "libxmlattributecollection-iterator.h"

class XmlOrdinalPredicate : public XmlPredicate
{
public:
	XmlOrdinalPredicate(unsigned int ordinal) noexcept;

public:
	unsigned int GetOrdinal() const;

	virtual void Reset();
	virtual bool IsMatch(const LibXmlAttributeCollection& attributes) noexcept;

private:
	const unsigned int m_ordinal;
	unsigned int m_count;
};

#endif