#include "tagreader.h"
#include "tagexpression.h"
#include <iostream>
#include <fstream>

using namespace std;

void Usage()
{
	cerr << "Usage: xmlrip <path-to-xml-file>" << endl;
	exit(1);
}

int main(int argc, char** argv)
{
	if (argc != 2)
		Usage();
	
	unique_ptr<ifstream> inputStream(new ifstream(argv[1]));
	if (!inputStream->is_open())
	{
		cerr << "Failed to open file" << endl;
		return 1;
	}

	TagReader tagReader(move(inputStream));
	TagExpression expr{};
	expr.AddPredicate(TagPredicate{"outer"});
	expr.AddPredicate(TagPredicate{"inner"});


	Tag t = tagReader.GetNextTag();
	while (t.GetTagName() != "EOF")
	{
		if (expr.ProcessTag(t))
		{
			cout << t << endl;
		}

		t = tagReader.GetNextTag();
	};
}

