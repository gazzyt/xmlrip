#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <memory>

#include "libxmlattributecollection.h"
#include "xmlexpression.h"
#include "exception/xpathexception.h"

using namespace std;

/******************************************************************************************/
/* GetCurrentMatchDepth tests */
/******************************************************************************************/

TEST(XmlExpression, CurrentMatchDepthIsNoMatchForNewExpression) {
	// Arrange
    XmlExpression expr;
	
	// Act
    
	// Assert
	EXPECT_EQ(XmlExpression::NO_MATCH, expr.GetCurrentMatchDepth());
}

TEST(XmlExpression, CurrentMatchDepthIsNoMatchWhenNoMatch) {
	// Arrange
    XmlExpression expr;
	expr.AddStepExpr(make_unique<XmlStepExpr>("aa"));
	LibXmlAttributeCollection attrs{ nullptr };
	
	// Act
	expr.ProcessStartTag("bb", attrs);
    
	// Assert
	EXPECT_EQ(XmlExpression::NO_MATCH, expr.GetCurrentMatchDepth());
}

TEST(XmlExpression, CurrentMatchDepthIsZeroOnMatch) {
	// Arrange
    XmlExpression expr;
	expr.AddStepExpr(make_unique<XmlStepExpr>("aa"));
	LibXmlAttributeCollection attrs{ nullptr };
    
	// Act
	expr.ProcessStartTag("aa", attrs);
	
	// Assert
	EXPECT_EQ(0, expr.GetCurrentMatchDepth());
}

TEST(XmlExpression, CurrentMatchIsOneForChildTagsOfFullMatch) {
	// Arrange
    XmlExpression expr;
	expr.AddStepExpr(make_unique<XmlStepExpr>("aa"));
	LibXmlAttributeCollection attrs{ nullptr };
	
	// Act
	expr.ProcessStartTag("aa", attrs);
	expr.ProcessStartTag("bb", attrs);
    
	// Assert
	EXPECT_EQ(1, expr.GetCurrentMatchDepth());
}

/******************************************************************************************/
/* GetCurrentMatchDepth tests */
/******************************************************************************************/

TEST(XmlExpression, CurrentDocumentDepthIsZeroForNewExpression) {
	// Arrange
    XmlExpression expr;
	
	// Act
    
	// Assert
	EXPECT_EQ(0, expr.GetCurrentDocumentDepth());
}

TEST(XmlExpression, CurrentDocumentDepthIncrementsAfterStartTag) {
	// Arrange
    XmlExpression expr;
	LibXmlAttributeCollection attrs{ nullptr };
	
	// Act
	expr.ProcessStartTag("aa", attrs);
    
	// Assert
	EXPECT_EQ(1, expr.GetCurrentDocumentDepth());
}

TEST(XmlExpression, CurrentDocumentDepthDecrementsAfterEndTag) {
	// Arrange
    XmlExpression expr;
	LibXmlAttributeCollection attrs{ nullptr };
	
	// Act
	expr.ProcessStartTag("aa", attrs);
	expr.ProcessStartTag("bb", attrs);
	expr.ProcessEndTag("bb");
    
	// Assert
	EXPECT_EQ(1, expr.GetCurrentDocumentDepth());
}


/******************************************************************************************/
/* ProcessStartTag tests */
/******************************************************************************************/

TEST(XmlExpression, ProcessStartTagReturnsZeroWithSingleTagExpressionWhenTagMatches) {
	// Arrange
    XmlExpression expr;
	expr.AddStepExpr(make_unique<XmlStepExpr>("aa"));
	LibXmlAttributeCollection attrs{ nullptr };
	
	// Act
	auto result = expr.ProcessStartTag("aa", attrs);
    
	// Assert
	EXPECT_EQ(0, result);
}


TEST(XmlExpression, ProcessStartTagReturnsNoMatchWithSingleTagExpressionWhenTagDoesNotMatch) {
	// Arrange
    XmlExpression expr;
	expr.AddStepExpr(make_unique<XmlStepExpr>("aa"));
	LibXmlAttributeCollection attrs{ nullptr };
    
	// Act
	auto result = expr.ProcessStartTag("bb", attrs);
	
	// Assert
	EXPECT_EQ(XmlExpression::NO_MATCH, result);
}

TEST(XmlExpression, ProcessStartTagReturnsOneForChildTagsOfFullMatch) {
	// Arrange
    XmlExpression expr;
	expr.AddStepExpr(make_unique<XmlStepExpr>("aa"));
	LibXmlAttributeCollection attrs{ nullptr };
	
	// Act
	expr.ProcessStartTag("aa", attrs);
	auto result = expr.ProcessStartTag("bb", attrs);
    
	// Assert
	EXPECT_EQ(1, result);
}

TEST(XmlExpression, ProcessStartTagReturnsNoMatchAfterMatchingTagClosed) {
	// Arrange
    XmlExpression expr;
	expr.AddStepExpr(make_unique<XmlStepExpr>("aa"));
	LibXmlAttributeCollection attrs{ nullptr };
	
	// Act
	expr.ProcessStartTag("aa", attrs);
	expr.ProcessEndTag("aa");
	auto result = expr.ProcessStartTag("bb", attrs);
    
	// Assert
	EXPECT_EQ(XmlExpression::NO_MATCH, result);
}

TEST(XmlExpression, ProcessStartTagProcessesTwoPrecidatesCorrectly) {
	// Arrange
    XmlExpression expr;
 	expr.AddStepExpr(make_unique<XmlStepExpr>("aa"));
	expr.AddStepExpr(make_unique<XmlStepExpr>("bb"));
	LibXmlAttributeCollection attrs{ nullptr };
	
	// Act
	// Assert
	// <aa><bb><cc></cc></bb><cc></cc><bb></bb></aa><bb></bb>
	EXPECT_EQ(XmlExpression::NO_MATCH, expr.ProcessStartTag("aa", attrs));
	EXPECT_EQ(0, expr.ProcessStartTag("bb", attrs));
	EXPECT_EQ(1, expr.ProcessStartTag("cc", attrs));
	EXPECT_EQ(1, expr.ProcessEndTag("cc"));
	EXPECT_EQ(0, expr.ProcessEndTag("bb"));
	EXPECT_EQ(XmlExpression::NO_MATCH, expr.ProcessStartTag("cc", attrs));
	EXPECT_EQ(XmlExpression::NO_MATCH, expr.ProcessEndTag("cc"));
	EXPECT_EQ(0, expr.ProcessStartTag("bb", attrs));
	EXPECT_EQ(0, expr.ProcessEndTag("bb"));
   	EXPECT_EQ(XmlExpression::NO_MATCH, expr.ProcessEndTag("aa"));
	EXPECT_EQ(XmlExpression::NO_MATCH, expr.ProcessStartTag("bb", attrs));
	EXPECT_EQ(XmlExpression::NO_MATCH, expr.ProcessEndTag("bb"));

}


/******************************************************************************************/
/* ProcessEndTag tests */
/******************************************************************************************/

TEST(XmlExpression, ProcessStartTagReturnsZeroForClosingTagOfFullMatch) {
	// Arrange
    XmlExpression expr;
	expr.AddStepExpr(make_unique<XmlStepExpr>("aa"));
	LibXmlAttributeCollection attrs{ nullptr };
	
	// Act
	expr.ProcessStartTag("aa", attrs);
	auto result = expr.ProcessEndTag("aa");
    
	// Assert
	EXPECT_EQ(0, result);
}


/******************************************************************************************/
/* FromText tests */
/******************************************************************************************/

TEST(XmlExpression, FromTextThrowsXPathExceptionIfXPathNotBeginWithSlash) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		auto expr = XmlExpression::FromText("aa");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("XPath must begin with / or // at position 0", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XmlExpression, FromTextCreatesSingleItemExpressionCorrectly) {
	// Arrange
	
	// Act
	auto expr = XmlExpression::FromText("/aa");
	
	// Assert
	ASSERT_TRUE((bool)expr);

	auto& predicates = expr->GetStepExprs();
	EXPECT_EQ(1U, predicates.size());
	EXPECT_EQ("aa", predicates[0]->GetTagName());
}

TEST(XmlExpression, FromTextCreatesTwoItemExpressionCorrectly) {
	// Arrange
	
	// Act
	auto expr = XmlExpression::FromText("/aa/bb");
	
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
	return XmlExpression::ReadStepExpr(tokeniser, token);
}

TEST(XmlExpression, ReadStepExprThrowsXPathExceptionIfXPathNotBeginWithSlash) {
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

TEST(XmlExpression, ReadStepExprThrowsXPathExceptionIfXPathNotContainTagName) {
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

TEST(XmlExpression, ReadStepExprThrowsXPathExceptionIfXPathContainDot) {
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

TEST(XmlExpression, ReadStepExprThrowsXPathExceptionIfXPathConditionMissingAt) {
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

TEST(XmlExpression, ReadStepExprThrowsXPathExceptionIfXPathConditionMissingAttributeName) {
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

TEST(XmlExpression, ReadStepExprThrowsXPathExceptionIfXPathConditionMissingEquals) {
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

TEST(XmlExpression, ReadStepExprThrowsXPathExceptionIfXPathConditionMissingValue) {
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

TEST(XmlExpression, ReadStepExprThrowsXPathExceptionIfXPathConditionClosingBracket) {
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
	
TEST(XmlExpression, ReadStepExprReturnsStepExprForSimpleTagName) {
    // Arrange
	
	// Act
	auto pred = GetTestStepExpr("/simpletagname");
    
	EXPECT_EQ("simpletagname", pred->GetTagName());
	EXPECT_EQ(0U, pred->GetPredicates().size());
	EXPECT_EQ(1, pred->GetDocumentDepthPredicate());
}

TEST(XmlExpression, ReadStepExprReturnsStepExprForSimpleTagNameWithDepth) {
    // Arrange
	
	// Act
	auto pred = GetTestStepExpr("//simpletagname");
    
	EXPECT_EQ("simpletagname", pred->GetTagName());
	EXPECT_EQ(0U, pred->GetPredicates().size());
	EXPECT_EQ(-1, pred->GetDocumentDepthPredicate());
}

TEST(XmlExpression, ReadStepExprReturnsStepExprForSimpleTagNameWithAttributeDoubleQuote) {
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

TEST(XmlExpression, ReadStepExprReturnsStepExprForSimpleTagNameWithAttributeSingleQuote) {
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

TEST(XmlExpression, ReadStepExprReturnsStepExprForSimpleTagNameWithAttributeStartsWith) {
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

TEST(XmlExpression, ReadStepExprThrowsXPathExceptionIfXPathFunctionNameUnrecognised) {
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

TEST(XmlExpression, ReadStepExprReturnsStepExprForSimpleTagNameWithTwoAttributeFilters) {
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
