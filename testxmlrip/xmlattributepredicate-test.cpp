#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <sstream>

#include "xmlstreammodifiers.h"
#include "customprinters.h"

#include "xmlattributepredicate.h"

using namespace std;

/******************************************************************************************/
/* constructor tests                                                                      */
/******************************************************************************************/

TEST(XmlAttributePredicate, ConstructorCreatesCorrectPredicate) {
	// Arrange
	
	// Act
	XmlAttributePredicate predicate(XmlAttributePredicate::MODE_EQUAL, "aname", "avalue");
	
	// Assert
	EXPECT_EQ(XmlAttributePredicate::MODE_EQUAL, predicate.GetMode());
	EXPECT_EQ("aname", predicate.GetName());
	EXPECT_EQ("avalue", predicate.GetValue());
}

/******************************************************************************************/
/* IsMatch tests                                                                          */
/******************************************************************************************/

TEST(XmlAttributePredicate, IsMatchReturnsFalseInEqualsModeWhenAttributeNameDiffers) {
	// Arrange
	XmlAttributePredicate predicate(XmlAttributePredicate::MODE_EQUAL, "bname", "avalue");
	
	// Act
	
	// Assert
	EXPECT_FALSE(predicate.IsMatch("aname", "avalue"));
}

TEST(XmlAttributePredicate, IsMatchReturnsFalseInEqualsModeWhenAttributeValueDiffers) {
	// Arrange
	XmlAttributePredicate predicate(XmlAttributePredicate::MODE_EQUAL, "aname", "bvalue");
	
	// Act
	
	// Assert
	EXPECT_FALSE(predicate.IsMatch("aname", "avalue"));
}

TEST(XmlAttributePredicate, IsMatchReturnsTrueInEqualsModeWhenNameAndValueSame) {
	// Arrange
	XmlAttributePredicate predicate(XmlAttributePredicate::MODE_EQUAL, "aname", "avalue");
	
	// Act
	
	// Assert
	EXPECT_TRUE(predicate.IsMatch("aname", "avalue"));
}

TEST(XmlAttributePredicate, IsMatchReturnsTrueInStartsWithModeWhenNameAndValueSame) {
	// Arrange
	XmlAttributePredicate predicate(XmlAttributePredicate::MODE_EQUAL, "aname", "avalue");
	
	// Act
	
	// Assert
	EXPECT_TRUE(predicate.IsMatch("aname", "avalue"));
}

TEST(XmlAttributePredicate, IsMatchReturnsTrueInStartsWithModeWhenNameSameAndValueStartsWith) {
	// Arrange
	XmlAttributePredicate predicate(XmlAttributePredicate::MODE_STARTSWITH, "aname", "av");
	
	// Act
	
	// Assert
	EXPECT_TRUE(predicate.IsMatch("aname", "avalue"));
}

TEST(XmlAttributePredicate, IsMatchReturnsFalseInStartsWithModeWhenNameSameAndValueTooShort) {
	// Arrange
	XmlAttributePredicate predicate(XmlAttributePredicate::MODE_STARTSWITH, "aname", "avalue");
	
	// Act
	
	// Assert
	EXPECT_FALSE(predicate.IsMatch("aname", "av"));
}

TEST(XmlAttributePredicate, IsMatchReturnsFalseInStartsWithModeWhenNameSameAndValueDiffers) {
	// Arrange
	XmlAttributePredicate predicate(XmlAttributePredicate::MODE_STARTSWITH, "aname", "av");
	
	// Act
	
	// Assert
	EXPECT_FALSE(predicate.IsMatch("aname", "bvalue"));
}

TEST(XmlAttributePredicate, IsMatchReturnsFalseInStartsWithModeWhenNameDiffers) {
	// Arrange
	XmlAttributePredicate predicate(XmlAttributePredicate::MODE_STARTSWITH, "aname", "avalue");
	
	// Act
	
	// Assert
	EXPECT_FALSE(predicate.IsMatch("bname", "avalue"));
}
