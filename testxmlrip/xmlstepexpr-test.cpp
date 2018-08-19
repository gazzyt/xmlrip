#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <algorithm>
#include <memory>
#include <sstream>

#include "libxmlattributecollection.h"
#include "libxmlattributecollection-iterator.h"
#include "xmlstepexpr.h"
#include "exception/xpathexception.h"

using namespace std;


/******************************************************************************************/
/* template<class T> bool IsMatch(const char* tagName, const T& attributes) tests */
/******************************************************************************************/

TEST(XmlStepExpr, IsMatchReturnsTrueWhenTagNamesMatch) {
	// Arrange
	LibXmlAttributeCollection attrs{ nullptr };
	XmlStepExpr testPredicate("aa");

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 0);

	// Assert
	EXPECT_TRUE(result);
}

TEST(XmlStepExpr, IsMatchReturnsFalseWhenTagNamesNoMatch) {
	// Arrange
	LibXmlAttributeCollection attrs{ nullptr };
	XmlStepExpr testPredicate("aa");

	// Act
	bool result = testPredicate.IsMatch("bb", attrs, 0);

	// Assert
	EXPECT_FALSE(result);
}

TEST(XmlStepExpr, IsMatchReturnsTrueWhenTagNamesAndAttributesMatch) {
	// Arrange
	static const xmlChar* testAttrs[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };
	LibXmlAttributeCollection attrs{ testAttrs };
	XmlStepExpr testPredicate("aa");
	testPredicate.AddPredicate(make_unique<XmlAttributePredicate>(XmlAttributePredicate::MODE_EQUAL, "attname2", "attvalue2"));

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 0);

	// Assert
	EXPECT_TRUE(result);
}

TEST(XmlStepExpr, IsMatchReturnsFalseWhenTagNamesMatchAndAttributeNameNoMatch) {
	// Arrange
	static const xmlChar* testAttrs[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };
	LibXmlAttributeCollection attrs{ testAttrs };
	XmlStepExpr testPredicate("aa");
	testPredicate.AddPredicate(make_unique<XmlAttributePredicate>(XmlAttributePredicate::MODE_EQUAL, "attname3", "attvalue2"));

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 0);

	// Assert
	EXPECT_FALSE(result);
}

TEST(XmlStepExpr, IsMatchReturnsFalseWhenTagNamesMatchAndAttributeValueNameNoMatch) {
	// Arrange
	static const xmlChar* testAttrs[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };
	LibXmlAttributeCollection attrs{ testAttrs };
	XmlStepExpr testPredicate("aa");
	testPredicate.AddPredicate(make_unique<XmlAttributePredicate>(XmlAttributePredicate::MODE_EQUAL, "attname2", "attvalue3"));

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 0);

	// Assert
	EXPECT_FALSE(result);
}

TEST(XmlStepExpr, IsMatchReturnsTrueWhenTagNamesAndDepthMatch) {
	// Arrange
	LibXmlAttributeCollection attrs{ nullptr };
	XmlStepExpr testPredicate("aa", 0);

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 0);

	// Assert
	EXPECT_TRUE(result);
}

TEST(XmlStepExpr, IsMatchReturnsFalseWhenTagNamesMatchAndDepthNoMatch) {
	// Arrange
	LibXmlAttributeCollection attrs{ nullptr };
	XmlStepExpr testPredicate("aa", 0);

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 1);

	// Assert
	EXPECT_FALSE(result);
}

TEST(XmlStepExpr, IsMatchReturnsTrueWhenTagNamesAndBothAttributesMatchTwoAttributePredicates) {
	// Arrange
	static const xmlChar* testAttrs[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };
	LibXmlAttributeCollection attrs{ testAttrs };
	XmlStepExpr testPredicate("aa");
	testPredicate.AddPredicate(make_unique<XmlAttributePredicate>(XmlAttributePredicate::MODE_EQUAL, "attname1", "attvalue1"));
	testPredicate.AddPredicate(make_unique<XmlAttributePredicate>(XmlAttributePredicate::MODE_EQUAL, "attname2", "attvalue2"));

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 0);

	// Assert
	EXPECT_TRUE(result);
}

TEST(XmlStepExpr, IsMatchReturnsFalseWhenTagNamesAndOneAttributeMatchesTwoAttributePredicates) {
	// Arrange
	static const xmlChar* testAttrs[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };
	LibXmlAttributeCollection attrs{ testAttrs };
	XmlStepExpr testPredicate("aa");
	testPredicate.AddPredicate(make_unique<XmlAttributePredicate>(XmlAttributePredicate::MODE_EQUAL, "attname1", "attvalue1"));
	testPredicate.AddPredicate(make_unique<XmlAttributePredicate>(XmlAttributePredicate::MODE_EQUAL, "attname3", "attvalue2"));

	// Act
	bool result = testPredicate.IsMatch("aa", attrs, 0);

	// Assert
	EXPECT_FALSE(result);
}

/******************************************************************************************/
/* Reset() tests                                                                          */
/******************************************************************************************/

class ResetPredicateTester : public XmlPredicate
{
public:
	ResetPredicateTester() : m_resetCalls{0} {}
	virtual void Reset() { ++m_resetCalls; }
	virtual bool IsMatch(const LibXmlAttributeCollection& /*attributes*/) const noexcept { return false; };
	int m_resetCalls;
};

TEST(XmlStepExpr, ResetResetsAllPredicates) {
	// Arrange
	ResetPredicateTester* pPredicate1 = new ResetPredicateTester();
	XmlStepExpr testStepExpr("aa");
	testStepExpr.AddPredicate(unique_ptr<XmlPredicate>{pPredicate1});

	// Act
	testStepExpr.Reset();

	// Assert
	EXPECT_EQ(1, pPredicate1->m_resetCalls);
}
