#include <unistd.h>
#include "libxmlprint.h"
#include "exception/printexception.h"

using namespace std;

LibXmlPrint::LibXmlPrint()
:	m_outBuffer(nullptr),
	m_writer(nullptr)
{
	m_outBuffer = xmlOutputBufferCreateFd(STDOUT_FILENO, NULL);
	if (m_outBuffer == NULL) {
		throw PrintException("Error creating output buffer");
	}
	
	m_writer = xmlNewTextWriter(m_outBuffer);
	if (m_writer == NULL) {
		throw PrintException("Error creating writer");
	}

	xmlTextWriterSetIndent(m_writer, 2);
}

LibXmlPrint::~LibXmlPrint()
{
    xmlFreeTextWriter(m_writer);
}

void LibXmlPrint::StartElement(const char* tagName, LibXmlAttributeCollection attrs) const
{
    int rc = xmlTextWriterStartElement(m_writer, BAD_CAST tagName);
    if (rc < 0) {
        throw PrintException("Error at xmlTextWriterStartElement");
    }
	
	for (auto iter = begin(attrs); iter != end(attrs); ++iter)
	{
		rc = xmlTextWriterWriteAttribute(m_writer, BAD_CAST iter->first, BAD_CAST iter->second);
		if (rc < 0) {
			throw PrintException("Error at xmlTextWriterWriteAttribute\n");
		}
	}
}

void LibXmlPrint::EndElement() const
{
    int rc = xmlTextWriterEndElement(m_writer);
    if (rc < 0) {
        throw PrintException("Error at xmlTextWriterEndElement");
    }
}

void LibXmlPrint::PrintText(const char* text, int length) const
{
	int rc = xmlTextWriterWriteString(m_writer, BAD_CAST string(text, length).c_str());
    if (rc < 0) {
        throw PrintException("Error at xmlTextWriterWriteString");
    }
}
