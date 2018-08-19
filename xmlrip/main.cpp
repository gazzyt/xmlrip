#include <algorithm>
#include <iostream>
#include <fstream>

#include "libxmlprint.h"
#include "libxmlxpathprocessor.h"
#include "xpathreader.h"
#include "xmlexpression.h"
#include "exception/baseexception.h"
#include "exception/xpathexception.h"

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
		xpathText = "//program[@TMSId=\"SH026320890000\"]";

	try
	{
		auto expr = XPathReader::FromText(xpathText);
		LibXmlXPathProcessor<LibXmlPrint>::Run(argv[1], move(expr));
	}
	catch(XPathException& e)
	{
		cerr << e.what() << endl;
		cerr << xpathText << endl;
		cerr << string(e.GetPosition(), '-') << '^' << endl;
	}
	catch(BaseException& e)
	{
		cerr << e.what() << endl;
	}

	cout << endl << endl;
}

