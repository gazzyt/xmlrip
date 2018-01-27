#include <algorithm>
#include <iostream>
#include <fstream>

#include "internalparserxpathprocessor.h"
#include "libxmlxpathprocessor.h"
#include "xmlexpression.h"
#include "exception/baseexception.h"

using namespace std;

void Usage()
{
	cerr << "Usage: xmlrip <path-to-xml-file> <xpath>" << endl;
	exit(1);
}

int main(int argc, char** argv)
{
	if (argc != 3)
		Usage();
	

	string xpathText = argv[2];
	if (xpathText == "xx")
		xpathText = "program[TMSId=\"SH026320890000\"]";
	auto expr = XmlExpression::FromText(xpathText);

	try
	{
#ifdef USE_INTERNAL_PARSER
	InternalParserXPathProcessor::Run(argv[1], move(expr));
#else
	LibXmlXPathProcessor::Run(argv[1], move(expr));
#endif
	}
	catch(BaseException& e)
	{
		cerr << e << endl;
	}

	cout << endl << endl;
}

