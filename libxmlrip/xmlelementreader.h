#ifndef XMLELEMENTREADER_H
#define XMLELEMENTREADER_H

#include <istream>
#include <memory>

#include "xmlelement.h"
#include "inlinebuffer.h"

class XmlElementReader
{
public:
	XmlElementReader(std::unique_ptr<InlineBuffer> stream);


public:
	XmlElement GetNextElement();

private:
	XmlElement ReadTag();
	XmlElement ReadDeclaration();
	XmlElement ReadComment();
	std::string ReadText();

	std::unique_ptr<InlineBuffer> m_stream;

	XmlElementReader(const XmlElementReader& src) = delete;
	XmlElementReader operator=(const XmlElementReader& src) = delete;
	
};

#endif
