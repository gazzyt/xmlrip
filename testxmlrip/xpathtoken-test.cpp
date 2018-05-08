#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include "xpathtoken.h"

using namespace std;

/******************************************************************************************/
/* constructor tests                                                                 */
/******************************************************************************************/

TEST(XPathToken, ConstructorSetsType) {
	// Arrange
	
	// Act
	XPathToken token{XPathToken::TOK_SLASH};
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_SLASH, token.GetType());
	
}

