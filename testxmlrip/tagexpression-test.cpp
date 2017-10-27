#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include "tagexpression.h"

using namespace std;


TEST(TagExpression, ProcessTagReturnsTrueWithSingleTagExpressionWhenTagMatches) {
    TagExpression expr;
	Tag testTag("aa", true, false);
	expr.AddPredicate(TagPredicate{"aa"});
    
	EXPECT_TRUE(expr.ProcessTag(testTag));
}

TEST(TagExpression, ProcessTagReturnsFalseWithSingleTagExpressionWhenTagDoesNotMatch) {
    TagExpression expr;
	Tag testTag("bb", true, false);
	expr.AddPredicate(TagPredicate{"aa"});
    
	EXPECT_FALSE(expr.ProcessTag(testTag));
}

TEST(TagExpression, ProcessTagReturnsTrueForChildTagsOfFullMatch) {
	// Arrange
    TagExpression expr;
	Tag testTag1("aa", true, false);
	Tag testTag2("bb", true, false);
	expr.AddPredicate(TagPredicate{"aa"});
	
	// Act
	expr.ProcessTag(testTag1);
	auto result = expr.ProcessTag(testTag2);
    
	// Assert
	EXPECT_TRUE(result);
}

TEST(TagExpression, ProcessTagReturnsTrueForClosingTagOfFullMatch) {
	// Arrange
    TagExpression expr;
	Tag testTag1("aa", true, false);
	Tag testTag2("aa", false, true);
	expr.AddPredicate(TagPredicate{"aa"});
	
	// Act
	expr.ProcessTag(testTag1);
	auto result = expr.ProcessTag(testTag2);
    
	// Assert
	EXPECT_TRUE(result);
}

TEST(TagExpression, ProcessTagReturnsTrueForMatchingOpenClosingTag) {
	// Arrange
    TagExpression expr;
	Tag testTag1("aa", true, true);
	expr.AddPredicate(TagPredicate{"aa"});
	
	// Act
	auto result = expr.ProcessTag(testTag1);
    
	// Assert
	EXPECT_TRUE(result);
}

TEST(TagExpression, ProcessTagReturnsFalseAfterMatchingTagClosed) {
	// Arrange
    TagExpression expr;
	Tag testTag1("aa", true, false);
	Tag testTag2("aa", false, true);
	Tag testTag3("bb", true, false);
	expr.AddPredicate(TagPredicate{"aa"});
	
	// Act
	expr.ProcessTag(testTag1);
	expr.ProcessTag(testTag2);
	auto result = expr.ProcessTag(testTag3);
    
	// Assert
	EXPECT_FALSE(result);
}

TEST(TagExpression, ProcessTagProcessesTwoPrecidatesCorrectly) {
	// Arrange
    TagExpression expr;
	Tag openAATag("aa", true, false);
	Tag closeAATag("aa", false, true);
	Tag openBBTag("bb", true, false);
	Tag closeBBTag("bb", false, true);
	Tag openCCTag("cc", true, false);
	Tag closeCCTag("cc", false, true);
	expr.AddPredicate(TagPredicate{"aa"});
	expr.AddPredicate(TagPredicate{"bb"});
	
	// Act
	// Assert
	// <aa><bb><cc></cc></bb><cc></cc><bb></bb></aa><bb></bb>
	EXPECT_FALSE(expr.ProcessTag(openAATag));
	EXPECT_TRUE(expr.ProcessTag(openBBTag));
	EXPECT_TRUE(expr.ProcessTag(openCCTag));
	EXPECT_TRUE(expr.ProcessTag(closeCCTag));
	EXPECT_TRUE(expr.ProcessTag(closeBBTag));
	EXPECT_FALSE(expr.ProcessTag(openCCTag));
	EXPECT_FALSE(expr.ProcessTag(closeCCTag));
	EXPECT_TRUE(expr.ProcessTag(openBBTag));
	EXPECT_TRUE(expr.ProcessTag(closeBBTag));
   	EXPECT_FALSE(expr.ProcessTag(closeAATag));
	EXPECT_FALSE(expr.ProcessTag(openBBTag));
	EXPECT_FALSE(expr.ProcessTag(closeBBTag));

}

TEST(TagExpression, FromTextCreatesSingleItemExpressionCorrectly) {
	// Arrange
	
	// Act
	auto expr = TagExpression::FromText("aa");
	
	// Assert
	ASSERT_TRUE((bool)expr);

	auto predicates = expr->GetPredicates();
	EXPECT_EQ(1U, predicates.size());
	EXPECT_EQ("aa", predicates[0].GetTagName());
}

TEST(TagExpression, FromTextCreatesTwoItemExpressionCorrectly) {
	// Arrange
	
	// Act
	auto expr = TagExpression::FromText("aa/bb");
	
	// Assert
	ASSERT_TRUE((bool)expr);

	auto predicates = expr->GetPredicates();
	EXPECT_EQ(2U, predicates.size());
	EXPECT_EQ("aa", predicates[0].GetTagName());
	EXPECT_EQ("bb", predicates[1].GetTagName());
}
