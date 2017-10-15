#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <algorithm>
#include <memory>
#include <sstream>

#include "tagpredicate.h"

using namespace std;


TEST(TagPredicate, IsMatchReturnsTrueWhenOpeningTagNamesMatch) {
    Tag testTag("aa", true, false);
    TagPredicate testPredicate("aa");
    
	EXPECT_TRUE(testPredicate.IsMatch(testTag));
}

TEST(TagPredicate, IsMatchReturnsTrueWhenOpeningClosingTagNamesMatch) {
    Tag testTag("aa", true, true);
    TagPredicate testPredicate("aa");
    
	EXPECT_TRUE(testPredicate.IsMatch(testTag));
}

TEST(TagPredicate, IsMatchReturnsFalseWhenClosingTagNamesMatch) {
    Tag testTag("aa", false, true);
    TagPredicate testPredicate("aa");
    
	EXPECT_FALSE(testPredicate.IsMatch(testTag));
}
