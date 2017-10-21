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
