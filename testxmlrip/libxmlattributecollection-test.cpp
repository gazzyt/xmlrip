#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include "libxmlattributecollection.h"
#include "customprinters.h"

using namespace std;


static const xmlChar* testStrings[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2", nullptr };

TEST(LibXmlAttributeCollection, MemberBeginIteratesTwoTimes) {
	// Arrange
	LibXmlAttributeCollection coll(testStrings);
	unsigned count = 0;

	//Act
	for (auto iter = coll.begin(); iter != coll.end(); ++iter)
	{
		++count;
	}

	// Assert
	EXPECT_EQ(2, count);
}

TEST(LibXmlAttributeCollection, GlobalBeginIteratesTwoTimes) {
	// Arrange
	LibXmlAttributeCollection coll(testStrings);
	unsigned count = 0;

	//Act
	for (auto iter = begin(coll); iter != end(coll); ++iter)
	{
		++count;
	}

	// Assert
	EXPECT_EQ(2, count);
}
