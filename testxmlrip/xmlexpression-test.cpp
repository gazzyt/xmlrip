#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

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
	expr.AddPredicate(XmlPredicate{"aa"});
	LibXmlAttributeCollection attrs{ nullptr };
	
	// Act
	expr.ProcessStartTag("bb", attrs);
    
	// Assert
	EXPECT_EQ(XmlExpression::NO_MATCH, expr.GetCurrentMatchDepth());
}

TEST(XmlExpression, CurrentMatchDepthIsZeroOnMatch) {
	// Arrange
    XmlExpression expr;
	expr.AddPredicate(XmlPredicate{"aa"});
	LibXmlAttributeCollection attrs{ nullptr };
    
	// Act
	expr.ProcessStartTag("aa", attrs);
	
	// Assert
	EXPECT_EQ(0, expr.GetCurrentMatchDepth());
}

TEST(XmlExpression, CurrentMatchIsOneForChildTagsOfFullMatch) {
	// Arrange
    XmlExpression expr;
	expr.AddPredicate(XmlPredicate{"aa"});
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
	expr.AddPredicate(XmlPredicate{"aa"});
	LibXmlAttributeCollection attrs{ nullptr };
	
	// Act
	auto result = expr.ProcessStartTag("aa", attrs);
    
	// Assert
	EXPECT_EQ(0, result);
}


TEST(XmlExpression, ProcessStartTagReturnsNoMatchWithSingleTagExpressionWhenTagDoesNotMatch) {
	// Arrange
    XmlExpression expr;
	expr.AddPredicate(XmlPredicate{"aa"});
	LibXmlAttributeCollection attrs{ nullptr };
    
	// Act
	auto result = expr.ProcessStartTag("bb", attrs);
	
	// Assert
	EXPECT_EQ(XmlExpression::NO_MATCH, result);
}

TEST(XmlExpression, ProcessStartTagReturnsOneForChildTagsOfFullMatch) {
	// Arrange
    XmlExpression expr;
	expr.AddPredicate(XmlPredicate{"aa"});
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
	expr.AddPredicate(XmlPredicate{"aa"});
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
 	expr.AddPredicate(XmlPredicate{"aa"});
	expr.AddPredicate(XmlPredicate{"bb"});
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
	expr.AddPredicate(XmlPredicate{"aa"});
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

	auto predicates = expr->GetPredicates();
	EXPECT_EQ(1U, predicates.size());
	EXPECT_EQ("aa", predicates[0].GetTagName());
}

TEST(XmlExpression, FromTextCreatesTwoItemExpressionCorrectly) {
	// Arrange
	
	// Act
	auto expr = XmlExpression::FromText("/aa/bb");
	
	// Assert
	ASSERT_TRUE((bool)expr);

	auto predicates = expr->GetPredicates();
	EXPECT_EQ(2U, predicates.size());
	EXPECT_EQ("aa", predicates[0].GetTagName());
	EXPECT_EQ("bb", predicates[1].GetTagName());
}

/******************************************************************************************/
/* ReadPredicate tests */
/******************************************************************************************/
XmlPredicate GetTestPredicate(const string xpath)
{
	XPathTokeniser tokeniser{ xpath };
	XPathToken token = tokeniser.GetNextToken();
	return XmlExpression::ReadPredicate(tokeniser, token);
}

TEST(XmlExpression, ReadPredicateThrowsXPathExceptionIfXPathNotBeginWithSlash) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		XmlPredicate pred = GetTestPredicate("simpletagname");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Expected / or // at position 0", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XmlExpression, ReadPredicateThrowsXPathExceptionIfXPathNotContainTagName) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		XmlPredicate pred = GetTestPredicate("//@");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Expected element name at position 2", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XmlExpression, ReadPredicateThrowsXPathExceptionIfXPathContainDot) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		XmlPredicate pred = GetTestPredicate("//tag.");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Unexpected character in XPath: . at position 5", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XmlExpression, ReadPredicateThrowsXPathExceptionIfXPathConditionMissingAt) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		XmlPredicate pred = GetTestPredicate("//tag[a='t']");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XmlExpression, ReadPredicateThrowsXPathExceptionIfXPathConditionMissingAttributeName) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		XmlPredicate pred = GetTestPredicate("//tag[@='t']");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Expected attribute name at position 7", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XmlExpression, ReadPredicateThrowsXPathExceptionIfXPathConditionMissingEquals) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		XmlPredicate pred = GetTestPredicate("//tag[@a't']");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Expected = token at position 8", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XmlExpression, ReadPredicateThrowsXPathExceptionIfXPathConditionMissingValue) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		XmlPredicate pred = GetTestPredicate("//tag[@a=]");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Expected attribute value at position 9", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XmlExpression, ReadPredicateThrowsXPathExceptionIfXPathConditionClosingBracket) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		XmlPredicate pred = GetTestPredicate("//tag[@a='b'");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Expected ] token at position 12", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}
	
TEST(XmlExpression, ReadPredicateReturnsPredicateForSimpleTagName) {
    // Arrange
	
	// Act
	XmlPredicate pred = GetTestPredicate("/simpletagname");
    
	EXPECT_EQ("simpletagname", pred.GetTagName());
	EXPECT_EQ(nullptr, pred.GetAttributePredicate());
	EXPECT_EQ(1, pred.GetDocumentDepthPredicate());
}

TEST(XmlExpression, ReadPredicateReturnsPredicateForSimpleTagNameWithDepth) {
    // Arrange
	
	// Act
	XmlPredicate pred = GetTestPredicate("//simpletagname");
    
	EXPECT_EQ("simpletagname", pred.GetTagName());
	EXPECT_EQ(nullptr, pred.GetAttributePredicate());
	EXPECT_EQ(-1, pred.GetDocumentDepthPredicate());
}

TEST(XmlExpression, ReadPredicateReturnsPredicateForSimpleTagNameWithAttributeDoubleQuote) {
    // Arrange
	
	// Act
	XmlPredicate pred = GetTestPredicate("/simpletagname[@attr=\"val\"]");
    
	EXPECT_EQ("simpletagname", pred.GetTagName());
	ASSERT_NE(nullptr, pred.GetAttributePredicate());
	EXPECT_EQ("attr", pred.GetAttributePredicate()->GetName());
	EXPECT_EQ("val", pred.GetAttributePredicate()->GetValue());
}

TEST(XmlExpression, ReadPredicateReturnsPredicateForSimpleTagNameWithAttributeSingleQuote) {
    // Arrange
	
	// Act
	XmlPredicate pred = GetTestPredicate("/simpletagname[@attr='val']");
    
	EXPECT_EQ("simpletagname", pred.GetTagName());
	ASSERT_NE(nullptr, pred.GetAttributePredicate());
	EXPECT_EQ(XmlAttributePredicate::MODE_EQUAL, pred.GetAttributePredicate()->GetMode());
	EXPECT_EQ("attr", pred.GetAttributePredicate()->GetName());
	EXPECT_EQ("val", pred.GetAttributePredicate()->GetValue());
}

TEST(XmlExpression, ReadPredicateReturnsPredicateForSimpleTagNameWithAttributeStartsWith) {
    // Arrange
	
	// Act
	XmlPredicate pred = GetTestPredicate("/simpletagname[starts-with(@attr,'val')]");
    
	EXPECT_EQ("simpletagname", pred.GetTagName());
	ASSERT_NE(nullptr, pred.GetAttributePredicate());
	EXPECT_EQ(XmlAttributePredicate::MODE_STARTSWITH, pred.GetAttributePredicate()->GetMode());
	EXPECT_EQ("attr", pred.GetAttributePredicate()->GetName());
	EXPECT_EQ("val", pred.GetAttributePredicate()->GetValue());
}

TEST(XmlExpression, ReadPredicateThrowsXPathExceptionIfXPathFunctionNameUnrecognised) {
	// Arrange
	bool exceptionThrown = false;

	// Act
	try
	{
		XmlPredicate pred = GetTestPredicate("/simpletagname[staxxxxrts-with(@attr,'val')]");
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_STREQ("Unknown function name: staxxxxrts-with at position 15", e.what());
	}

	EXPECT_TRUE(exceptionThrown);
}
