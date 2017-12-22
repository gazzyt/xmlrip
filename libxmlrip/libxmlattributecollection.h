#ifndef LIBXMLATTRIBUTECOLLECTION_H
#define LIBXMLATTRIBUTECOLLECTION_H

#include "libxml/xmlstring.h"


class LibXmlAttributeCollection
{
public:
	LibXmlAttributeCollection(const xmlChar** attributes) : m_attributes(attributes)
	{};


private:
	const xmlChar** m_attributes;
};


#endif
