#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <algorithm>
#include <memory>
#include <sstream>

#include "xmlpredicate.h"

using namespace std;

TEST(XmlPredicate, CopyConstructorWorksWithAttributePredicate) {
	// Arrange
	XmlPredicate xp1{"TestTagName", make_unique<XmlAttribute>("attrName", "attrValue")};
	
	// Act
	XmlPredicate xp2(xp1);
	
	// Assert
	EXPECT_EQ(xp1.GetTagName(), xp2.GetTagName());
	EXPECT_NE(&xp1.GetTagName(), &xp2.GetTagName());
	ASSERT_NE(nullptr, xp2.GetAttributePredicate());
	EXPECT_NE(xp1.GetAttributePredicate(), xp2.GetAttributePredicate());
	EXPECT_EQ(xp1.GetAttributePredicate()->GetName(), xp2.GetAttributePredicate()->GetName());
	EXPECT_EQ(xp1.GetAttributePredicate()->GetValue(), xp2.GetAttributePredicate()->GetValue());
	
}

TEST(XmlPredicate, CopyConstructorWorksWithoutAttributePredicate) {
	// Arrange
	XmlPredicate xp1{"TestTagName"};
	
	// Act
	XmlPredicate xp2(xp1);
	
	// Assert
	EXPECT_EQ(xp1.GetTagName(), xp2.GetTagName());
	EXPECT_NE(&xp1.GetTagName(), &xp2.GetTagName());
	ASSERT_EQ(nullptr, xp2.GetAttributePredicate());
	
}

TEST(XmlPredicate, IsMatchReturnsTrueWhenOpeningTagNamesMatch) {
    XmlElement testElement(XmlElement::Type::tag, "aa", true, false);
    XmlPredicate testPredicate("aa");
    
	EXPECT_TRUE(testPredicate.IsMatch(testElement));
}

TEST(XmlPredicate, IsMatchReturnsTrueWhenOpeningClosingTagNamesMatch) {
    XmlElement testElement(XmlElement::Type::tag, "aa", true, true);
    XmlPredicate testPredicate("aa");
    
	EXPECT_TRUE(testPredicate.IsMatch(testElement));
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenClosingTagNamesMatch) {
    XmlElement testElement(XmlElement::Type::tag, "aa", false, true);
    XmlPredicate testPredicate("aa");
    
	EXPECT_FALSE(testPredicate.IsMatch(testElement));
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenOpeningTagNamesDoNotMatch) {
    XmlElement testElement(XmlElement::Type::tag, "bb", true, false);
    XmlPredicate testPredicate("aa");
    
	EXPECT_FALSE(testPredicate.IsMatch(testElement));
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenOpeningClosingTagNamesDoNotMatch) {
    XmlElement testElement(XmlElement::Type::tag, "cc", true, true);
    XmlPredicate testPredicate("aa");
    
	EXPECT_FALSE(testPredicate.IsMatch(testElement));
}

TEST(XmlPredicate, IsMatchReturnsTrueWhenOpeningTagNamesAndAttributesMatch) {
    // Arrange
	XmlElement testElement(XmlElement::Type::tag, "aa", vector<XmlAttribute>{XmlAttribute{"attr", "val"}}, true, false);
    XmlPredicate testPredicate("aa", make_unique<XmlAttribute>("attr", "val"));
    
	EXPECT_TRUE(testPredicate.IsMatch(testElement));
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenAttributeValueNotMatch) {
    // Arrange
	XmlElement testElement(XmlElement::Type::tag, "aa", vector<XmlAttribute>{XmlAttribute{"attr", "val"}}, true, false);
    XmlPredicate testPredicate("aa", make_unique<XmlAttribute>("attr", "valxx"));
    
	EXPECT_FALSE(testPredicate.IsMatch(testElement));
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenAttributeNameNotMatch) {
    // Arrange
	XmlElement testElement(XmlElement::Type::tag, "aa", vector<XmlAttribute>{XmlAttribute{"attr", "val"}}, true, false);
    XmlPredicate testPredicate("aa", make_unique<XmlAttribute>("attrxx", "val"));
    
	EXPECT_FALSE(testPredicate.IsMatch(testElement));
}
