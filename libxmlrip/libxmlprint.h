#ifndef LIBXMLPRINT_H
#define LIBXMLPRINT_H

#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

#include "libxmlattributecollection.h"

class LibXmlPrint
{
public:
	LibXmlPrint();
	LibXmlPrint(const LibXmlPrint& rhs) = delete;
	~LibXmlPrint();
	
	LibXmlPrint& operator=(const LibXmlPrint& rhs) = delete;

	void StartElement(const char* tagName, LibXmlAttributeCollection attrs) const;
	void EndElement() const;
	void PrintText(const char* text, int length) const;
	
private:
	xmlOutputBufferPtr m_outBuffer;
	xmlTextWriterPtr m_writer;

};

#endif
