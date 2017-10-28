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
static const vector<Tag> simpleXmlTags = {
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

TEST(TagReader_iterator, PreIncrementReturnNewIterator) {
	// Arrange
	auto xmlStream = make_unique<istringstream>(simpleXml);
	TagReader tagReader{move(xmlStream)};
	TagReader_iterator beginIter{tagReader};
	TagReader_iterator endIter{};
	
	// Act
	TagReader_iterator newIter = ++beginIter;
	
	// Assert
	EXPECT_EQ(simpleXmlTags[1], *beginIter);
	EXPECT_EQ(simpleXmlTags[1], *newIter);
}

TEST(TagReader_iterator, PostIncrementReturnOldIterator) {
	// Arrange
	auto xmlStream = make_unique<istringstream>(simpleXml);
	TagReader tagReader{move(xmlStream)};
	TagReader_iterator beginIter{tagReader};
	TagReader_iterator endIter{};
	
	// Act
	TagReader_iterator oldIter = beginIter++;
	
	// Assert
	EXPECT_EQ(simpleXmlTags[1], *beginIter);
	EXPECT_EQ(simpleXmlTags[0], *oldIter);
}
