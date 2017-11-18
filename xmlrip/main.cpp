#include <algorithm>
#include <iostream>
#include <fstream>

#include "inlinebuffer.h"
#include "xmlelementreader.h"
#include "xmlelementreader-iterator.h"
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

	unique_ptr<InlineBuffer> buffer = make_unique<InlineBuffer>(move(inputStream), 25000);
	XmlElementReader elemReader(move(buffer));
	XmlElementReader_iterator beginIter{elemReader};
	XmlElementReader_iterator endIter{};
	auto expr = XmlExpression::FromText(argv[2]);

	for_each(beginIter, endIter, 
		[&] (const XmlElement& elem) 
		{
			if (expr->ProcessElement(elem))
			{
				cout << elem << endl;
			}
		}
	);
	
}

