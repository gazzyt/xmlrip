#include <algorithm>
#include <iostream>
#include <fstream>

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

	try
	{
		auto expr = XmlExpression::FromText(xpathText);
		LibXmlXPathProcessor::Run(argv[1], move(expr));
	}
	catch(BaseException& e)
	{
		cerr << e << endl;
	}

	cout << endl << endl;
}

