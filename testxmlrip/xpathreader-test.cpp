#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <memory>

#include "xpathreader.h"
#include "xmlattributepredicate.h"
#include "xmlordinalpredicate.h"
#include "exception/xpathexception.h"

using namespace std;

/******************************************************************************************/
/* FromText tests */
/******************************************************************************************/

TEST(XPathReader, FromTextThrowsXPathExceptionIfXPathNotBeginWithSlash) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		auto expr = XPathReader::FromText("aa");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("XPath must begin with / or // at position 0", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XPathReader, FromTextCreatesSingleItemExpressionCorrectly) {
	// Arrange
	
	// Act
	auto expr = XPathReader::FromText("/aa");
	
	// Assert
	ASSERT_TRUE((bool)expr);

	auto& predicates = expr->GetStepExprs();
	EXPECT_EQ(1U, predicates.size());
	EXPECT_EQ("aa", predicates[0]->GetTagName());
}

TEST(XPathReader, FromTextCreatesTwoItemExpressionCorrectly) {
	// Arrange
	
	// Act
	auto expr = XPathReader::FromText("/aa/bb");
	
	// Assert
	ASSERT_TRUE((bool)expr);

	auto& predicates = expr->GetStepExprs();
	EXPECT_EQ(2U, predicates.size());
	EXPECT_EQ("aa", predicates[0]->GetTagName());
	EXPECT_EQ("bb", predicates[1]->GetTagName());
}

/******************************************************************************************/
/* ReadStepExpr tests */
/******************************************************************************************/
unique_ptr<XmlStepExpr> GetTestStepExpr(const string xpath)
{
	XPathTokeniser tokeniser{ xpath };
	XPathToken token = tokeniser.GetNextToken();
	return XPathReader::ReadStepExpr(tokeniser, token);
}

TEST(XPathReader, ReadStepExprThrowsXPathExceptionIfXPathNotBeginWithSlash) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		auto pred = GetTestStepExpr("simpletagname");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Expected / or // at position 0", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XPathReader, ReadStepExprThrowsXPathExceptionIfXPathNotContainTagName) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		auto pred = GetTestStepExpr("//@");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Expected element name at position 2", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XPathReader, ReadStepExprThrowsXPathExceptionIfXPathContainDot) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		auto pred = GetTestStepExpr("//tag.");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Unexpected character in XPath: . at position 5", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XPathReader, ReadStepExprThrowsXPathExceptionIfXPathConditionMissingAt) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		auto pred = GetTestStepExpr("//tag[a='t']");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XPathReader, ReadStepExprThrowsXPathExceptionIfXPathConditionMissingAttributeName) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		auto pred = GetTestStepExpr("//tag[@='t']");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Expected attribute name at position 7", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XPathReader, ReadStepExprThrowsXPathExceptionIfXPathConditionMissingEquals) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		auto pred = GetTestStepExpr("//tag[@a't']");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Expected = token at position 8", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XPathReader, ReadStepExprThrowsXPathExceptionIfXPathConditionMissingValue) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		auto pred = GetTestStepExpr("//tag[@a=]");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Expected attribute value at position 9", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XPathReader, ReadStepExprThrowsXPathExceptionIfXPathConditionClosingBracket) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		auto pred = GetTestStepExpr("//tag[@a='b'");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Expected ] token at position 12", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}
	
TEST(XPathReader, ReadStepExprReturnsStepExprForSimpleTagName) {
    // Arrange
	
	// Act
	auto pred = GetTestStepExpr("/simpletagname");
    
	EXPECT_EQ("simpletagname", pred->GetTagName());
	EXPECT_EQ(0U, pred->GetPredicates().size());
	EXPECT_EQ(1, pred->GetDocumentDepthPredicate());
}

TEST(XPathReader, ReadStepExprReturnsStepExprForSimpleTagNameWithDepth) {
    // Arrange
	
	// Act
	auto pred = GetTestStepExpr("//simpletagname");
    
	EXPECT_EQ("simpletagname", pred->GetTagName());
	EXPECT_EQ(0U, pred->GetPredicates().size());
	EXPECT_EQ(-1, pred->GetDocumentDepthPredicate());
}

TEST(XPathReader, ReadStepExprReturnsStepExprForSimpleTagNameWithAttributeDoubleQuote) {
    // Arrange
	
	// Act
	auto pred = GetTestStepExpr("/simpletagname[@attr=\"val\"]");
    
	EXPECT_EQ("simpletagname", pred->GetTagName());
	ASSERT_EQ(1U, pred->GetPredicates().size());
	auto p0 = dynamic_cast<XmlAttributePredicate*>(pred->GetPredicates()[0].get());
	ASSERT_NE(p0, nullptr);
	EXPECT_EQ("attr", p0->GetName());
	EXPECT_EQ("val", p0->GetValue());
}

TEST(XPathReader, ReadStepExprReturnsStepExprForSimpleTagNameWithAttributeSingleQuote) {
    // Arrange
	
	// Act
	auto pred = GetTestStepExpr("/simpletagname[@attr='val']");
    
	EXPECT_EQ("simpletagname", pred->GetTagName());
	ASSERT_EQ(1U, pred->GetPredicates().size());
	auto p0 = dynamic_cast<XmlAttributePredicate*>(pred->GetPredicates()[0].get());
	ASSERT_NE(p0, nullptr);
	EXPECT_EQ(XmlAttributePredicate::MODE_EQUAL, p0->GetMode());
	EXPECT_EQ("attr", p0->GetName());
	EXPECT_EQ("val", p0->GetValue());
}

TEST(XPathReader, ReadStepExprReturnsStepExprForSimpleTagNameWithAttributeStartsWith) {
    // Arrange
	
	// Act
	auto pred = GetTestStepExpr("/simpletagname[starts-with(@attr,'val')]");
    
	EXPECT_EQ("simpletagname", pred->GetTagName());
	ASSERT_EQ(1U, pred->GetPredicates().size());
	auto p0 = dynamic_cast<XmlAttributePredicate*>(pred->GetPredicates()[0].get());
	ASSERT_NE(p0, nullptr);
	EXPECT_EQ(XmlAttributePredicate::MODE_STARTSWITH, p0->GetMode());
	EXPECT_EQ("attr", p0->GetName());
	EXPECT_EQ("val", p0->GetValue());
}

TEST(XPathReader, ReadStepExprThrowsXPathExceptionIfXPathFunctionNameUnrecognised) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		auto pred = GetTestStepExpr("/simpletagname[staxxxxrts-with(@attr,'val')]");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Unknown function name: staxxxxrts-with at position 15", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XPathReader, ReadStepExprReturnsStepExprForSimpleTagNameWithTwoAttributeFilters) {
    // Arrange
	
	// Act
	auto pred = GetTestStepExpr("/simpletagname[@attr=\"val\"][@attr2=\"val2\"]");
    
	EXPECT_EQ("simpletagname", pred->GetTagName());
	ASSERT_EQ(2U, pred->GetPredicates().size());
	auto p0 = dynamic_cast<XmlAttributePredicate*>(pred->GetPredicates()[0].get());
	auto p1 = dynamic_cast<XmlAttributePredicate*>(pred->GetPredicates()[1].get());
	ASSERT_NE(p0, nullptr);
	ASSERT_NE(p1, nullptr);
	EXPECT_EQ("attr", p0->GetName());
	EXPECT_EQ("val", p0->GetValue());
	EXPECT_EQ("attr2", p1->GetName());
	EXPECT_EQ("val2", p1->GetValue());
}

TEST(XPathReader, ReadStepExprReturnsStepExprForSimpleTagNameWithOrdinalFilter) {
    // Arrange
	
	// Act
	auto pred = GetTestStepExpr("//simpletagname[5]");
    
	EXPECT_EQ("simpletagname", pred->GetTagName());
	ASSERT_EQ(1U, pred->GetPredicates().size());
	auto p0 = dynamic_cast<XmlOrdinalPredicate*>(pred->GetPredicates()[0].get());
	ASSERT_NE(p0, nullptr);
	EXPECT_EQ(5U, p0->GetOrdinal());
}
