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
		EXPECT_EQ("XPath must begin with / or //", e.GetMessage());
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
TEST(XmlExpression, ReadPredicateReturnsPredicateForSimpleTagName) {
    // Arrange
	string xpath{ "/simpletagname" };
	XPathTokeniser tokeniser{ xpath };
	XPathToken token = tokeniser.GetNextToken();
	
	// Act
	XmlPredicate pred = XmlExpression::ReadPredicate(tokeniser, token);
    
	EXPECT_EQ("simpletagname", pred.GetTagName());
	EXPECT_EQ(nullptr, pred.GetAttributePredicate());
}

TEST(XmlExpression, ReadPredicateReturnsPredicateForSimpleTagNameWithAttributeDoubleQuote) {
    // Arrange
	string xpath{ "/simpletagname[@attr=\"val\"]" };
	XPathTokeniser tokeniser{ xpath };
	XPathToken token = tokeniser.GetNextToken();
	
	// Act
	XmlPredicate pred = XmlExpression::ReadPredicate(tokeniser, token);
    
	EXPECT_EQ("simpletagname", pred.GetTagName());
	ASSERT_NE(nullptr, pred.GetAttributePredicate());
	EXPECT_EQ("attr", pred.GetAttributePredicate()->GetName());
	EXPECT_EQ("val", pred.GetAttributePredicate()->GetValue());
}

TEST(XmlExpression, ReadPredicateReturnsPredicateForSimpleTagNameWithAttributeSingleQuote) {
    // Arrange
	string xpath{ "/simpletagname[@attr='val']" };
	XPathTokeniser tokeniser{ xpath };
	XPathToken token = tokeniser.GetNextToken();
	
	// Act
	XmlPredicate pred = XmlExpression::ReadPredicate(tokeniser, token);
    
	EXPECT_EQ("simpletagname", pred.GetTagName());
	ASSERT_NE(nullptr, pred.GetAttributePredicate());
	EXPECT_EQ("attr", pred.GetAttributePredicate()->GetName());
	EXPECT_EQ("val", pred.GetAttributePredicate()->GetValue());
}
