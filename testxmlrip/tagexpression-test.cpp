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
