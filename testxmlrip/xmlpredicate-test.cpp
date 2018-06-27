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

/******************************************************************************************/
/* copy constructor tests                                                                 */
/******************************************************************************************/

TEST(XmlPredicate, CopyConstructorWorksWithAttributePredicate) {
	// Arrange
	XmlPredicate xp1{"TestTagName"};
	xp1.AddPredicate(XmlAttributePredicate{XmlAttributePredicate::MODE_EQUAL, "attrName", "attrValue"});
	
	// Act
	XmlPredicate xp2(xp1);
	
	// Assert
	EXPECT_EQ(xp1.GetTagName(), xp2.GetTagName());
	EXPECT_NE(&xp1.GetTagName(), &xp2.GetTagName());
	ASSERT_EQ(1U, xp2.GetAttributePredicates().size());
	EXPECT_EQ(xp1.GetAttributePredicates()[0].GetName(), xp2.GetAttributePredicates()[0].GetName());
	EXPECT_EQ(xp1.GetAttributePredicates()[0].GetValue(), xp2.GetAttributePredicates()[0].GetValue());
	
}

TEST(XmlPredicate, CopyConstructorWorksWithoutAttributePredicate) {
	// Arrange
	XmlPredicate xp1{"TestTagName"};
	
	// Act
	XmlPredicate xp2(xp1);
	
	// Assert
	EXPECT_EQ(xp1.GetTagName(), xp2.GetTagName());
	EXPECT_NE(&xp1.GetTagName(), &xp2.GetTagName());
	ASSERT_EQ(0U, xp2.GetAttributePredicates().size());
	
}

TEST(XmlPredicate, CopyConstructorCopiesDocumentDepthPredicate) {
	// Arrange
	XmlPredicate xp1{"TestTagName", 14};
	
	// Act
	XmlPredicate xp2(xp1);
	
	// Assert
	EXPECT_EQ(xp1.GetDocumentDepthPredicate(), xp2.GetDocumentDepthPredicate());
	
}


/******************************************************************************************/
/* template<class T> bool IsMatch(const char* tagName, const T& attributes) tests */
/******************************************************************************************/

TEST(XmlPredicate, IsMatchReturnsTrueWhenTagNamesMatch) {
	// Arrange
	LibXmlAttributeCollection attrs{ nullptr };
	XmlPredicate testPredicate("aa");

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 0);

	// Assert
	EXPECT_TRUE(result);
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenTagNamesNoMatch) {
	// Arrange
	LibXmlAttributeCollection attrs{ nullptr };
	XmlPredicate testPredicate("aa");

	// Act
	bool result = testPredicate.IsMatch("bb", attrs, 0);

	// Assert
	EXPECT_FALSE(result);
}

TEST(XmlPredicate, IsMatchReturnsTrueWhenTagNamesAndAttributesMatch) {
	// Arrange
	static const xmlChar* testAttrs[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };
	LibXmlAttributeCollection attrs{ testAttrs };
	XmlPredicate testPredicate("aa");
	testPredicate.AddPredicate(XmlAttributePredicate{XmlAttributePredicate::MODE_EQUAL, "attname2", "attvalue2"});

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 0);

	// Assert
	EXPECT_TRUE(result);
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenTagNamesMatchAndAttributeNameNoMatch) {
	// Arrange
	static const xmlChar* testAttrs[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };
	LibXmlAttributeCollection attrs{ testAttrs };
	XmlPredicate testPredicate("aa");
	testPredicate.AddPredicate(XmlAttributePredicate{XmlAttributePredicate::MODE_EQUAL, "attname3", "attvalue2"});

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 0);

	// Assert
	EXPECT_FALSE(result);
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenTagNamesMatchAndAttributeValueNameNoMatch) {
	// Arrange
	static const xmlChar* testAttrs[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };
	LibXmlAttributeCollection attrs{ testAttrs };
	XmlPredicate testPredicate("aa");
	testPredicate.AddPredicate(XmlAttributePredicate{XmlAttributePredicate::MODE_EQUAL, "attname2", "attvalue3"});

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 0);

	// Assert
	EXPECT_FALSE(result);
}

TEST(XmlPredicate, IsMatchReturnsTrueWhenTagNamesAndDepthMatch) {
	// Arrange
	LibXmlAttributeCollection attrs{ nullptr };
	XmlPredicate testPredicate("aa", 0);

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 0);

	// Assert
	EXPECT_TRUE(result);
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenTagNamesMatchAndDepthNoMatch) {
	// Arrange
	LibXmlAttributeCollection attrs{ nullptr };
	XmlPredicate testPredicate("aa", 0);

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 1);

	// Assert
	EXPECT_FALSE(result);
}

TEST(XmlPredicate, IsMatchReturnsTrueWhenTagNamesAndBothAttributesMatchTwoAttributePredicates) {
	// Arrange
	static const xmlChar* testAttrs[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };
	LibXmlAttributeCollection attrs{ testAttrs };
	XmlPredicate testPredicate("aa");
	testPredicate.AddPredicate(XmlAttributePredicate{XmlAttributePredicate::MODE_EQUAL, "attname1", "attvalue1"});
	testPredicate.AddPredicate(XmlAttributePredicate{XmlAttributePredicate::MODE_EQUAL, "attname2", "attvalue2"});

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 0);

	// Assert
	EXPECT_TRUE(result);
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenTagNamesAndOneAttributeMatchesTwoAttributePredicates) {
	// Arrange
	static const xmlChar* testAttrs[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };
	LibXmlAttributeCollection attrs{ testAttrs };
	XmlPredicate testPredicate("aa");
	testPredicate.AddPredicate(XmlAttributePredicate{XmlAttributePredicate::MODE_EQUAL, "attname1", "attvalue1"});
	testPredicate.AddPredicate(XmlAttributePredicate{XmlAttributePredicate::MODE_EQUAL, "attname3", "attvalue2"});

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 0);

	// Assert
	EXPECT_FALSE(result);
}
