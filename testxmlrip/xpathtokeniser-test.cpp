
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

TEST(XPathTokeniser, ReturnsNullTokenForEmptyString) {
	// Arrange
	string xpath("");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	XPathToken token = tokeniser.GetNextToken();
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_NULL, token.GetType());
}

TEST(XPathTokeniser, ReturnsStringTokenForWord) {
	// Arrange
	string xpath("inner");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	XPathToken token = tokeniser.GetNextToken();
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_STRING, token.GetType());
	EXPECT_EQ(xpath, token.GetString());
}

TEST(XPathTokeniser, ReturnsSlashTokenForSlash) {
	// Arrange
	string xpath("/");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	XPathToken token = tokeniser.GetNextToken();
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_SLASH, token.GetType());
	EXPECT_EQ(xpath, token.GetString());
}

TEST(XPathTokeniser, ReturnsAtTokenForAt) {
	// Arrange
	string xpath("@");
	XPathTokeniser tokeniser(xpath);
	
	// Act
	XPathToken token = tokeniser.GetNextToken();
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_AT, token.GetType());
	EXPECT_EQ(xpath, token.GetString());
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

