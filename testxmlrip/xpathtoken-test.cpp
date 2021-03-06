#include <algorithm>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include "xpathtoken.h"

using namespace std;

/******************************************************************************************/
/* constructor tests                                                                 */
/******************************************************************************************/

TEST(XPathToken, ThreeParamConstructorSetsType) {
	// Arrange
	string chars("//");
	
	// Act
	XPathToken token{XPathToken::TOK_SLASH, 5, begin(chars), end(chars)};
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_SLASH, token.GetType());
	
}

TEST(XPathToken, OneParamConstructorSetsType) {
	// Arrange
	
	// Act
	XPathToken token{XPathToken::TOK_NULL, -1};
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_NULL, token.GetType());
	
}

/******************************************************************************************/
/* GetString tests                                                                 */
/******************************************************************************************/

TEST(XPathToken, GetStringReturnsTokenText) {
	// Arrange
	string chars("tokenText");
	
	// Act
	XPathToken token{XPathToken::TOK_STRING, 5, begin(chars), end(chars)};
	
	// Assert
	EXPECT_EQ(chars, token.GetString());
	
}
	
TEST(XPathToken, GetStringReturnsEmptyStringWhenNoTokenText) {
	// Arrange
	
	// Act
	XPathToken token{XPathToken::TOK_NULL, -1};
	
	// Assert
	EXPECT_EQ("", token.GetString());
	
}

/******************************************************************************************/
/* GetPosition tests                                                                 */
/******************************************************************************************/

TEST(XPathToken, GetPositionReturnsPosition) {
	// Arrange
	string chars("tokenText");

	// Act
	XPathToken token{ XPathToken::TOK_STRING, 5, begin(chars), end(chars) };

	// Assert
	EXPECT_EQ(5, token.GetPosition());

}

