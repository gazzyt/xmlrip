#include <algorithm>
#include <iostream>
#include <fstream>

#include "internalparserxpathprocessor.h"
#include "xmlexpression.h"

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
	
	unique_ptr<ifstream> inputStream(new ifstream(argv[1]));
	if (!inputStream->is_open())
	{
		cerr << "Failed to open file" << endl;
		return 1;
	}


	string xpathText = argv[2];
	if (xpathText == "xx")
		xpathText = "program[TMSId=\"SH026320890000\"]";
	auto expr = XmlExpression::FromText(xpathText);

	InternalParserXPathProcessor::Run(move(inputStream), move(expr));
}

