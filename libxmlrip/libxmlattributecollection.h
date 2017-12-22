#ifndef LIBXMLATTRIBUTECOLLECTION_H
#define LIBXMLATTRIBUTECOLLECTION_H

#include "libxml/xmlstring.h"

#include "libxmlattributecollection-iterator.h"


class LibXmlAttributeCollection
{
public:
	typedef LibXmlAttributeCollection_iterator const_iterator;

public:
	LibXmlAttributeCollection(const xmlChar** attributes) : m_attributes(attributes)
	{};

	const_iterator begin() const
	{
		return LibXmlAttributeCollection_iterator{ m_attributes };
	}

	const_iterator end() const
	{
		return LibXmlAttributeCollection_iterator{};
	}


private:
	const xmlChar** m_attributes;
};


#endif
