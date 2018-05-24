#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include "libxmlattributecollection.h"
#include "xmlexpression.h"
#include "exception/xpathexception.h"

using namespace std;

TEST(XPath, TwoLevelXPath) {
	// Arrange
	auto expr = XmlExpression::FromText("/aa/bb");
	LibXmlAttributeCollection attrs{ nullptr };
	
	// Act
	auto result1 = expr->ProcessStartTag("aa", attrs);
	auto result2 = expr->ProcessStartTag("bb", attrs);
    
	// Assert
	EXPECT_EQ(XmlExpression::NO_MATCH, result1);
	EXPECT_EQ(0, result2);
}

TEST(XPath, OneLevelXPathFromRoot) {
	// Arrange
	auto expr = XmlExpression::FromText("/bb");
	LibXmlAttributeCollection attrs{ nullptr };
	
	// Act
	auto result1 = expr->ProcessStartTag("aa", attrs);
	auto result2 = expr->ProcessStartTag("bb", attrs);
    
	// Assert
	EXPECT_EQ(XmlExpression::NO_MATCH, result1);
	EXPECT_EQ(XmlExpression::NO_MATCH, result2);
}

TEST(XPath, OneLevelXPathAnyDepth) {
	// Arrange
	auto expr = XmlExpression::FromText("//bb");
	LibXmlAttributeCollection attrs{ nullptr };
	
	// Act
	auto result1 = expr->ProcessStartTag("aa", attrs);
	auto result2 = expr->ProcessStartTag("bb", attrs);
    
	// Assert
	EXPECT_EQ(XmlExpression::NO_MATCH, result1);
	EXPECT_EQ(0, result2);
}

TEST(XPath, TwoLevelXPathAnyDepth) {
	// Arrange
	auto expr = XmlExpression::FromText("//aa//bb");
	LibXmlAttributeCollection attrs{ nullptr };

	// Act
	auto result1 = expr->ProcessStartTag("xx", attrs);
	auto result2 = expr->ProcessStartTag("aa", attrs);
	auto result3 = expr->ProcessStartTag("yy", attrs);
	auto result4 = expr->ProcessStartTag("bb", attrs);
    
	// Assert
	EXPECT_EQ(XmlExpression::NO_MATCH, result1);
	EXPECT_EQ(XmlExpression::NO_MATCH, result2);
	EXPECT_EQ(XmlExpression::NO_MATCH, result3);
	EXPECT_EQ(0, result4);
}
