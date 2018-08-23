#ifndef XMLPREDICATE_H
#define XMLPREDICATE_H

#include "libxmlattributecollection.h"

class XmlPredicate
{
public:
	virtual void Reset() {};
	virtual bool IsMatch(const LibXmlAttributeCollection& attributes) noexcept = 0;
};


#endif