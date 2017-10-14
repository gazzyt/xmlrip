#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <algorithm>
#include <memory>
#include <sstream>

#include "tagreader.h"

using namespace std;

static const string simpleXml = "<a></a>";
static const auto simpleXmlTags = {
	Tag{"a", true, false}, 
	Tag{"a", false, true}
};


TEST(TagReader, CreatesCorrectTokensForSimpleXml) {
	int tagIndex = 0;
	auto xmlStream = make_unique<istringstream>(simpleXml);
	TagReader tagReader{move(xmlStream)};
	
	for_each(begin(simpleXmlTags), end(simpleXmlTags), 
		[&] (const Tag& t) 
		{
			EXPECT_EQ(t,tagReader.GetNextTag()) << "Tag number " << tagIndex << " did not have expected value";
			++tagIndex;
		}
	);
}
