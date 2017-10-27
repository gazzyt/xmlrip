#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <algorithm>
#include <memory>
#include <sstream>

#include "tagreader-iterator.h"

using namespace std;

static const string simpleXml = "<a></a>";
static const auto simpleXmlTags = {
	Tag{"a", true, false}, 
	Tag{"a", false, true}
};


TEST(TagReader_iterator, CreatesCorrectTokensForSimpleXml) {
	auto xmlStream = make_unique<istringstream>(simpleXml);
	TagReader tagReader{move(xmlStream)};
	TagReader_iterator beginIter{tagReader};
	TagReader_iterator endIter{};
	
	vector<Tag> actualTags{};
	
	copy(beginIter, endIter, back_inserter(actualTags));
	
	ASSERT_EQ(simpleXmlTags.size(), actualTags.size());
	EXPECT_TRUE(equal(begin(simpleXmlTags), end(simpleXmlTags), begin(actualTags)));
}
