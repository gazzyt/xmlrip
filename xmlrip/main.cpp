#include "tagreader.h"
#include "tagexpression.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	cout << "Hello world" << endl;

	unique_ptr<ifstream> inputStream(new ifstream("test.xml"));
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

