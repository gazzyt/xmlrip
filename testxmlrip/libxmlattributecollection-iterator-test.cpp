#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include "libxmlattributecollection-iterator.h"
#include "customprinters.h"

using namespace std;


static const xmlChar* testStrings[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };

TEST(LibXmlAttributeCollection_iterator, ContructWithNullSetsEnd) {
	// Arrange
	LibXmlAttributeCollection_iterator end{};

	//Act
	LibXmlAttributeCollection_iterator coll{ nullptr };

	// Assert
	EXPECT_EQ(end, coll);
}

TEST(LibXmlAttributeCollection_iterator, ContructWithFirstNameNullSetsEnd) {
	// Arrange
	const xmlChar* firstName = nullptr;
	LibXmlAttributeCollection_iterator end{};

	//Act
	LibXmlAttributeCollection_iterator coll{ &firstName };

	// Assert
	EXPECT_EQ(end, coll);
}

TEST(LibXmlAttributeCollection_iterator, IndirectionOperatorReturnsStrings) {
	// Arrange
	LibXmlAttributeCollection_iterator end{};

	//Act
	LibXmlAttributeCollection_iterator coll{ testStrings };

	// Assert
	EXPECT_NE(end, coll);
	EXPECT_STREQ(reinterpret_cast< const char *>(testStrings[0]), coll->first);
	EXPECT_STREQ(reinterpret_cast< const char *>(testStrings[1]), coll->second);
}

TEST(LibXmlAttributeCollection_iterator, DereferenceOperatorReturnsStrings) {
	// Arrange
	LibXmlAttributeCollection_iterator end{};

	//Act
	LibXmlAttributeCollection_iterator coll{ testStrings };
	auto attr = *coll;

	// Assert
	EXPECT_NE(end, coll);
	EXPECT_STREQ(reinterpret_cast< const char *>(testStrings[0]), attr.first);
	EXPECT_STREQ(reinterpret_cast< const char *>(testStrings[1]), attr.second);
}

TEST(LibXmlAttributeCollection_iterator, PreIncrementOperatorReturnsNextItem) {
	// Arrange
	LibXmlAttributeCollection_iterator end{};
	LibXmlAttributeCollection_iterator coll{ testStrings };

	//Act
	auto iter = ++coll;

	// Assert
	EXPECT_NE(end, coll);
	EXPECT_NE(end, iter);
	EXPECT_EQ(coll, iter);
	EXPECT_STREQ(reinterpret_cast< const char *>(testStrings[2]), coll->first);
	EXPECT_STREQ(reinterpret_cast< const char *>(testStrings[2]), iter->first);
}

TEST(LibXmlAttributeCollection_iterator, PostIncrementOperatorReturnsCurrentItem) {
	// Arrange
	LibXmlAttributeCollection_iterator end{};
	LibXmlAttributeCollection_iterator coll{ testStrings };

	//Act
	auto iter = coll++;

	// Assert
	EXPECT_NE(end, coll);
	EXPECT_NE(end, iter);
	EXPECT_NE(coll, iter);
	EXPECT_STREQ(reinterpret_cast< const char *>(testStrings[2]), coll->first);
	EXPECT_STREQ(reinterpret_cast< const char *>(testStrings[0]), iter->first);
}

TEST(LibXmlAttributeCollection_iterator, IncrementToEndReturnsEndIterator) {
	// Arrange
	LibXmlAttributeCollection_iterator end{};
	LibXmlAttributeCollection_iterator coll{ testStrings };

	//Act
	auto iter = ++coll;
	++iter;

	// Assert
	EXPECT_EQ(end, iter);
}
