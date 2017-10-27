#include <algorithm>
#include <iostream>
#include <fstream>

#include "tagreader.h"
#include "tagreader-iterator.h"
#include "tagexpression.h"

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

	TagReader tagReader(move(inputStream));
	TagReader_iterator beginIter{tagReader};
	TagReader_iterator endIter{};
	auto expr = TagExpression::FromText(argv[2]);

	for_each(beginIter, endIter, 
		[&] (const Tag& t) 
		{
			if (expr->ProcessTag(t))
			{
				cout << t << endl;
			}
		}
	);
	
}

