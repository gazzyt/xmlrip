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

TEST(InlineBuffer, GetLineReturnsCorrectString) {
	// Arrange
	stringbuf result;
	InlineBuffer buf{ make_unique<istringstream>(testString), 100 };

	//Act
	buf.get(result, 'g');

	// Assert
	EXPECT_EQ("abcdef", result.str());
	EXPECT_EQ('g', buf.peek());
}

TEST(InlineBuffer, GetLineReturnsCorrectStringAcrossBuffers) {
	// Arrange
	stringbuf result;
	InlineBuffer buf{ make_unique<istringstream>(testString), 10 };

	//Act
	buf.get(result, 'x');

	// Assert
	EXPECT_EQ("abcdefghijklmnopqrstuvw", result.str());
	EXPECT_EQ('x', buf.peek());
}
