#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <sstream>

#include "xmlstreammodifiers.h"
#include "customprinters.h"

#include "xmlattributepredicate.h"

using namespace std;


TEST(XmlAttributePredicate, CreatesCorrectPredicate) {
	// Arrange
	
	// Act
	XmlAttributePredicate predicate(XmlAttributePredicate::MODE_EQUAL, "aname", "avalue");
	
	// Assert
	EXPECT_EQ(XmlAttributePredicate::MODE_EQUAL, predicate.GetMode());
	EXPECT_EQ("aname", predicate.GetName());
	EXPECT_EQ("avalue", predicate.GetValue());
}


TEST(XmlAttributePredicate, AttributeNoMatchWhenAttributeNameDiffers) {
	// Arrange
	XmlAttributePredicate predicate(XmlAttributePredicate::MODE_EQUAL, "bname", "avalue");
	
	// Act
	
	// Assert
	EXPECT_FALSE(predicate.IsMatch("aname", "avalue"));
}

TEST(XmlAttributePredicate, AttributeNotMatchWhenAttributeValueDiffers) {
	// Arrange
	XmlAttributePredicate predicate(XmlAttributePredicate::MODE_EQUAL, "aname", "bvalue");
	
	// Act
	
	// Assert
	EXPECT_FALSE(predicate.IsMatch("aname", "avalue"));
}

TEST(XmlAttributePredicate, AttributeMatchesWhenNameAndValueSame) {
	// Arrange
	XmlAttributePredicate predicate(XmlAttributePredicate::MODE_EQUAL, "aname", "avalue");
	
	// Act
	
	// Assert
	EXPECT_TRUE(predicate.IsMatch("aname", "avalue"));
}


