#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <algorithm>
#include <iterator>
#include <memory>
#include <sstream>

#include "inlinebuffer.h"
#include "customprinters.h"

using namespace std;

static const string testString = "abcdefghijklmnopqrstuvwxyz";

TEST(InlineBuffer, PeekReturnsCorrectCharAndDoesNotAdvance) {
	// Arrange
	InlineBuffer buf{ make_unique<istringstream>(testString), 100 };

	//Act
	// Assert
	EXPECT_EQ('a', buf.peek());
	EXPECT_EQ('a', buf.peek());
}

TEST(InlineBuffer, GetCharReturnsCorrectCharAndDoesAdvance) {
	// Arrange
	char ch1, ch2;
	InlineBuffer buf{ make_unique<istringstream>(testString), 100 };

	//Act
	buf.get(ch1);
	buf.get(ch2);

	// Assert
	EXPECT_EQ('a', ch1);
	EXPECT_EQ('b', ch2);
}

TEST(InlineBuffer, GetCharSetsEofFlag) {
	// Arrange
	char ch1, ch2, ch3;
	InlineBuffer buf{ make_unique<istringstream>("12"), 10 };

	//Act
	// Assert
	EXPECT_FALSE(buf.eof());
	buf.get(ch1);
	EXPECT_EQ('1', ch1);
	EXPECT_FALSE(buf.eof());
	buf.get(ch2);
	EXPECT_EQ('2', ch2);
	EXPECT_FALSE(buf.eof());
	buf.get(ch3);
	EXPECT_EQ(EOF, ch3);
	EXPECT_TRUE(buf.eof());
}

TEST(InlineBuffer, PeekSetsEofFlag) {
	// Arrange
	char ch1, ch2;
	InlineBuffer buf{ make_unique<istringstream>("12"), 10 };

	//Act
	buf.get(ch1);
	buf.get(ch2);

	// Assert
	EXPECT_FALSE(buf.eof());
	EXPECT_EQ(EOF, buf.peek());
	EXPECT_TRUE(buf.eof());
}

TEST(InlineBuffer, GetLineReturnsCorrectString) {
	// Arrange
	string result;
	InlineBuffer buf{ make_unique<istringstream>(testString), 100 };

	//Act
	buf.get(result, 'g');

	// Assert
	EXPECT_EQ("abcdef", result);
	EXPECT_EQ('g', buf.peek());
}

TEST(InlineBuffer, GetLineReturnsCorrectStringAcrossBuffers) {
	// Arrange
	string result;
	InlineBuffer buf{ make_unique<istringstream>(testString), 10 };

	//Act
	buf.get(result, 'x');

	// Assert
	EXPECT_EQ("abcdefghijklmnopqrstuvw", result);
	EXPECT_EQ('x', buf.peek());
}

TEST(InlineBuffer, GetLineSetsEofFlag) {
	// Arrange
	string result;
	InlineBuffer buf{ make_unique<istringstream>(testString), 100 };

	//Act
	buf.get(result, '<');

	// Assert
	EXPECT_EQ(testString, result);
	EXPECT_TRUE(buf.eof());
}
