#ifndef XMLELEMENTREADER_H
#define XMLELEMENTREADER_H

#include "xmlelement.h"
#include <istream>
#include <memory>

class XmlElementReader
{
public:
	XmlElementReader(std::unique_ptr<std::istream> stream);


public:
	XmlElement GetNextElement();

private:
	XmlElement ReadTag();
	XmlElement ReadDeclaration();
	XmlElement ReadComment();
	
	std::unique_ptr<std::istream> m_stream;

	XmlElementReader(const XmlElementReader& src) = delete;
	XmlElementReader operator=(const XmlElementReader& src) = delete;
	
};

#endif
