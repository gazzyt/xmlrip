#include <sstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include "xpathtokeniser.h"

using namespace std;

/******************************************************************************************/
/* GetNextToken tests                                                                 */
/******************************************************************************************/

TEST(XPathTokeniser, ReturnsNullTokenForEmptyStream) {
	// Arrange
	istringstream stream("");
	XPathTokeniser tokeniser(stream);
	
	// Act
	XPathToken token = tokeniser.GetNextToken();
	
	// Assert
	EXPECT_EQ(XPathToken::TOK_NULL, token.GetType());
	
}

