#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <algorithm>
#include <memory>
#include <sstream>

#include "libxmlattributecollection.h"
#include "libxmlattributecollection-iterator.h"
#include "xmlpredicate.h"
#include "exception/xpathexception.h"

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

/******************************************************************************************/
/* bool IsMatch(const XmlElement& elem) tests*/
/******************************************************************************************/

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

/******************************************************************************************/
/* template<class T> bool IsMatch(const char* tagName, const T& attributes) tests */
/******************************************************************************************/

TEST(XmlPredicate, IsMatchReturnsTrueWhenTagNamesMatch) {
	// Arrange
	LibXmlAttributeCollection attrs{ nullptr };
	XmlPredicate testPredicate("aa");

	// Act
	bool result = testPredicate.IsMatch("aa", attrs);

	// Assert
	EXPECT_TRUE(result);
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenTagNamesNoMatch) {
	// Arrange
	LibXmlAttributeCollection attrs{ nullptr };
	XmlPredicate testPredicate("aa");

	// Act
	bool result = testPredicate.IsMatch("bb", attrs);

	// Assert
	EXPECT_FALSE(result);
}

TEST(XmlPredicate, IsMatchReturnsTrueWhenTagNamesAndAttributesMatch) {
	// Arrange
	static const xmlChar* testAttrs[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };
	LibXmlAttributeCollection attrs{ testAttrs };
	XmlPredicate testPredicate("aa", make_unique<XmlAttribute>("attname2", "attvalue2"));

	// Act
	bool result = testPredicate.IsMatch("aa", attrs);

	// Assert
	EXPECT_TRUE(result);
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenTagNamesMatchAndAttributeNameNoMatch) {
	// Arrange
	static const xmlChar* testAttrs[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };
	LibXmlAttributeCollection attrs{ testAttrs };
	XmlPredicate testPredicate("aa", make_unique<XmlAttribute>("attname3", "attvalue2"));

	// Act
	bool result = testPredicate.IsMatch("aa", attrs);

	// Assert
	EXPECT_FALSE(result);
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenTagNamesMatchAndAttributeValueNameNoMatch) {
	// Arrange
	static const xmlChar* testAttrs[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };
	LibXmlAttributeCollection attrs{ testAttrs };
	XmlPredicate testPredicate("aa", make_unique<XmlAttribute>("attname2", "attvalue3"));

	// Act
	bool result = testPredicate.IsMatch("aa", attrs);

	// Assert
	EXPECT_FALSE(result);
}


/******************************************************************************************/
/* static XmlPredicate FromText(std::string text) */
/******************************************************************************************/

TEST(XmlPredicate, FromTextReturnsPredicateForSimpleTagName) {
    // Arrange
	
	// Act
	XmlPredicate pred = XmlPredicate::FromText("simpletagname");
    
	EXPECT_EQ("simpletagname", pred.GetTagName());
	EXPECT_EQ(nullptr, pred.GetAttributePredicate());
}

TEST(XmlPredicate, FromTextThrowsWithEmptyString) {
    // Arrange
	
	// Act
	EXPECT_THROW(XmlPredicate::FromText(""), XPathException);
}

TEST(XmlPredicate, FromTextReturnsPredicateForSimpleTagNameWithAttribute) {
    // Arrange
	
	// Act
	XmlPredicate pred = XmlPredicate::FromText("simpletagname[attr=\"val\"]");
    
	EXPECT_EQ("simpletagname", pred.GetTagName());
	ASSERT_NE(nullptr, pred.GetAttributePredicate());
	EXPECT_EQ("attr", pred.GetAttributePredicate()->GetName());
	EXPECT_EQ("\"val\"", pred.GetAttributePredicate()->GetValue());
}
