#include <iostream>

#include "libxmlattributecollection.h"
#include "libxmlutils.h"

#include "libxmlxpathprocessor.h"


using namespace std;

xmlSAXHandler LibXmlXPathProcessor::m_handler
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

xmlEntityPtr LibXmlXPathProcessor::getEntity(void * /*ctx*/, const xmlChar *name)
{
    return xmlGetPredefinedEntity(name);
}

void LibXmlXPathProcessor::StartElement(void *ctx, const xmlChar *name, const xmlChar **atts)
{
	auto pCtx = reinterpret_cast<ParserState*>(ctx);
	auto strName = reinterpret_cast<const char*>(name);
	auto depth = pCtx->expr->ProcessStartTag(strName, LibXmlAttributeCollection{atts});
	if (depth != XmlExpression::NO_MATCH)
	{
		cout << endl << Indent(depth) << XmlElement{XmlElement::Type::tag, strName, LibXmlAttributeCollection{atts}, true, false};
	}
}

void LibXmlXPathProcessor::EndElement(void *ctx, const xmlChar *name)
{
	auto pCtx = reinterpret_cast<ParserState*>(ctx);
	auto strName = reinterpret_cast<const char*>(name);
	auto depth = pCtx->expr->ProcessEndTag(strName);
	if (depth != XmlExpression::NO_MATCH)
	{
		cout << endl << Indent(depth) << XmlElement{XmlElement::Type::tag, strName, false, true};
	}
}

void LibXmlXPathProcessor::Characters(void *ctx, const xmlChar *chars, int len)
{
	auto pCtx = reinterpret_cast<ParserState*>(ctx);
	auto depth = pCtx->expr->GetCurrentMatchDepth();

	if (depth != XmlExpression::NO_MATCH && !isspace(chars, len))
	{
		const char* pChars = reinterpret_cast<const char *>(chars);
		cout << Indent(depth);
		cout.write(pChars, len);
		//cout << endl;
	}
}


void LibXmlXPathProcessor::Run(const char* fileName, std::unique_ptr<XmlExpression> expr)
{
	struct ParserState state {};

	state.expr = move(expr);

	xmlSAXUserParseFile(&m_handler, &state, fileName);

	//unique_ptr<InlineBuffer> buffer = make_unique<InlineBuffer>(move(inputStream), 25000);
	//XmlElementReader elemReader(move(buffer));
	//XmlElementReader_iterator beginIter{ elemReader };
	//XmlElementReader_iterator endIter{};

	//for_each(beginIter, endIter,
	//	[&](const XmlElement& elem)
	//{
	//	if (expr->ProcessElement(elem))
	//	{
	//		cout << elem << endl;
	//	}
	//}
	//);

}

string LibXmlXPathProcessor::Indent(int depth)
{
	if (depth > 0)
	{
		return string(depth * 4, ' ');
	}
	
	return "";
}