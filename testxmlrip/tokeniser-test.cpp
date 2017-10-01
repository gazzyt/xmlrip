#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <memory>
#include <sstream>

#include "tokeniser.h"

using namespace std;

static const string simpleXml = "<a></a>";

TEST(Tokeniser, CreatesCorrectTokens) {
	auto xmlStream = make_unique<istringstream>(simpleXml);
	Tokeniser tokeniser{move(xmlStream)};
	auto token1 = tokeniser.GetNextToken();
    EXPECT_EQ(token1.GetType(), Token::Type::lt);
	
	auto token2 = tokeniser.GetNextToken();
	EXPECT_EQ(token2.GetType(), Token::Type::string);
	EXPECT_EQ(token2.GetStringValue(), "a");
}

