#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop


#include "tag.h"

using namespace std;


TEST(Tag, CreatesCorrectTagFromNameOnly) {
	// Arrange
	string tagText{"aa"};
	
	// Act
	Tag tag = Tag::FromText(tagText, true, true);
	
	// Assert
	EXPECT_TRUE(tag.IsOpeningTag());
	EXPECT_TRUE(tag.IsClosingTag());
	EXPECT_EQ("aa", tag.GetTagName());
}

TEST(Tag, CreatesCorrectTagFromNameAndAttributes) {
	// Arrange
	string tagText{"aa att=3"};
	
	// Act
	Tag tag = Tag::FromText(tagText, true, true);
	
	// Assert
	EXPECT_TRUE(tag.IsOpeningTag());
	EXPECT_TRUE(tag.IsClosingTag());
	EXPECT_EQ("aa", tag.GetTagName());
}
