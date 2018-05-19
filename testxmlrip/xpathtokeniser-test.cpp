
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include "xpathtokeniser.h"
#include "exception/xpathexception.h"

using namespace std;

/******************************************************************************************/
/* GetNextToken tests                                                                 */
/******************************************************************************************/

TEST(XPathTokeniser, GetNextTokenReturnsNullTokenForEmptyString) {
	// Arrange
	string xpath("");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	XPathToken token = tokeniser.GetNextToken();
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_NULL, token.GetType());
}

TEST(XPathTokeniser, GetNextTokenReturnsStringTokenForWord) {
	// Arrange
	string xpath("inner");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	XPathToken token = tokeniser.GetNextToken();
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_STRING, token.GetType());
	EXPECT_EQ(xpath, token.GetString());
}

TEST(XPathTokeniser, GetNextTokenReturnsSlashTokenForSlash) {
	// Arrange
	string xpath("/");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	XPathToken token = tokeniser.GetNextToken();
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_SLASH, token.GetType());
	EXPECT_EQ(xpath, token.GetString());
}

TEST(XPathTokeniser, GetNextTokenReturnsDoubleSlashTokenForDoubleSlash) {
	// Arrange
	string xpath("//");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	XPathToken token = tokeniser.GetNextToken();
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_DBLSLASH, token.GetType());
	EXPECT_EQ(xpath, token.GetString());
}

TEST(XPathTokeniser, GetNextTokenReturnsLeftSquareBracketTokenForLeftSquareBracket) {
	// Arrange
	string xpath("[");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	XPathToken token = tokeniser.GetNextToken();
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_LEFTSQUAREBRACKET, token.GetType());
	EXPECT_EQ(xpath, token.GetString());
}

TEST(XPathTokeniser, GetNextTokenReturnsRightSquareBracketTokenForRightSquareBracket) {
	// Arrange
	string xpath("]");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	XPathToken token = tokeniser.GetNextToken();
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_RIGHTSQUAREBRACKET, token.GetType());
	EXPECT_EQ(xpath, token.GetString());
}

TEST(XPathTokeniser, GetNextTokenReturnsEqualsTokenForEquals) {
	// Arrange
	string xpath("=");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	XPathToken token = tokeniser.GetNextToken();
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_EQUALS, token.GetType());
	EXPECT_EQ(xpath, token.GetString());
}

TEST(XPathTokeniser, GetNextTokenReturnsAtTokenForAt) {
	// Arrange
	string xpath("@");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	XPathToken token = tokeniser.GetNextToken();
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_AT, token.GetType());
	EXPECT_EQ(xpath, token.GetString());
}

TEST(XPathTokeniser, GetNextTokenReturnsCorrectTokenSequence) {
	// Arrange
	string xpath("/inner/outer");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	XPathToken token1 = tokeniser.GetNextToken();
	XPathToken token2 = tokeniser.GetNextToken();
	XPathToken token3 = tokeniser.GetNextToken();
	XPathToken token4 = tokeniser.GetNextToken();
	XPathToken token5 = tokeniser.GetNextToken();

	// Assert
	EXPECT_EQ(XPathToken::TOK_SLASH, token1.GetType());
	EXPECT_EQ(XPathToken::TOK_STRING, token2.GetType());
	EXPECT_EQ("inner", token2.GetString());
	EXPECT_EQ(XPathToken::TOK_SLASH, token3.GetType());
	EXPECT_EQ(XPathToken::TOK_STRING, token4.GetType());
	EXPECT_EQ("outer", token4.GetString());
	EXPECT_EQ(XPathToken::TOK_NULL, token5.GetType());
}

TEST(XPathTokeniser, GetNextTokenReturnsDoubleQuotedStringToken) {
	// Arrange
	string xpath("/inner[@a=\" one two \"]");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	tokeniser.GetNextToken();
	tokeniser.GetNextToken();
	tokeniser.GetNextToken();
	tokeniser.GetNextToken();
	tokeniser.GetNextToken();
	tokeniser.GetNextToken();
	XPathToken token = tokeniser.GetNextToken();

	// Assert
	EXPECT_EQ(XPathToken::TOK_STRING, token.GetType());
	EXPECT_EQ(" one two ", token.GetString());
}

TEST(XPathTokeniser, GetNextTokenThrowsXPathExceptionForMissingClosingDoubleQuote) {
	// Arrange
	string xpath("/inner[@a=\" one two ]");
	XPathTokeniser tokeniser(xpath);
	bool exceptionThrown = false;

	// Act
	try
	{
		tokeniser.GetNextToken();
		tokeniser.GetNextToken();
		tokeniser.GetNextToken();
		tokeniser.GetNextToken();
		tokeniser.GetNextToken();
		tokeniser.GetNextToken();
		tokeniser.GetNextToken();
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_EQ("Missing closing quote", e.GetMessage());
	}

	EXPECT_TRUE(exceptionThrown);
}

TEST(XPathTokeniser, GetNextTokenReturnsSingleQuotedStringToken) {
	// Arrange
	string xpath("/inner[@a=' one two ']");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	tokeniser.GetNextToken();
	tokeniser.GetNextToken();
	tokeniser.GetNextToken();
	tokeniser.GetNextToken();
	tokeniser.GetNextToken();
	tokeniser.GetNextToken();
	XPathToken token = tokeniser.GetNextToken();

	// Assert
	EXPECT_EQ(XPathToken::TOK_STRING, token.GetType());
	EXPECT_EQ(" one two ", token.GetString());
}

TEST(XPathTokeniser, GetNextTokenThrowsXPathExceptionForMissingClosingSingleQuote) {
	// Arrange
	string xpath("/inner[@a=' one two ]");
	XPathTokeniser tokeniser(xpath);
	bool exceptionThrown = false;

	// Act
	try
	{
		tokeniser.GetNextToken();
		tokeniser.GetNextToken();
		tokeniser.GetNextToken();
		tokeniser.GetNextToken();
		tokeniser.GetNextToken();
		tokeniser.GetNextToken();
		tokeniser.GetNextToken();
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_EQ("Missing closing quote", e.GetMessage());
	}

	EXPECT_TRUE(exceptionThrown);
}
	
TEST(XPathTokeniser, GetNextTokenThrowsXPathExceptionForIllegalCharactor) {
	// Arrange
	string xpath("|");
	XPathTokeniser tokeniser(xpath);
	bool exceptionThrown = false;

	// Act
	try
	{
		tokeniser.GetNextToken();
	}
	catch (XPathException& e)
	{
		exceptionThrown = true;
		EXPECT_EQ("Unexpected character in XPath: |", e.GetMessage());
	}

	EXPECT_TRUE(exceptionThrown);
}

