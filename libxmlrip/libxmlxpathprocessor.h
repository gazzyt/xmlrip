#ifndef LIBXMLXPATHPROCESSOR_H
#define LIBXMLXPATHPROCESSOR_H

#include <cassert>
#include <istream>
#include <memory>

#define LIBXML_STATIC

extern "C" {
#include "libxml/parser.h"
}

#include "xmlexpression.h"
#include "libxmlutils.h"

template <class T> class LibXmlXPathProcessor
{
public:
	static void Run(const char* fileName, std::unique_ptr<XmlExpression> expr);
	static void Run(const char* xmlText, size_t xmlTextLength, std::unique_ptr<XmlExpression> expr, T& printer);

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
		T& printer;
		int return_val;
		
		ParserState(std::unique_ptr<XmlExpression> e, T& p)
		: expr{std::move(e)}, printer{p}, return_val{0} {}
	};

};

template <class T>
xmlSAXHandler LibXmlXPathProcessor<T>::m_handler
{
	nullptr, //internalSubsetSAXFunc
	nullptr, //isStandaloneSAXFunc
	nullptr, //hasInternalSubsetSAXFunc
	nullptr, //hasExternalSubsetSAXFunc
	nullptr, //resolveEntitySAXFunc
	&getEntity, //getEntitySAXFunc
	nullptr, //entityDeclSAXFunc
	nullptr, //notationDeclSAXFunc
	nullptr, //attributeDeclSAXFunc
	nullptr, //elementDeclSAXFunc
	nullptr, //unparsedEntityDeclSAXFunc
	nullptr, //setDocumentLocatorSAXFunc
	nullptr, //startDocumentSAXFunc
	nullptr, //endDocumentSAXFunc
	&StartElement, //startElementSAXFunc
	&EndElement, //endElementSAXFunc
	nullptr, //referenceSAXFunc
	&Characters, //charactersSAXFunc
	nullptr, //ignorableWhitespaceSAXFunc
	nullptr, //processingInstructionSAXFunc
	nullptr, //commentSAXFunc
	nullptr, //warningSAXFunc
	nullptr, //errorSAXFunc
	nullptr, //fatalErrorSAXFunc
	nullptr, //getParameterEntitySAXFunc
	nullptr, //cdataBlockSAXFunc
	nullptr, //externalSubsetSAXFunc
	XML_SAX2_MAGIC, //initialized;
	/* The following fields are extensions available only on version 2 */
	nullptr, //void *_private
	nullptr, //startElementNsSAX2Func startElementNs
	nullptr, //endElementNsSAX2Func endElementNs
	nullptr //xmlStructuredErrorFunc serror
};

template <class T>
xmlEntityPtr LibXmlXPathProcessor<T>::getEntity(void * /*ctx*/, const xmlChar *name)
{
    return xmlGetPredefinedEntity(name);
}

template <class T>
void LibXmlXPathProcessor<T>::StartElement(void *ctx, const xmlChar *name, const xmlChar **atts)
{
	auto pCtx = reinterpret_cast<ParserState*>(ctx);
	auto strName = reinterpret_cast<const char*>(name);
	auto depth = pCtx->expr->ProcessStartTag(strName, LibXmlAttributeCollection{atts});
	if (depth != XmlExpression::NO_MATCH)
	{
		pCtx->printer.StartElement(strName, LibXmlAttributeCollection{atts});
	}
}

template <class T>
void LibXmlXPathProcessor<T>::EndElement(void *ctx, const xmlChar *name)
{
	auto pCtx = reinterpret_cast<ParserState*>(ctx);
	auto strName = reinterpret_cast<const char*>(name);
	auto depth = pCtx->expr->ProcessEndTag(strName);
	if (depth != XmlExpression::NO_MATCH)
	{
		pCtx->printer.EndElement();
	}
}

template <class T>
void LibXmlXPathProcessor<T>::Characters(void *ctx, const xmlChar *chars, int len)
{
	auto pCtx = reinterpret_cast<ParserState*>(ctx);
	auto depth = pCtx->expr->GetCurrentMatchDepth();

	if (depth != XmlExpression::NO_MATCH && !isspace(chars, len))
	{
		const char* pChars = reinterpret_cast<const char *>(chars);
		pCtx->printer.PrintText(pChars, len);
	}
}


template <class T>
void LibXmlXPathProcessor<T>::Run(const char* fileName, std::unique_ptr<XmlExpression> expr)
{
	T print;
	struct ParserState state {move(expr), print};

	xmlSAXUserParseFile(&m_handler, &state, fileName);
}

template <class T>
void LibXmlXPathProcessor<T>::Run(const char* xmlText, size_t xmlTextLength, std::unique_ptr<XmlExpression> expr, T& printer)
{
	struct ParserState state {move(expr), printer};

	assert(xmlTextLength < std::numeric_limits<int>::max());

	xmlSAXUserParseMemory(&m_handler, &state, xmlText, static_cast<int>(xmlTextLength));
}

template <class T>
std::string LibXmlXPathProcessor<T>::Indent(int depth)
{
	if (depth > 0)
	{
		return std::string(depth * 4, ' ');
	}
	
	return "";
}

#endif
