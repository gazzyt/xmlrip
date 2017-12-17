#ifndef INTERNALPARSERXPATHPROCESSOR_H
#define INTERNALPARSERXPATHPROCESSOR_H

#include <istream>
#include <memory>

#include "xmlexpression.h"

class InternalParserXPathProcessor
{
public:
	static void Run(std::unique_ptr<std::istream> inputStream, std::unique_ptr<XmlExpression> expr);

	InternalParserXPathProcessor() = delete;
	
};

#endif
