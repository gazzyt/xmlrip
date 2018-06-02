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
	for_each(begin(coll), end(coll), [&](auto) {++count; });

	// Assert
	EXPECT_EQ(2U, count);
}

TEST(LibXmlAttributeCollection, GlobalBeginIteratesTwoTimes) {
	// Arrange
	LibXmlAttributeCollection coll(testStrings);
	unsigned count = 0;

	//Act
	for_each(begin(coll), end(coll), [&](auto) {++count; });

	// Assert
	EXPECT_EQ(2U, count);
}
