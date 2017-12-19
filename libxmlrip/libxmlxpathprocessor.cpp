#include <iostream>



#include "libxmlxpathprocessor.h"


using namespace std;

xmlSAXHandler LibXmlXPathProcessor::m_handler
{
	nullptr, //internalSubsetSAXFunc
	nullptr, //isStandaloneSAXFunc
	nullptr, //hasInternalSubsetSAXFunc
	nullptr, //hasExternalSubsetSAXFunc
	nullptr, //resolveEntitySAXFunc
	nullptr, //getEntitySAXFunc
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
	nullptr, //charactersSAXFunc
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

void LibXmlXPathProcessor::StartElement(void *ctx, const xmlChar *name, const xmlChar **atts)
{
	vector<XmlAttribute> attributes{};

	if (atts)
	{
		const xmlChar **attIter = atts;

		while (*attIter != nullptr)
		{
			auto attName = *attIter;
			++attIter;

			if (*attIter != nullptr)
			{
				auto attValue = *attIter;
				string quotedValue = string{ "\"" } +reinterpret_cast<const char*>(attValue) + "\"";
				attributes.push_back(XmlAttribute{ reinterpret_cast<const char*>(attName), move(quotedValue) });
			}
			++attIter;
		}
	}

	XmlElement elem{ XmlElement::Type::tag, reinterpret_cast<const char*>(name), move(attributes), true, false };

	if (reinterpret_cast<ParserState*>(ctx)->expr->ProcessElement(elem))
	{
		std::cout << elem << endl;
	}

}

void LibXmlXPathProcessor::EndElement(void *ctx, const xmlChar *name)
{

	//XmlElement elem{ XmlElement::Type::tag, reinterpret_cast<const char*>(name), false, true };

	//if (reinterpret_cast<ParserState*>(ctx)->expr->ProcessElement(elem))
	//{
	//	std::cout << elem << endl;
	//}

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
