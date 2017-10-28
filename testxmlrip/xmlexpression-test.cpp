#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include "xmlexpression.h"

using namespace std;


TEST(XmlExpression, ProcessTagReturnsTrueWithSingleTagExpressionWhenTagMatches) {
    XmlExpression expr;
	XmlElement testElement(XmlElement::Type::tag, "aa", true, false);
	expr.AddPredicate(XmlPredicate{"aa"});
    
	EXPECT_TRUE(expr.ProcessElement(testElement));
}

TEST(XmlExpression, ProcessTagReturnsFalseWithSingleTagExpressionWhenTagDoesNotMatch) {
    XmlExpression expr;
	XmlElement testElement(XmlElement::Type::tag, "bb", true, false);
	expr.AddPredicate(XmlPredicate{"aa"});
    
	EXPECT_FALSE(expr.ProcessElement(testElement));
}

TEST(XmlExpression, ProcessTagReturnsTrueForChildTagsOfFullMatch) {
	// Arrange
    XmlExpression expr;
	XmlElement testElement1(XmlElement::Type::tag, "aa", true, false);
	XmlElement testElement2(XmlElement::Type::tag, "bb", true, false);
	expr.AddPredicate(XmlPredicate{"aa"});
	
	// Act
	expr.ProcessElement(testElement1);
	auto result = expr.ProcessElement(testElement2);
    
	// Assert
	EXPECT_TRUE(result);
}

TEST(XmlExpression, ProcessTagReturnsTrueForClosingTagOfFullMatch) {
	// Arrange
    XmlExpression expr;
	XmlElement testElement1(XmlElement::Type::tag, "aa", true, false);
	XmlElement testElement2(XmlElement::Type::tag, "aa", false, true);
	expr.AddPredicate(XmlPredicate{"aa"});
	
	// Act
	expr.ProcessElement(testElement1);
	auto result = expr.ProcessElement(testElement2);
    
	// Assert
	EXPECT_TRUE(result);
}

TEST(XmlExpression, ProcessTagReturnsTrueForMatchingOpenClosingTag) {
	// Arrange
    XmlExpression expr;
	XmlElement testElement1(XmlElement::Type::tag, "aa", true, true);
	expr.AddPredicate(XmlPredicate{"aa"});
	
	// Act
	auto result = expr.ProcessElement(testElement1);
    
	// Assert
	EXPECT_TRUE(result);
}

TEST(XmlExpression, ProcessTagReturnsFalseAfterMatchingTagClosed) {
	// Arrange
    XmlExpression expr;
	XmlElement testElement1(XmlElement::Type::tag, "aa", true, false);
	XmlElement testElement2(XmlElement::Type::tag, "aa", false, true);
	XmlElement testElement3(XmlElement::Type::tag, "bb", true, false);
	expr.AddPredicate(XmlPredicate{"aa"});
	
	// Act
	expr.ProcessElement(testElement1);
	expr.ProcessElement(testElement2);
	auto result = expr.ProcessElement(testElement3);
    
	// Assert
	EXPECT_FALSE(result);
}

TEST(XmlExpression, ProcessTagProcessesTwoPrecidatesCorrectly) {
	// Arrange
    XmlExpression expr;
	XmlElement openAATag(XmlElement::Type::tag, "aa", true, false);
	XmlElement closeAATag(XmlElement::Type::tag, "aa", false, true);
	XmlElement openBBTag(XmlElement::Type::tag, "bb", true, false);
	XmlElement closeBBTag(XmlElement::Type::tag, "bb", false, true);
	XmlElement openCCTag(XmlElement::Type::tag, "cc", true, false);
	XmlElement closeCCTag(XmlElement::Type::tag, "cc", false, true);
	expr.AddPredicate(XmlPredicate{"aa"});
	expr.AddPredicate(XmlPredicate{"bb"});
	
	// Act
	// Assert
	// <aa><bb><cc></cc></bb><cc></cc><bb></bb></aa><bb></bb>
	EXPECT_FALSE(expr.ProcessElement(openAATag));
	EXPECT_TRUE(expr.ProcessElement(openBBTag));
	EXPECT_TRUE(expr.ProcessElement(openCCTag));
	EXPECT_TRUE(expr.ProcessElement(closeCCTag));
	EXPECT_TRUE(expr.ProcessElement(closeBBTag));
	EXPECT_FALSE(expr.ProcessElement(openCCTag));
	EXPECT_FALSE(expr.ProcessElement(closeCCTag));
	EXPECT_TRUE(expr.ProcessElement(openBBTag));
	EXPECT_TRUE(expr.ProcessElement(closeBBTag));
   	EXPECT_FALSE(expr.ProcessElement(closeAATag));
	EXPECT_FALSE(expr.ProcessElement(openBBTag));
	EXPECT_FALSE(expr.ProcessElement(closeBBTag));

}

TEST(XmlExpression, FromTextCreatesSingleItemExpressionCorrectly) {
	// Arrange
	
	// Act
	auto expr = XmlExpression::FromText("aa");
	
	// Assert
	ASSERT_TRUE((bool)expr);

	auto predicates = expr->GetPredicates();
	EXPECT_EQ(1U, predicates.size());
	EXPECT_EQ("aa", predicates[0].GetTagName());
}

TEST(XmlExpression, FromTextCreatesTwoItemExpressionCorrectly) {
	// Arrange
	
	// Act
	auto expr = XmlExpression::FromText("aa/bb");
	
	// Assert
	ASSERT_TRUE((bool)expr);

	auto predicates = expr->GetPredicates();
	EXPECT_EQ(2U, predicates.size());
	EXPECT_EQ("aa", predicates[0].GetTagName());
	EXPECT_EQ("bb", predicates[1].GetTagName());
}
