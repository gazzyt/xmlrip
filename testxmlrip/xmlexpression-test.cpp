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

