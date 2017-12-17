#include <iostream>

#include "internalparserxpathprocessor.h"

#include "inlinebuffer.h"
#include "xmlelementreader.h"
#include "xmlelementreader-iterator.h"

using namespace std;


void InternalParserXPathProcessor::Run(std::unique_ptr<std::istream> inputStream, std::unique_ptr<XmlExpression> expr)
{
	unique_ptr<InlineBuffer> buffer = make_unique<InlineBuffer>(move(inputStream), 25000);
	XmlElementReader elemReader(move(buffer));
	XmlElementReader_iterator beginIter{ elemReader };
	XmlElementReader_iterator endIter{};

	for_each(beginIter, endIter,
		[&](const XmlElement& elem)
	{
		if (expr->ProcessElement(elem))
		{
			cout << elem << endl;
		}
	}
	);

}
