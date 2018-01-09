#ifndef LIBXMLXPATHPROCESSOR_H
#define LIBXMLXPATHPROCESSOR_H

#include <istream>
#include <memory>

#define LIBXML_STATIC

extern "C" {
#include "libxml/parser.h"
}

#include "xmlexpression.h"

class LibXmlXPathProcessor
{
public:
	static void Run(const char* fileName, std::unique_ptr<XmlExpression> expr);

	LibXmlXPathProcessor() = delete;
	
private:
	static xmlSAXHandler m_handler;

	static xmlEntityPtr getEntity(void *user_data, const xmlChar *name);
	static void StartElement(void *ctx, const xmlChar *name, const xmlChar **atts);
	static void EndElement(void *ctx, const xmlChar *name);
	static void Characters(void *ctx, const xmlChar *chars, int len);
	static std::string Indent(int depth);

	struct ParserState {
		std::unique_ptr<XmlExpression> expr;
		int return_val;
	};

};


#endif
