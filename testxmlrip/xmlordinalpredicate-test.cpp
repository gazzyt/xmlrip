#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <sstream>

#include "xmlstreammodifiers.h"
#include "customprinters.h"

#include "xmlordinalpredicate.h"

using namespace std;

/******************************************************************************************/
/* constructor tests                                                                      */
/******************************************************************************************/

TEST(XmlOrdinalPredicate, ConstructorCreatesCorrectPredicate) {
	// Arrange
	
	// Act
	XmlOrdinalPredicate predicate(7);
	
	// Assert
	EXPECT_EQ(7U, predicate.GetOrdinal());
}


/******************************************************************************************/
/* IsMatch(const LibXmlAttributeCollection&) tests                                                                          */
/******************************************************************************************/

TEST(XmlOrdinalPredicate, IsMatchReturnsTrueWhenCalledOrdinalTimes) {
	// Arrange
	XmlOrdinalPredicate predicate(2);
	const xmlChar* attrs[] = {
		BAD_CAST "aname", BAD_CAST "avalue",
		BAD_CAST "bname", BAD_CAST "bvalue",
		nullptr
	};
	LibXmlAttributeCollection libXmlAttrs{attrs};
	
	// Act
	predicate.IsMatch(libXmlAttrs);
	
	// Assert
	EXPECT_TRUE(predicate.IsMatch(libXmlAttrs));
}

TEST(XmlOrdinalPredicate, IsMatchReturnsFalseWhenCalledLessThanOrdinalTimes) {
	// Arrange
	XmlOrdinalPredicate predicate(2);
	const xmlChar* attrs[] = {
		BAD_CAST "aname", BAD_CAST "avalue",
		BAD_CAST "bname", BAD_CAST "bvalue",
		nullptr
	};
	LibXmlAttributeCollection libXmlAttrs{attrs};
	
	// Act
	
	// Assert
	EXPECT_FALSE(predicate.IsMatch(libXmlAttrs));
}

TEST(XmlOrdinalPredicate, IsMatchReturnsFalseWhenCalledMoreThatOrdinalTimes) {
	// Arrange
	XmlOrdinalPredicate predicate(2);
	const xmlChar* attrs[] = {
		BAD_CAST "aname", BAD_CAST "avalue",
		BAD_CAST "bname", BAD_CAST "bvalue",
		nullptr
	};
	LibXmlAttributeCollection libXmlAttrs{attrs};
	
	// Act
	predicate.IsMatch(libXmlAttrs);
	predicate.IsMatch(libXmlAttrs);
	
	// Assert
	EXPECT_FALSE(predicate.IsMatch(libXmlAttrs));
}

/******************************************************************************************/
/* Reset() tests                                                                          */
/******************************************************************************************/
TEST(XmlOrdinalPredicate, ResetCausesIsMatchToReturnTrueAgain) {
	// Arrange
	XmlOrdinalPredicate predicate(1);
	const xmlChar* attrs[] = {
		BAD_CAST "aname", BAD_CAST "avalue",
		BAD_CAST "bname", BAD_CAST "bvalue",
		nullptr
	};
	LibXmlAttributeCollection libXmlAttrs{attrs};
	
	// Act
	predicate.IsMatch(libXmlAttrs);
	predicate.Reset();
	
	// Assert
	EXPECT_TRUE(predicate.IsMatch(libXmlAttrs));
}
